#include "JDM/Header/JDMwindow.hpp"
#include "JDM/Header/cacheManager.hpp"
#include "JDM/Header/JDMbaseComponents/JDMbaseLayout.hpp"


JLIST<JPAIR<JPAIR<JSP<JDM::Comp::Components>, JUINT>, JCHAR>> JDM::Window::_allHandlingComponents = {};
JLIST<JSP<JDM::AnimationBase>>                                JDM::Window::_allAnimations         = {};
JLIST<JSP<JDM::Clock>>                                        JDM::Window::_allClock              = {};
JLIST<JSP<JDM::Comp::Components>>                             JDM::Window::_allComponents         = {};
JDM::Comp::FocusedTextComponent                              *JDM::Window::focusedTextComponent  = JNULLPTR;

JDM::Window::Window(
    JSTRVIEW title,
    JCONST JDM::PositionSize posSize,
    JCONST JDM::ColorRGB windowColor
) :
    _title        (JSTR(title)),
    _winColor     (windowColor),
    _positionSize (posSize)
{
    JDM::Logger(" > [ START ]: Windows Opening: JDM - SDL2 (", title , ")");

    JDM::Logger(" > [ INFO ]: Trying to init EVERYTHING...");
    JIF (JTHIS->_initializeAll())
    {
        JDM::Logger(" > [ ERROR ]: An issue occurred during the initialization process.");
        JTHIS->_handleError();
    }

    JDM::Logger(" > [ INFO ]: Creating window...");
    JIF (JTHIS->_createWindow())
    {
        JDM::Logger(" > [ ERROR ]: An issue occurred during the creation of the window.");
        JTHIS->_handleError();
    }

    JDM::Logger(" > [ INFO ]: Creating renderer...");
    JIF (JTHIS->_createRenderer())
    {
        JDM::Logger(" > [ ERROR ]: An issue occurred during the creation of the renderer.");
        JTHIS->_handleError();
    }

    JDM::Logger(" > [ INFO ]: Windows Opened: JDM - SDL2 (", title , ")");

    JDM::WindowWidth  = JTHIS->_positionSize.width;
    JDM::WindowHeight = JTHIS->_positionSize.height;
}

JDM::Window::~Window()
{
    SDL_DestroyWindow   (JTHIS->_window);
    SDL_DestroyRenderer (JDM::renderer);
    JIF (JTHIS->_iconSurface != JNULLPTR)
        SDL_FreeSurface(JTHIS->_iconSurface);

    JDM::CacheManager::cleanSurfaceCache();
    SDL_Quit();

    JDM::Logger(" > [ END ]: Windows Closed: JDM - SDL2 (", JTHIS->_title , ")");
}

JCVOID JDM::Window::_handleError()
{
    JDM::Logger(" > [ INFO ]: Exiting due to an Error.");
    JEXIT(EXIT_FAILURE);
}

JCBOOL JDM::Window::_initializeAll()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

    JINT imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    JRETURN (
        (  SDL_Init(SDL_INIT_EVERYTHING) != 0)
    ||  (  TTF_Init() != 0)
    ||  (!(IMG_Init(imgFlags) & imgFlags))
    );
}

JCBOOL JDM::Window::_createWindow()
{
    JTHIS->_window = SDL_CreateWindow(
        JTHIS->_title.c_str(),
        JTHIS->_positionSize.x,
        JTHIS->_positionSize.y,
        JTHIS->_positionSize.width,
        JTHIS->_positionSize.height,
        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL
    );
    JRETURN (JTHIS->_window == JNULLPTR);
}

JCBOOL JDM::Window::_createRenderer()
{
    JDM::renderer = SDL_CreateRenderer(
        JTHIS->_window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE
    );
    JRETURN (JDM::renderer == JNULLPTR);
}

JCVOID JDM::Window::run()
{
    JDM::Logger(" > [ INFO ]: Initializing all objects...");
    JTHIS->initAllObjects    ();
    JTHIS->_handleComponents ();

    JFOR (JCONST JAUTO &comp : JTHIS->_allComponents)
    {
        JAUTO layout = JDYNAMICC<JDM::Base::BaseLayout*>(comp.get());
        JIF (layout != JNULLPTR)
            layout->handleChildren();
    }

    JTHIS->_running   = SDL_TRUE;
    JTHIS->_firstTime = SDL_GetTicks();
    JDM::Logger(" > [ INFO ]: JDM - SDL2 (", JTHIS->_title , ") is running...");

    JWHILE (JTHIS->_running)
    {
        JTHIS->_secondTime = SDL_GetTicks();
        if ((JTHIS->_secondTime - JTHIS->_firstTime) > (1000 / JDM::FPS))
        {
            JUINT32 FrameTime = JTHIS->_secondTime - JTHIS->_prevTime;
            JTHIS->_prevTime  = JTHIS->_secondTime;

            JDM::TimeFrame   = FrameTime / 1000.0;
            JDM::ElapseTime += JDM::TimeFrame;

            JTHIS->_pollEvent();
            JTHIS->_animationUpdate();
            JTHIS->_winUpdate();

            JTHIS->update();
            JTHIS->_winRender();
            JTHIS->_handleComponents();

            JTHIS->_firstTime = SDL_GetTicks();
        }
    }
}

