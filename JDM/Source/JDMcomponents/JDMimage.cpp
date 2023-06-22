#include "JDM/Header/JDMcomponents/JDMimage.hpp"
#include "JDM/Header/JDMfunctions.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class Image
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class Image
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::Image::Image(
    JCSTR                &source,
    JCDOUBLE              xPos,
    JCDOUBLE              yPos,
    JCDOUBLE              width,
    JCDOUBLE              height,
    JCONST JDM::ColorRGBA color,
    JCONST FourArc        arc
) :
    JDM::Comp::Components(xPos, yPos, width, height)
{
    JTHIS->setImageSource (source);
    JTHIS->_imageColor = color;
    JTHIS->_arc        = arc;
    JTHIS->_setImageTexture (JTHIS->getSize());
}

JDM::Comp::Image::Image(
    JMAP<Properties, JSP<JDM::Object>> mapComponent
)
{
    JFOR (JAUTO [propertyName, object]: mapComponent)
    {
        JIF(!JDM::Comp::Components::setObjectProperties(JSTATICC<JDM::Comp::Components::Properties>(propertyName), object))
            JDM::Base::BaseImage::_setObjectProperties(JSTATICC<JDM::Base::BaseImage::ImageProperties>(propertyName), object);
    }
    JTHIS->setImageSource  (JTHIS->getImageSource());
    JTHIS->_setImageTexture(JTHIS->getSize());
}

JUINT8 *JDM::Comp::Image::getPointerRImage()
{
    JRETURN &JTHIS->_imageColor.r;
}

JUINT8 *JDM::Comp::Image::getPointerGImage()
{
    JRETURN &JTHIS->_imageColor.g;
}

JUINT8 *JDM::Comp::Image::getPointerBImage()
{
    JRETURN &JTHIS->_imageColor.b;
}

JUINT8 *JDM::Comp::Image::getPointerAImage()
{
    JRETURN &JTHIS->_imageColor.a;
}

JCSTR JDM::Comp::Image::getName() JCONST
{
    JRETURN "Image";
}

JCVOID JDM::Comp::Image::update()
{
    JTHIS->_updateImage(JTHIS->getSizePos());
}

JCVOID JDM::Comp::Image::renderComp()
{
    JIF (JDM::IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight()))
    {
        JTHIS->_renderImage    ();
        JTHIS->_renderGradient (JTHIS->getSizePos());
    }
}