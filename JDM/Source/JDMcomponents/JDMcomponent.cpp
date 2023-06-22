#include "JDM/Header/JDMcomponents/JDMcomponent.hpp"
#include "JDM/Header/JDMfunctions.hpp"
#include "JDM/Header/JDMinclude.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class Components
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class Components
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::Components::Components(
    JCDOUBLE xPos,
    JCDOUBLE yPos,
    JCDOUBLE width,
    JCDOUBLE height
) :
    _sizePos({xPos, yPos, width, height})
{ }

JDM::Comp::Components::Components(
    JMAP<Properties, JSP<JDM::Object>> mapComponent
)
{
    JFOR (JAUTO [propertyName, object]: mapComponent)
        JTHIS->setObjectProperties(propertyName, object);
}

JCBOOL JDM::Comp::Components::setObjectProperties(Properties propertyName, JSP<JDM::Object> &object)
{
    JSWITCH (propertyName)
    {
        JCASE Properties::X:
            JTHIS->setX(JDM::getObjectArithmetic(object));
            JRETURN JTRUE;

        JCASE Properties::Y:
            JTHIS->setY(JDM::getObjectArithmetic(object));
            JRETURN JTRUE;

        JCASE Properties::WIDTH:
            JTHIS->setWidth(JDM::getObjectArithmetic(object));
            JRETURN JTRUE;

        JCASE Properties::HEIGHT:
            JTHIS->setHeight(JDM::getObjectArithmetic(object));
            JRETURN JTRUE;

        JCASE Properties::DISABLED:
            JTHIS->setDisabled(JDM::getIfBoolean(object));
            JRETURN JTRUE;

        JCASE Properties::PICK_ON_BOUNDS:
            JTHIS->setPickOnBounds(JDM::getIfBoolean(object));
            JRETURN JTRUE;

        JCASE Properties::WILL_RENDER:
            JTHIS->setRendering(JDM::getIfBoolean(object));
            JRETURN JTRUE;
    }
    JRETURN JFALSE;
}

JCBOOL JDM::Comp::Components::contains(JCDOUBLE xPos, JCDOUBLE yPos) JCONST
{
    JRETURN ((JTHIS->getX() <= xPos && (JTHIS->getX() + JTHIS->getWidth()) >= xPos)
          && (JTHIS->getY() <= yPos && (JTHIS->getY() + JTHIS->getHeight()) >= yPos));
}

JCVOID JDM::Comp::Components::setSizePos(JCONST JDM::PositionSize sPos)
{
    JTHIS->_sizePos = sPos;
}

JCVOID JDM::Comp::Components::setPos(JCONST JDM::Position pos)
{
    JTHIS->_sizePos.pos = pos;
}

JCVOID JDM::Comp::Components::setSize(JCONST JDM::Size size)
{
    JTHIS->_sizePos.size = size;
}

JCVOID JDM::Comp::Components::setX(JCDOUBLE xPos)
{
    JTHIS->_sizePos.x = xPos;
}

JCVOID JDM::Comp::Components::setY(JCDOUBLE yPos)
{
    JTHIS->_sizePos.y = yPos;
}

JCVOID JDM::Comp::Components::setWidth(JCDOUBLE Width)
{
    JTHIS->_sizePos.width = Width;
}

JCVOID JDM::Comp::Components::setHeight(JCDOUBLE Height)
{
    JTHIS->_sizePos.height = Height;
}

JCVOID JDM::Comp::Components::setDisabled(JCBOOL disabled)
{
    JTHIS->_disabled = disabled;
}

JCVOID JDM::Comp::Components::setPickOnBounds(JCBOOL bounds)
{
    JTHIS->_pickOnBounds = bounds;
}

JCVOID JDM::Comp::Components::setPickOnTop(JCBOOL top)
{
    JTHIS->_pickOnTop = top;
}

JCVOID JDM::Comp::Components::setRendering(JCBOOL isRendering)
{
    JTHIS->_stopRendering = !isRendering;
}

JCVOID JDM::Comp::Components::setUpdateFunction(JCONST JFUNCCALL function)
{
    JTHIS->_updateFunction = function;
}

JCVOID JDM::Comp::Components::setmouseDownFunction(JCONST JFUNCTION<JCVOID(SDL_MouseButtonEvent& mouse)> function)
{
    JTHIS->_mouseDownFunction = function;
}

JCVOID JDM::Comp::Components::setmouseMotionFunction(JCONST JFUNCTION<JCVOID(SDL_MouseMotionEvent& mouse)> function)
{
    JTHIS->_mouseMotionFunction = function;
}