JCVOID JDM::Window::_setFocusedTextComponent(JDM::Comp::FocusedTextComponent *focusedText)
{
    JDM::Window::focusedTextComponent = focusedText;
}

JCVOID JDM::Window::_animationUpdate()
{
    JFOR(JAUTO anim = JDM::Window::_allAnimations.begin(); anim != JDM::Window::_allAnimations.end();)
    {
        JIF ((*anim)->update() && (*anim)->getAutoRemove())
            anim = JDM::Window::_allAnimations.erase(anim);

        anim++;
    }
    JFOR(JAUTO timer = JDM::Window::_allClock.begin(); timer != JDM::Window::_allClock.end();)
    {
        JIF ((*timer)->update() && (*timer)->getAutoRemove())
            timer = JDM::Window::_allClock.erase(timer);

        timer++;
    }
}

JCVOID JDM::Window::_winUpdate()
{
    JFOR (JAUTO comp = JDM::Window::_allComponents.rbegin(); comp != JDM::Window::_allComponents.rend(); comp++)
        JIF (!(*comp)->getDisabled())
            (*comp)->updateComp();
}

JCVOID JDM::Window::_winRender()
{
    SDL_SetRenderDrawColor(JDM::renderer, JTHIS->_winColor.r, JTHIS->_winColor.g, JTHIS->_winColor.b, 0xff);
    SDL_RenderClear(JDM::renderer);

    JFOR (JAUTO comp = JDM::Window::_allComponents.rbegin(); comp != JDM::Window::_allComponents.rend(); comp++)
        JIF (!(*comp)->getDisabled() && (*comp)->getRendering())
            (*comp)->renderComp();

    JIF (JTHIS->_isCursorChangeable)
    {
        JTHIS->_cursorRect = {JDM::Mouse::GlobalMouseX - JDM::WindowX, JDM::Mouse::GlobalMouseY - JDM::WindowY, 20, 20};
        SDL_RenderCopy(JDM::renderer, JTHIS->_cursorTexture, JNULLPTR, &JTHIS->_cursorRect);
    }
    SDL_RenderPresent(JDM::renderer);
}

JCVOID JDM::Window::_pollEvent()
{
    SDL_GetGlobalMouseState (&JDM::Mouse::GlobalMouseX, &JDM::Mouse::GlobalMouseY);
    SDL_GetWindowPosition   (JTHIS->_window, &JDM::WindowX, &JDM::WindowY);

    JWHILE (SDL_PollEvent(&JTHIS->_event))
    {
        JSWITCH (JTHIS->_event.type)
        {
            JCASE SDL_QUIT:
                JTHIS->_running = SDL_FALSE;
                JBREAK;
            JCASE SDL_KEYDOWN:
                JIF (JTHIS->_isKeyDown)
                    JTHIS->keyHold(JTHIS->_keyBoardDown(JTHIS->_event.key));
                JELSE
                    JTHIS->keyDown(JTHIS->_keyBoardDown(JTHIS->_event.key));
                JBREAK;
            JCASE SDL_KEYUP:
                JTHIS->keyUp(JTHIS->_keyBoardUp(JTHIS->_event.key));
                JBREAK;
            JCASE SDL_MOUSEBUTTONDOWN:
                JDM::alreadyTouched = JFALSE;
                JIF (JDM::Window::focusedTextComponent != JNULLPTR)
                    JDM::Window::focusedTextComponent->isFocused = JFALSE;

                JDM::Window::focusedTextComponent = JNULLPTR;
                JTHIS->_mouseWinDown(JTHIS->_event.button);

                JFOR (JAUTO &comp : JDM::Window::_allComponents)
                {
                    JIF (!comp->getDisabled() && comp->mouseDownComp(JTHIS->_event.button))
                    {
                        JAUTO focusedText = JDYNAMICC<JDM::Comp::FocusedTextComponent*>(comp.get());
                        JIF (focusedText != JNULLPTR)
                            JDM::Window::focusedTextComponent->isFocused = JTRUE;
                    }
                }
                JBREAK;
            JCASE SDL_MOUSEMOTION:
                JTHIS->_mouseWinMotion(JTHIS->_event.motion);
                JFOR (JAUTO &comp : JDM::Window::_allComponents)
                    JIF(!comp->getDisabled())
                        comp->mouseMotionComp(JTHIS->_event.motion);
                JBREAK;
            JCASE SDL_MOUSEBUTTONUP:
                JTHIS->_mouseWinUp(JTHIS->_event.button);
                JFOR (JAUTO &comp : JDM::Window::_allComponents)
                    JIF(!comp->getDisabled())
                        comp->mouseUpComp(JTHIS->_event.button);
                JBREAK;
        }
    }
}
JCVOID JDM::Window::_mouseWinDown(SDL_MouseButtonEvent &mouse)
{
    JIF (mouse.button == SDL_BUTTON_LEFT)
        JDM::Mouse::LeftMouseDown = JTRUE;
    JELSE
        JDM::Mouse::RightMouseDown = JTRUE;
    JTHIS->mouseDown();
}

