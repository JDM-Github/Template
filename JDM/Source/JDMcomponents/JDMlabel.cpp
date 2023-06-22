#include "JDM/Header/JDMcomponents/JDMlabel.hpp"
#include "JDM/Header/JDMfunctions.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class Label
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class Label
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::Label::Label(
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
    JDM::Font::Valign   vAlign
) :
    JDM::Comp::Components(xPos, yPos, width, height)
{
    JTHIS->setTextMessage (text  );
    JTHIS->setImageSource (source);
    JTHIS->_textColor  = color;
    JTHIS->_imageColor = colorImage;
    JTHIS->_arc        = arc;
    JTHIS->_fontSize   = fontSize;
    JTHIS->_halign     = hAlign;
    JTHIS->_valign     = vAlign;
    JTHIS->_setTextTexture  ();
    JTHIS->_setImageTexture (JTHIS->getSize());
}

JDM::Comp::Label::Label(
    JMAP<Properties, JSP<JDM::Object>> mapComponent
)
{
    JFOR (JAUTO [propertyName, object]: mapComponent)
    {
        JIF(!JDM::Comp::Components::setObjectProperties(JSTATICC<JDM::Comp::Components::Properties>(propertyName), object))
            JIF(!JDM::Base::BaseImage::_setObjectProperties(JSTATICC<JDM::Base::BaseImage::ImageProperties>(propertyName), object))
                JDM::Base::BaseText::_setObjectProperties(JSTATICC<JDM::Base::BaseText::TextProperties>(propertyName), object);
    }
    JTHIS->_setTextTexture();
    JTHIS->setImageSource  (JTHIS->getImageSource());
    JTHIS->_setImageTexture(JTHIS->getSize());
}

JUINT8 *JDM::Comp::Label::getPointerRText()
{
    JRETURN &JTHIS->_textColor.r;
}

JUINT8 *JDM::Comp::Label::getPointerGText()
{
    JRETURN &JTHIS->_textColor.g;
}

JUINT8 *JDM::Comp::Label::getPointerBText()
{
    JRETURN &JTHIS->_textColor.b;
}

JUINT8 *JDM::Comp::Label::getPointerAText()
{
    JRETURN &JTHIS->_textColor.a;
}

JUINT8 *JDM::Comp::Label::getPointerRImage()
{
    JRETURN &JTHIS->_imageColor.r;
}

JUINT8 *JDM::Comp::Label::getPointerGImage()
{
    JRETURN &JTHIS->_imageColor.g;
}

JUINT8 *JDM::Comp::Label::getPointerBImage()
{
    JRETURN &JTHIS->_imageColor.b;
}

JUINT8 *JDM::Comp::Label::getPointerAImage()
{
    JRETURN &JTHIS->_imageColor.a;
}

JCVOID JDM::Comp::Label::update()
{
    JTHIS->_updateImage (JTHIS->getSizePos());
    JTHIS->_updateText  (JTHIS->getSizePos());
}

JCVOID JDM::Comp::Label::renderComp()
{
    JIF (JDM::IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight()))
    {
        JTHIS->_renderImage    ();
        JTHIS->_renderGradient (JTHIS->getSizePos());
        JTHIS->_renderText     ();
    }
}

JCSTR JDM::Comp::Label::getName() JCONST
{
    JRETURN "Label";
}