#include "JDM/Header/JDMcomponents/JDMbutton.hpp"
#include "JDM/Header/JDMfunctions.hpp"
#include "JDM/Header/JDMinclude.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class Button
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class Button
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::Button::Button(
    JCSTR              &text,
    JCSTR              &source,
    JCDOUBLE            xPos,
    JCDOUBLE            yPos,
    JCDOUBLE            width,
    JCDOUBLE            height,
    JCONST ColorRGBA    color,
    JCONST ColorRGBA    colorImage,
    JCONST JDM::FourArc arc,
    JCINT               fontSize,
    JDM::Font::Halign   hAlign,
    JDM::Font::Valign   vAlign,
    JCONST ColorRGBA    colorClick,
    JCONST ColorRGBA    colorHover
) :
    JDM::Comp::Label(text, source, xPos, yPos, width, height, color, colorImage, arc, fontSize, hAlign, vAlign)
{
    JTHIS->setOriginalColor(colorImage);
    JTHIS->_clickedColor = colorClick;
    JTHIS->_hoverColor   = colorHover;
}

JCBOOL JDM::Comp::Button::mouseDownComp(SDL_MouseButtonEvent &mouse)
{
    JIF (JTHIS->getPickOnBounds())
    {
        JIF(JTHIS->getPickOnTop() && JDM::alreadyTouched)
            JRETURN JFALSE;

        JIF (JTHIS->contains(mouse.x, mouse.y))
        {
            JTHIS->getmouseDownFunction()  (mouse);
            JTHIS->setImageAndOpacityColor (JTHIS->_clickedColor);
            JTHIS->setMouseClick           (JTRUE);
            JDM::alreadyTouched = JTRUE;
            JRETURN JTRUE;
        }
    }
    JRETURN JFALSE;
}

JCVOID JDM::Comp::Button::setOriginalColor(JCONST ColorRGBA &color)
{
    JTHIS->_originalColor = color;
    JTHIS->setImageAndOpacityColor(JTHIS->_originalColor);
}

JCVOID JDM::Comp::Button::setClickedColor(JCONST ColorRGBA &color)
{
    JTHIS->_clickedColor = color;
}

JCVOID JDM::Comp::Button::setHoverColor(JCONST ColorRGBA &color)
{
    JTHIS->_hoverColor = color;
}

JCVOID JDM::Comp::Button::mouseUpComp(SDL_MouseButtonEvent &mouse)
{
    JIF (JTHIS->getMouseClick())
    {
        JIF (JTHIS->_isHoverable)
        {
            JIF (JTHIS->contains(JDM::Mouse::MouseX, JDM::Mouse::MouseY))
            {
                JTHIS->setImageAndOpacityColor(JTHIS->_hoverColor);
            }
            JELSE
                JTHIS->setImageAndOpacityColor(JTHIS->_originalColor);
        }
        JELSE
            JTHIS->setImageAndOpacityColor(JTHIS->_originalColor);
    }
    Label::mouseUpComp(mouse);
}

JCVOID JDM::Comp::Button::update()
{
    Label::update();
    JIF (JTHIS->getMouseClick())
        JRETURN;

    JIF (JTHIS->_isHoverable)
    {
        JIF (JTHIS->contains(JDM::Mouse::MouseX, JDM::Mouse::MouseY))
        {
            JTHIS->setImageAndOpacityColor(JTHIS->_hoverColor);
        }
        JELSE
            JTHIS->setImageAndOpacityColor(JTHIS->_originalColor);
    }
    JELSE
        JTHIS->setImageAndOpacityColor(JTHIS->_originalColor);
}

JCVOID JDM::Comp::Button::setIsHoverable(JCBOOL isHoverable)
{
    JTHIS->_isHoverable = isHoverable;
}

JCBOOL JDM::Comp::Button::getIsHoverable() JCONST
{
    JRETURN JTHIS->_isHoverable;
}