JCVOID JDM::Window::_mouseWinUp(SDL_MouseButtonEvent &mouse)
{
    JIF (mouse.button == SDL_BUTTON_RIGHT)
        JDM::Mouse::RightMouseDown = JFALSE;
    JELSE
        JDM::Mouse::LeftMouseDown = JFALSE;
    JTHIS->mouseUp();
}

JCVOID JDM::Window::_mouseWinMotion(SDL_MouseMotionEvent &mouse)
{
    SDL_GetMouseState  (&JDM::Mouse::MouseX, &JDM::Mouse::MouseY);
    JTHIS->mouseMotion ();
}

JCBOOL *JDM::Window::_keyBoardDown(SDL_KeyboardEvent &key)
{
    JTHIS->_isKeyDown = JTRUE;
    JSWITCH (key.keysym.sym) {
        JCASE SDLK_a        : JDM::KeyCode::A = JTRUE; JTHIS->_enterKey("a", "A"); JRETURN &JDM::KeyCode::A;
        JCASE SDLK_b        : JDM::KeyCode::B = JTRUE; JTHIS->_enterKey("b", "B"); JRETURN &JDM::KeyCode::B;
        JCASE SDLK_c        : JDM::KeyCode::C = JTRUE; JTHIS->_enterKey("c", "C"); JRETURN &JDM::KeyCode::C;
        JCASE SDLK_d        : JDM::KeyCode::D = JTRUE; JTHIS->_enterKey("d", "D"); JRETURN &JDM::KeyCode::D;
        JCASE SDLK_e        : JDM::KeyCode::E = JTRUE; JTHIS->_enterKey("e", "E"); JRETURN &JDM::KeyCode::E;
        JCASE SDLK_f        : JDM::KeyCode::F = JTRUE; JTHIS->_enterKey("f", "F"); JRETURN &JDM::KeyCode::F;
        JCASE SDLK_g        : JDM::KeyCode::G = JTRUE; JTHIS->_enterKey("g", "G"); JRETURN &JDM::KeyCode::G;
        JCASE SDLK_h        : JDM::KeyCode::H = JTRUE; JTHIS->_enterKey("h", "H"); JRETURN &JDM::KeyCode::H;
        JCASE SDLK_i        : JDM::KeyCode::I = JTRUE; JTHIS->_enterKey("i", "I"); JRETURN &JDM::KeyCode::I;
        JCASE SDLK_j        : JDM::KeyCode::J = JTRUE; JTHIS->_enterKey("j", "J"); JRETURN &JDM::KeyCode::J;
        JCASE SDLK_k        : JDM::KeyCode::K = JTRUE; JTHIS->_enterKey("k", "K"); JRETURN &JDM::KeyCode::K;
        JCASE SDLK_l        : JDM::KeyCode::L = JTRUE; JTHIS->_enterKey("l", "L"); JRETURN &JDM::KeyCode::L;
        JCASE SDLK_m        : JDM::KeyCode::M = JTRUE; JTHIS->_enterKey("m", "M"); JRETURN &JDM::KeyCode::M;
        JCASE SDLK_n        : JDM::KeyCode::N = JTRUE; JTHIS->_enterKey("n", "N"); JRETURN &JDM::KeyCode::N;
        JCASE SDLK_o        : JDM::KeyCode::O = JTRUE; JTHIS->_enterKey("o", "O"); JRETURN &JDM::KeyCode::O;
        JCASE SDLK_p        : JDM::KeyCode::P = JTRUE; JTHIS->_enterKey("p", "P"); JRETURN &JDM::KeyCode::P;
        JCASE SDLK_q        : JDM::KeyCode::Q = JTRUE; JTHIS->_enterKey("q", "Q"); JRETURN &JDM::KeyCode::Q;
        JCASE SDLK_r        : JDM::KeyCode::R = JTRUE; JTHIS->_enterKey("r", "R"); JRETURN &JDM::KeyCode::R;
        JCASE SDLK_s        : JDM::KeyCode::S = JTRUE; JTHIS->_enterKey("s", "S"); JRETURN &JDM::KeyCode::S;
        JCASE SDLK_t        : JDM::KeyCode::T = JTRUE; JTHIS->_enterKey("t", "T"); JRETURN &JDM::KeyCode::T;
        JCASE SDLK_u        : JDM::KeyCode::U = JTRUE; JTHIS->_enterKey("u", "U"); JRETURN &JDM::KeyCode::U;
        JCASE SDLK_v        : JDM::KeyCode::V = JTRUE; JTHIS->_enterKey("v", "V"); JRETURN &JDM::KeyCode::V;
        JCASE SDLK_w        : JDM::KeyCode::W = JTRUE; JTHIS->_enterKey("w", "W"); JRETURN &JDM::KeyCode::W;
        JCASE SDLK_x        : JDM::KeyCode::X = JTRUE; JTHIS->_enterKey("x", "X"); JRETURN &JDM::KeyCode::X;
        JCASE SDLK_y        : JDM::KeyCode::Y = JTRUE; JTHIS->_enterKey("y", "Y"); JRETURN &JDM::KeyCode::Y;
        JCASE SDLK_z        : JDM::KeyCode::Z = JTRUE; JTHIS->_enterKey("z", "Z"); JRETURN &JDM::KeyCode::Z;

        JCASE SDLK_LSHIFT   : JDM::KeyCode::LEFT_SHIFT    = JTRUE; JRETURN &JDM::KeyCode::LEFT_SHIFT;
        JCASE SDLK_RSHIFT   : JDM::KeyCode::RIGHT_SHIFT   = JTRUE; JRETURN &JDM::KeyCode::RIGHT_SHIFT;
        JCASE SDLK_LCTRL    : JDM::KeyCode::LEFT_CONTROL  = JTRUE; JRETURN &JDM::KeyCode::LEFT_CONTROL;
        JCASE SDLK_RCTRL    : JDM::KeyCode::RIGHT_CONTROL = JTRUE; JRETURN &JDM::KeyCode::RIGHT_CONTROL;
        JCASE SDLK_CAPSLOCK : JDM::KeyCode::CAPSLOCK      = JTRUE; JRETURN &JDM::KeyCode::CAPSLOCK;

        JCASE SDLK_RETURN:
            JDM::KeyCode::ENTER = JTRUE;
            JIF (JDM::Window::focusedTextComponent != JNULLPTR)
            { 
                JDM::Window::focusedTextComponent->isFocused = JFALSE;
                JDM::Window::focusedTextComponent->functionEnter();
            }
            JDM::Window::focusedTextComponent = JNULLPTR;
            JRETURN &JDM::KeyCode::ENTER;

        JCASE SDLK_TAB       : JDM::KeyCode::TAB       = JTRUE; JTHIS->_enterKey (" ", " "); JRETURN &JDM::KeyCode::TAB;
        JCASE SDLK_BACKSPACE : JDM::KeyCode::BACKSPACE = JTRUE; JTHIS->_deletekey(        ); JRETURN &JDM::KeyCode::BACKSPACE;
        JCASE SDLK_SPACE     : JDM::KeyCode::SPACE     = JTRUE; JTHIS->_enterKey (" ", " "); JRETURN &JDM::KeyCode::SPACE;
        JCASE SDLK_EQUALS    : JDM::KeyCode::KPLUS     = JTRUE; JTHIS->_enterKey ("=", "+"); JRETURN &JDM::KeyCode::KPLUS;
        JCASE SDLK_MINUS     : JDM::KeyCode::KMINUS    = JTRUE; JTHIS->_enterKey ("-", "_"); JRETURN &JDM::KeyCode::KMINUS;
        JCASE SDLK_0         : JDM::KeyCode::N0        = JTRUE; JTHIS->_enterKey ("0", ")"); JRETURN &JDM::KeyCode::N0;
        JCASE SDLK_1         : JDM::KeyCode::N1        = JTRUE; JTHIS->_enterKey ("1", "!"); JRETURN &JDM::KeyCode::N1;
        JCASE SDLK_2         : JDM::KeyCode::N2        = JTRUE; JTHIS->_enterKey ("2", "@"); JRETURN &JDM::KeyCode::N2;
        JCASE SDLK_3         : JDM::KeyCode::N3        = JTRUE; JTHIS->_enterKey ("3", "#"); JRETURN &JDM::KeyCode::N3;
        JCASE SDLK_4         : JDM::KeyCode::N4        = JTRUE; JTHIS->_enterKey ("4", "$"); JRETURN &JDM::KeyCode::N4;
        JCASE SDLK_5         : JDM::KeyCode::N5        = JTRUE; JTHIS->_enterKey ("5", "%"); JRETURN &JDM::KeyCode::N5;
        JCASE SDLK_6         : JDM::KeyCode::N6        = JTRUE; JTHIS->_enterKey ("6", "^"); JRETURN &JDM::KeyCode::N6;
        JCASE SDLK_7         : JDM::KeyCode::N7        = JTRUE; JTHIS->_enterKey ("7", "&"); JRETURN &JDM::KeyCode::N7;
        JCASE SDLK_8         : JDM::KeyCode::N8        = JTRUE; JTHIS->_enterKey ("8", "*"); JRETURN &JDM::KeyCode::N8;
        JCASE SDLK_9         : JDM::KeyCode::N9        = JTRUE; JTHIS->_enterKey ("9", "("); JRETURN &JDM::KeyCode::N9;

        JCASE SDLK_UP        : JDM::KeyCode::UP        = JTRUE; JRETURN &JDM::KeyCode::UP;
        JCASE SDLK_DOWN      : JDM::KeyCode::DOWN      = JTRUE; JRETURN &JDM::KeyCode::DOWN;

        JCASE SDLK_LEFT      :
            JDM::KeyCode::LEFT = JTRUE;
            JIF (JDM::Window::focusedTextComponent != JNULLPTR)
            {
                JDM::Window::focusedTextComponent->index--;
                JIF(JDM::Window::focusedTextComponent->index < -1)
                    JDM::Window::focusedTextComponent->index = -1;
            }
            JRETURN &JDM::KeyCode::LEFT;

        JCASE SDLK_RIGHT:
            JDM::KeyCode::RIGHT = JTRUE;
            JIF (JDM::Window::focusedTextComponent != JNULLPTR)
            {
                JDM::Window::focusedTextComponent->index++;
                JIF(JDM::Window::focusedTextComponent->index > JDM::Window::focusedTextComponent->getText().size() - 1)
                    JDM::Window::focusedTextComponent->index = JDM::Window::focusedTextComponent->getText().size() - 1;
            }
            JRETURN &JDM::KeyCode::RIGHT;

        JCASE SDLK_PERIOD : JDM::KeyCode::PERIOD   = JTRUE; JTHIS->_enterKey(".", ">" ); JRETURN &JDM::KeyCode::PERIOD;
        JCASE SDLK_COMMA  : JDM::KeyCode::COMMA    = JTRUE; JTHIS->_enterKey(",", "<" ); JRETURN &JDM::KeyCode::COMMA;
        JCASE SDLK_SLASH  : JDM::KeyCode::QUESTION = JTRUE; JTHIS->_enterKey("/", "?" ); JRETURN &JDM::KeyCode::QUESTION;
        JCASE SDLK_QUOTE  : JDM::KeyCode::QUESTION = JTRUE; JTHIS->_enterKey("'", "\""); JRETURN &JDM::KeyCode::QUESTION;
        JDEFAULT: JRETURN JNULLPTR;
    }
}

