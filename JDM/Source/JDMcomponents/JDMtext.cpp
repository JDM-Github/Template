#include "JDM/Header/JDMcomponents/JDMtext.hpp"
#include "JDM/Header/JDMfunctions.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class Text
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class Text
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::Text::Text(
    JCSTR                &text,
    JCDOUBLE              xPos,
    JCDOUBLE              yPos,
    JCDOUBLE              width,
    JCDOUBLE              height,
    JCONST JDM::ColorRGBA color,
    JCINT                 fontSize,
    JDM::Font::Halign     hAlign,
    JDM::Font::Valign     vAlign
) :
    JDM::Comp::Components(xPos, yPos, width, height)
{
    JTHIS->setTextMessage(text);
    JTHIS->_textColor = color;
    JTHIS->_fontSize  = fontSize;
    JTHIS->_halign    = hAlign;
    JTHIS->_valign    = vAlign;
    JTHIS->_setTextTexture();
}

JDM::Comp::Text::Text(
    JMAP<Properties, JSP<JDM::Object>> mapComponent
)
{
    JFOR (JAUTO [propertyName, object]: mapComponent)
    {
        JIF(!JDM::Comp::Components::setObjectProperties(JSTATICC<JDM::Comp::Components::Properties>(propertyName), object))
            JDM::Base::BaseText::_setObjectProperties(JSTATICC<JDM::Base::BaseText::TextProperties>(propertyName), object);
    }
    JTHIS->_setTextTexture();
}

JUINT8 *JDM::Comp::Text::getPointerRText()
{
    JRETURN &JTHIS->_textColor.r;
}

JUINT8 *JDM::Comp::Text::getPointerGText()
{
    JRETURN &JTHIS->_textColor.g;
}

JUINT8 *JDM::Comp::Text::getPointerBText()
{
    JRETURN &JTHIS->_textColor.b;
}

JUINT8 *JDM::Comp::Text::getPointerAText()
{
    JRETURN &JTHIS->_textColor.a;
}

JCSTR JDM::Comp::Text::getName() JCONST
{
    JRETURN "Text";
}

JCVOID JDM::Comp::Text::update()
{
    JTHIS->_updateText(JTHIS->getSizePos());
}

JCVOID JDM::Comp::Text::renderComp()
{
    JIF (JDM::IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight()))
    {
        JTHIS->_renderText();
    }
}
