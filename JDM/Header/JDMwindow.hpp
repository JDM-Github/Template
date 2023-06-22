#pragma once
#ifndef JDM_WINDOW_HPP
#define JDM_WINDOW_HPP

#include "JDMinclude.hpp"
#include "JDMfunctions.hpp"
#include "JDManimation.hpp"
#include "JDMstructs.hpp"
#include "JDMcomponents/JDMcomponent.hpp"
#include "JDMcomponents/JDMfocusedText.hpp"
#include "JDMkeycodes.hpp"
#include "logger.hpp"


JNAMESPACE JDM
{
    JCLASS Window
    {
    JPUBLIC:
        JSTATIC Comp::FocusedTextComponent *focusedTextComponent;

    JPUBLIC:
        JCVOID          run            (            );
        JVIRTUAL JCVOID update         (            );
        JVIRTUAL JCVOID initAllObjects (            );
        JVIRTUAL JCVOID mouseDown      (            );
        JVIRTUAL JCVOID mouseUp        (            );
        JVIRTUAL JCVOID mouseMotion    (            );
        JVIRTUAL JCVOID keyDown        (JCBOOL* Key );
        JVIRTUAL JCVOID keyHold        (JCBOOL* Key );
        JVIRTUAL JCVOID keyUp          (JCBOOL* Key );
        JCVOID          setTitle       (JCCHARP title);
        JCVOID          setIcon        (JCCHARP path);
        JCVOID          setCursor      (JCCHARP path);

        Window(
            JSTRVIEW            title       = "Window",
            JCONST PositionSize posSize     = {0x0a, 0x0a, 0x1f4, 0x1f4},
            JCONST ColorRGB     windowColor = {0x00, 0x00, 0x00}
        );
        ~Window();

    JPUBLIC:
        JTEMPLATE <JCLASS T>
        JINLINE JSTATIC JCVOID addComponents(JUINT position = 0)
        {
            static_assert(std::is_base_of<JDM::Comp::Components, T>(), "NOPE");
            JDM::Window::_allHandlingComponents.push_back(JMPAIR(JMPAIR(JMS<T>(), position), 'A'));
        }

        JSTATIC JCVOID addComponents                (JCONST JSP<Comp::Components>& comp, JUINT position = 0);
        JSTATIC JCVOID removeComponents             (JCONST JSP<Comp::Components>& comp                    );
        JSTATIC JCVOID bringComponentsToFront       (JCONST JSP<Comp::Components>& comp                    );
        JSTATIC JCVOID bringComponentsToBack        (JCONST JSP<Comp::Components>& comp                    );
        JSTATIC JCVOID bringComponentsUsingPosition (JCONST JSP<Comp::Components>& comp, JUINT position = 0);
        JSTATIC JCVOID addClock                     (JCONST JSP<Clock>& timer                              );
        JSTATIC JCVOID addStartClock                (JCONST JSP<Clock>& timer                              );
        JSTATIC JCVOID removeClock                  (JCONST JSP<Clock>& timer                              );

        JTEMPLATE<JCLASS T>
        JINLINE JSTATIC JCVOID addAnimation(JCONST JSP<Animation<T>>& anim)
        {
            JDM::Window::_allAnimations.push_back(anim);
        }

        JTEMPLATE<JCLASS T>
        JINLINE JSTATIC JCVOID addStartAnimation(JCONST JSP<Animation<T>>& anim)
        {
            anim->start(); JDM::Window::_allAnimations.push_back(anim);
        }

        JTEMPLATE<JCLASS T>
        JINLINE JSTATIC JCVOID removeAnimation(JCONST JSP<Animation<T>>& anim)
        {
            anim->cancel(); JDM::Window::_allAnimations.remove(anim);
        }

    JPRIVATE:
        ColorRGB     _winColor           = {0x00, 0x00, 0x00};
        PositionSize _positionSize       = {0x0a, 0x0a, 0x1f4, 0x1f4};
        JBOOL        _started            = JFALSE;
        JBOOL        _isKeyDown          = JFALSE;
        JBOOL        _isCursorChangeable = JFALSE;
        JSTR         _title              = JEMPTYSTRING;

        SDL_bool     _running            = SDL_TRUE;
        SDL_Window  *_window             = JNULLPTR;
        SDL_Event    _event;

        SDL_Surface *_iconSurface        = JNULLPTR;
        SDL_Texture *_cursorTexture      = JNULLPTR;
        SDL_Rect     _cursorRect         = {0x00, 0x00, 0x00, 0x00};

        JUINT32      _firstTime          = 0x00;
        JUINT32      _prevTime           = 0x00;
        JUINT32      _secondTime         = 0x00;

        JSTATIC JLIST<JPAIR<JPAIR<JSP<JDM::Comp::Components>, JUINT>, JCHAR>> _allHandlingComponents;
        JSTATIC JLIST<JSP<AnimationBase>>                                     _allAnimations;
        JSTATIC JLIST<JSP<Clock>>                                             _allClock;
        JSTATIC JLIST<JSP<Comp::Components>>                                  _allComponents;

    JPRIVATE:
        JCVOID  _handleError             (                                       );
        JCBOOL  _initializeAll           (                                       );
        JCBOOL  _createWindow            (                                       );
        JCBOOL  _createRenderer          (                                       );
        
        JCVOID  _animationUpdate         (                                       );
        JCVOID  _winUpdate               (                                       );
        JCVOID  _winRender               (                                       );
        JCVOID  _handleComponents        (                                       );
        JCVOID  _pollEvent               (                                       );

        JCVOID  _mouseWinDown            (SDL_MouseButtonEvent& mouse            );
        JCVOID  _mouseWinUp              (SDL_MouseButtonEvent& mouse            );
        JCVOID  _mouseWinMotion          (SDL_MouseMotionEvent& mouse            );
        JCBOOL *_keyBoardDown            (SDL_KeyboardEvent& key                 );
        JCBOOL *_keyBoardUp              (SDL_KeyboardEvent& key                 );

        JCVOID  _enterKey                (JCSTR& small, JCSTR& big               );
        JCVOID  _deletekey               (                                       );
        JCVOID  _setFocusedTextComponent (Comp::FocusedTextComponent* focusedText);
    };
}

#endif