JCBOOL *JDM::Window::_keyBoardUp(SDL_KeyboardEvent &key)
{
    JTHIS->_isKeyDown = JFALSE;
    JSWITCH (key.keysym.sym)
    {
        JCASE SDLK_a         : JDM::KeyCode::A               = JFALSE; JRETURN &JDM::KeyCode::A;
        JCASE SDLK_b         : JDM::KeyCode::B               = JFALSE; JRETURN &JDM::KeyCode::B;
        JCASE SDLK_c         : JDM::KeyCode::C               = JFALSE; JRETURN &JDM::KeyCode::C;
        JCASE SDLK_d         : JDM::KeyCode::D               = JFALSE; JRETURN &JDM::KeyCode::D;
        JCASE SDLK_e         : JDM::KeyCode::E               = JFALSE; JRETURN &JDM::KeyCode::E;
        JCASE SDLK_f         : JDM::KeyCode::F               = JFALSE; JRETURN &JDM::KeyCode::F;
        JCASE SDLK_g         : JDM::KeyCode::G               = JFALSE; JRETURN &JDM::KeyCode::G;
        JCASE SDLK_h         : JDM::KeyCode::H               = JFALSE; JRETURN &JDM::KeyCode::H;
        JCASE SDLK_i         : JDM::KeyCode::I               = JFALSE; JRETURN &JDM::KeyCode::I;
        JCASE SDLK_j         : JDM::KeyCode::J               = JFALSE; JRETURN &JDM::KeyCode::J;
        JCASE SDLK_k         : JDM::KeyCode::K               = JFALSE; JRETURN &JDM::KeyCode::K;
        JCASE SDLK_l         : JDM::KeyCode::L               = JFALSE; JRETURN &JDM::KeyCode::L;
        JCASE SDLK_m         : JDM::KeyCode::M               = JFALSE; JRETURN &JDM::KeyCode::M;
        JCASE SDLK_n         : JDM::KeyCode::N               = JFALSE; JRETURN &JDM::KeyCode::N;
        JCASE SDLK_o         : JDM::KeyCode::O               = JFALSE; JRETURN &JDM::KeyCode::O;
        JCASE SDLK_p         : JDM::KeyCode::P               = JFALSE; JRETURN &JDM::KeyCode::P;
        JCASE SDLK_q         : JDM::KeyCode::Q               = JFALSE; JRETURN &JDM::KeyCode::Q;
        JCASE SDLK_r         : JDM::KeyCode::R               = JFALSE; JRETURN &JDM::KeyCode::R;
        JCASE SDLK_s         : JDM::KeyCode::S               = JFALSE; JRETURN &JDM::KeyCode::S;
        JCASE SDLK_t         : JDM::KeyCode::T               = JFALSE; JRETURN &JDM::KeyCode::T;
        JCASE SDLK_u         : JDM::KeyCode::U               = JFALSE; JRETURN &JDM::KeyCode::U;
        JCASE SDLK_v         : JDM::KeyCode::V               = JFALSE; JRETURN &JDM::KeyCode::V;
        JCASE SDLK_w         : JDM::KeyCode::W               = JFALSE; JRETURN &JDM::KeyCode::W;
        JCASE SDLK_x         : JDM::KeyCode::X               = JFALSE; JRETURN &JDM::KeyCode::X;
        JCASE SDLK_y         : JDM::KeyCode::Y               = JFALSE; JRETURN &JDM::KeyCode::Y;
        JCASE SDLK_z         : JDM::KeyCode::Z               = JFALSE; JRETURN &JDM::KeyCode::Z;
        JCASE SDLK_0         : JDM::KeyCode::N0              = JFALSE; JRETURN &JDM::KeyCode::N0;
        JCASE SDLK_1         : JDM::KeyCode::N1              = JFALSE; JRETURN &JDM::KeyCode::N1;
        JCASE SDLK_2         : JDM::KeyCode::N2              = JFALSE; JRETURN &JDM::KeyCode::N2;
        JCASE SDLK_3         : JDM::KeyCode::N3              = JFALSE; JRETURN &JDM::KeyCode::N3;
        JCASE SDLK_4         : JDM::KeyCode::N4              = JFALSE; JRETURN &JDM::KeyCode::N4;
        JCASE SDLK_5         : JDM::KeyCode::N5              = JFALSE; JRETURN &JDM::KeyCode::N5;
        JCASE SDLK_6         : JDM::KeyCode::N6              = JFALSE; JRETURN &JDM::KeyCode::N6;
        JCASE SDLK_7         : JDM::KeyCode::N7              = JFALSE; JRETURN &JDM::KeyCode::N7;
        JCASE SDLK_8         : JDM::KeyCode::N8              = JFALSE; JRETURN &JDM::KeyCode::N8;
        JCASE SDLK_9         : JDM::KeyCode::N9              = JFALSE; JRETURN &JDM::KeyCode::N9;
        JCASE SDLK_UP        : JDM::KeyCode::UP              = JFALSE; JRETURN &JDM::KeyCode::UP;
        JCASE SDLK_DOWN      : JDM::KeyCode::DOWN            = JFALSE; JRETURN &JDM::KeyCode::DOWN;
        JCASE SDLK_LEFT      : JDM::KeyCode::LEFT            = JFALSE; JRETURN &JDM::KeyCode::LEFT;
        JCASE SDLK_RIGHT     : JDM::KeyCode::RIGHT           = JFALSE; JRETURN &JDM::KeyCode::RIGHT;
        JCASE SDLK_PERIOD    : JDM::KeyCode::PERIOD          = JFALSE; JRETURN &JDM::KeyCode::PERIOD;
        JCASE SDLK_COMMA     : JDM::KeyCode::COMMA           = JFALSE; JRETURN &JDM::KeyCode::COMMA;
        JCASE SDLK_QUESTION  : JDM::KeyCode::QUESTION        = JFALSE; JRETURN &JDM::KeyCode::QUESTION;
        JCASE SDLK_QUOTE     : JDM::KeyCode::QOUTE           = JFALSE; JRETURN &JDM::KeyCode::QOUTE;
        JCASE SDLK_LSHIFT    : JDM::KeyCode::LEFT_SHIFT      = JFALSE; JRETURN &JDM::KeyCode::LEFT_SHIFT;
        JCASE SDLK_RSHIFT    : JDM::KeyCode::RIGHT_SHIFT     = JFALSE; JRETURN &JDM::KeyCode::RIGHT_SHIFT;
        JCASE SDLK_LCTRL     : JDM::KeyCode::LEFT_CONTROL    = JFALSE; JRETURN &JDM::KeyCode::LEFT_CONTROL;
        JCASE SDLK_RCTRL     : JDM::KeyCode::RIGHT_CONTROL   = JFALSE; JRETURN &JDM::KeyCode::RIGHT_CONTROL;
        JCASE SDLK_CAPSLOCK  : JDM::KeyCode::CAPSLOCK        = JFALSE; JRETURN &JDM::KeyCode::CAPSLOCK;
        JCASE SDLK_RETURN    : JDM::KeyCode::ENTER           = JFALSE; JRETURN &JDM::KeyCode::ENTER;
        JCASE SDLK_TAB       : JDM::KeyCode::TAB             = JFALSE; JRETURN &JDM::KeyCode::TAB;
        JCASE SDLK_BACKSPACE : JDM::KeyCode::BACKSPACE       = JFALSE; JRETURN &JDM::KeyCode::BACKSPACE;
        JCASE SDLK_SPACE     : JDM::KeyCode::SPACE           = JFALSE; JRETURN &JDM::KeyCode::SPACE;
        JCASE SDLK_EQUALS    : JDM::KeyCode::KPLUS           = JFALSE; JRETURN &JDM::KeyCode::KPLUS;
        JCASE SDLK_MINUS     : JDM::KeyCode::KMINUS          = JFALSE; JRETURN &JDM::KeyCode::KMINUS;
        JDEFAULT: JRETURN JNULLPTR;
    }
}