JCVOID JDM::Comp::Components::setmouseUpFunction(JCONST JFUNCTION<JCVOID(SDL_MouseButtonEvent& mouse)> function)
{
    JTHIS->_mouseUpFunction = function;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

JCONST JDM::PositionSize JDM::Comp::Components::getSizePos() JCONST
{
    JRETURN JTHIS->_sizePos;
}

JCONST JDM::Position JDM::Comp::Components::getPos() JCONST
{
    JRETURN JTHIS->_sizePos.pos;
}

JCONST JDM::Size JDM::Comp::Components::getSize() JCONST
{
    JRETURN JTHIS->_sizePos.size;
}

JCDOUBLE JDM::Comp::Components::getX() JCONST
{
    JRETURN JTHIS->_sizePos.x;
}

JCDOUBLE JDM::Comp::Components::getY() JCONST
{
    JRETURN JTHIS->_sizePos.y;
}

JCDOUBLE JDM::Comp::Components::getWidth() JCONST
{
    JRETURN JTHIS->_sizePos.width;
}

JCDOUBLE JDM::Comp::Components::getHeight() JCONST
{
    JRETURN JTHIS->_sizePos.height;
}

JCBOOL JDM::Comp::Components::getDisabled() JCONST
{
    JRETURN JTHIS->_disabled;
}

JCBOOL JDM::Comp::Components::getRendering() JCONST
{
    JRETURN !JTHIS->_stopRendering;
}

JCBOOL JDM::Comp::Components::getPickOnBounds() JCONST
{
    JRETURN JTHIS->_pickOnBounds;
}

JCBOOL JDM::Comp::Components::getPickOnTop() JCONST
{
    JRETURN JTHIS->_pickOnTop;
}

JCBOOL JDM::Comp::Components::getMouseClick() JCONST
{
    JRETURN JTHIS->_mouseClicked;
}

JCSTR JDM::Comp::Components::getName() JCONST
{
    JRETURN "Components";
}

JDOUBLE *JDM::Comp::Components::getPointerX()
{
    JRETURN &JTHIS->_sizePos.x;
}

JDOUBLE *JDM::Comp::Components::getPointerY()
{
    JRETURN &JTHIS->_sizePos.y;
}

JDOUBLE *JDM::Comp::Components::getPointerWidth()
{
    JRETURN &JTHIS->_sizePos.width;
}

JDOUBLE *JDM::Comp::Components::getPointerHeight()
{
    JRETURN &JTHIS->_sizePos.height;
}

JUINT8 *JDM::Comp::Components::getPointerRImage()
{
    JRETURN JNULLPTR;
}

JUINT8 *JDM::Comp::Components::getPointerGImage()
{
    JRETURN JNULLPTR;
}

JUINT8 *JDM::Comp::Components::getPointerBImage()
{
    JRETURN JNULLPTR;
}

JUINT8 *JDM::Comp::Components::getPointerAImage()
{
    JRETURN JNULLPTR;
}

JUINT8 *JDM::Comp::Components::getPointerRText()
{
    JRETURN JNULLPTR;
}

JUINT8 *JDM::Comp::Components::getPointerGText()
{
    JRETURN JNULLPTR;
}

JUINT8 *JDM::Comp::Components::getPointerBText()
{
    JRETURN JNULLPTR;
}

JUINT8 *JDM::Comp::Components::getPointerAText()
{
    JRETURN JNULLPTR;
}

JCONST JFUNCCALL JDM::Comp::Components::getUpdateFunction() JCONST
{
    JRETURN JTHIS->_updateFunction;
}

JCONST JFUNCTION<JVOID(SDL_MouseButtonEvent& mouse)> JDM::Comp::Components::getmouseDownFunction() JCONST
{
    JRETURN JTHIS->_mouseDownFunction;
}

JCONST JFUNCTION<JVOID(SDL_MouseMotionEvent& mouse)> JDM::Comp::Components::getmouseMotionFunction() JCONST
{
    JRETURN JTHIS->_mouseMotionFunction;
}

JCONST JFUNCTION<JVOID(SDL_MouseButtonEvent& mouse)> JDM::Comp::Components::getmouseUpFunction() JCONST
{
    JRETURN JTHIS->_mouseUpFunction;
}

JCVOID JDM::Comp::Components::updateComp()
{
    JTHIS->update();
    JTHIS->_updateFunction();
}

JCBOOL JDM::Comp::Components::mouseDownComp(SDL_MouseButtonEvent &mouse)
{
    JIF (JTHIS->_pickOnBounds)
    {
        JIF (JTHIS->_pickOnTop && JDM::alreadyTouched)
            JRETURN JFALSE;

        JIF (JTHIS->contains(mouse.x, mouse.y))
        {
            JTHIS->_mouseDownFunction(mouse);
            JTHIS->_mouseClicked = JTRUE;
            JDM::alreadyTouched  = JTRUE;
            JRETURN JTRUE;
        }
    }
    JRETURN JFALSE;
}

JCVOID JDM::Comp::Components::mouseMotionComp(SDL_MouseMotionEvent &mouse)
{
    JIF (JTHIS->_mouseClicked)
        JTHIS->_mouseMotionFunction(mouse);
}

JCVOID JDM::Comp::Components::mouseUpComp(SDL_MouseButtonEvent &mouse)
{
    JIF (JTHIS->_mouseClicked)
    {
        JTHIS->_mouseClicked = JFALSE;
        JTHIS->_mouseUpFunction(mouse);
    }
}

JCVOID JDM::Comp::Components::setMouseClick(JCBOOL set)
{
    JTHIS->_mouseClicked = set; 
}