JCVOID JDM::Window::_enterKey(JCSTR &small, JCSTR &big)
{
    JIF (JDM::Window::focusedTextComponent != JNULLPTR)
    {
        JDM::Window::focusedTextComponent->setTextMessage(
            JDM::retAddCharAtIndex(JDM::Window::focusedTextComponent->getText(),
            JDM::Window::focusedTextComponent->index + 1,
            JDM::KeyCode::LEFT_SHIFT || JDM::KeyCode::RIGHT_SHIFT ? big : small));
        JDM::Window::focusedTextComponent->index += 1;
    }
}

JCVOID JDM::Window::_deletekey()
{
    JIF (JDM::Window::focusedTextComponent != JNULLPTR)
    {
        JDM::Window::focusedTextComponent->setTextMessage(
            JDM::retSubtractCharAtIndex(JDM::Window::focusedTextComponent->getText(),
            JDM::Window::focusedTextComponent->index));

        JDM::Window::focusedTextComponent->index -= 1;
        JIF(JDM::Window::focusedTextComponent->index < -1)
            JDM::Window::focusedTextComponent->index = -1;
    }
}

JCVOID JDM::Window::update         (             ) {}
JCVOID JDM::Window::initAllObjects (             ) {}
JCVOID JDM::Window::mouseDown      (             ) {}
JCVOID JDM::Window::mouseUp        (             ) {}
JCVOID JDM::Window::mouseMotion    (             ) {}
JCVOID JDM::Window::keyDown        (JCBOOL * Key ) {}
JCVOID JDM::Window::keyHold        (JCBOOL * Key ) {}
JCVOID JDM::Window::keyUp          (JCBOOL * Key ) {}

JCVOID JDM::Window::setTitle       (JCCHAR *title)
{
    SDL_SetWindowTitle(JTHIS->_window, title);
}

JCVOID JDM::Window::setIcon(JCCHAR *path)
{
    JTHIS->_iconSurface = IMG_Load( (JDM::isFileExist(path)) ? path : CircleImage.c_str());
    SDL_SetWindowIcon(JTHIS->_window, JTHIS->_iconSurface);
}

JCVOID JDM::Window::setCursor(JCCHAR *path)
{
    JTHIS->_isCursorChangeable = JTRUE;
    JIF (JDM::isFileExist(path))
    {
        JTHIS->_cursorTexture = IMG_LoadTexture(JDM::renderer, path);
        SDL_SetTextureScaleMode(JTHIS->_cursorTexture, SDL_ScaleModeLinear);
        SDL_SetTextureBlendMode(JTHIS->_cursorTexture, SDL_BLENDMODE_BLEND);
        SDL_ShowCursor         (SDL_DISABLE);
    }
    JELSE
    {
        JTHIS->_isCursorChangeable = JFALSE;
        SDL_ShowCursor(SDL_ENABLE);
    }
}

JCVOID JDM::Window::addComponents(JCONST JSP<JDM::Comp::Components> &comp, JUINT position)
{
    JDM::Window::_allHandlingComponents.push_back(JMPAIR(JMPAIR(comp, position), 'A'));
}

JCVOID JDM::Window::removeComponents(JCONST JSP<JDM::Comp::Components> &comp)
{
    JDM::Window::_allHandlingComponents.push_back(JMPAIR(JMPAIR(comp, 0), 'R'));
}

JCVOID JDM::Window::bringComponentsToBack(JCONST JSP<JDM::Comp::Components> &comp)
{
    JIF (std::find(JDM::Window::_allComponents.begin(), JDM::Window::_allComponents.end(), comp) != JDM::Window::_allComponents.end())
    {
        JDM::Window::_allHandlingComponents.push_back(JMPAIR(JMPAIR(comp, 0), 'R'));
        JDM::Window::_allHandlingComponents.push_back(JMPAIR(JMPAIR(comp, JDM::Window::_allComponents.size()-1), 'A'));
    }
}

JCVOID JDM::Window::bringComponentsToFront(JCONST JSP<JDM::Comp::Components> &comp)
{
    JIF (std::find(JDM::Window::_allComponents.begin(), JDM::Window::_allComponents.end(), comp) != JDM::Window::_allComponents.end())
    {
        JDM::Window::_allHandlingComponents.push_back(JMPAIR(JMPAIR(comp, 0), 'R'));
        JDM::Window::_allHandlingComponents.push_back(JMPAIR(JMPAIR(comp, 0), 'A'));
    }
}

JCVOID JDM::Window::bringComponentsUsingPosition(JCONST JSP<JDM::Comp::Components> &comp, JUINT position)
{
    JIF (std::find(JDM::Window::_allComponents.begin(), JDM::Window::_allComponents.end(), comp) != JDM::Window::_allComponents.end())
    {
        JDM::Window::_allHandlingComponents.push_back(JMPAIR(JMPAIR(comp, 0), 'R'));
        JDM::Window::_allHandlingComponents.push_back(JMPAIR(JMPAIR(comp, position), 'A'));
    }
}

JCVOID JDM::Window::_handleComponents()
{
    JFOR (JCONST JAUTO &handleComp: JDM::Window::_allHandlingComponents)
    {
        JSWITCH (handleComp.second)
        {
            JCASE 'R':
                JDM::Window::_allComponents.remove(handleComp.first.first);
                JBREAK;
            JCASE 'A':
                JIF (std::find(JDM::Window::_allComponents.begin(), JDM::Window::_allComponents.end(), handleComp.first.first) == JDM::Window::_allComponents.end())
                {
                    JAUTO it = JDM::Window::_allComponents.begin();
                    std::advance                       (it, handleComp.first.second);
                    JDM::Window::_allComponents.insert (it, handleComp.first.first);
                }
                JELSE
                    JDM::Logger(" > [ WARNING ]: The component (", handleComp.first.first, "-", handleComp.first.first->getName(), ") is already added.");

                JBREAK;
        }
    }
    JDM::Window::_allHandlingComponents.clear();
}

JCVOID JDM::Window::addClock(JCONST JSP<JDM::Clock> &timer)
{
    JDM::Window::_allClock.push_back(timer);
}

JCVOID JDM::Window::addStartClock(JCONST JSP<JDM::Clock> &timer)
{
    JDM::Window::_allClock.push_back(timer); timer->start();
}

JCVOID JDM::Window::removeClock(JCONST JSP<JDM::Clock> &timer)
{
    timer->reset();
    JDM::Window::_allClock.remove(timer);
}
