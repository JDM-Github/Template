#include "JDM/Header/JDMbaseComponents/JDMbaseImage.hpp"
#include "JDM/Header/JDMfunctions.hpp"
#include "JDM/Header/JDMinclude.hpp"
#include "JDM/Header/logger.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class BaseImage
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class BaseImage
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Public: Set Image Source (Change Image)
 * 
 * @param source 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::setImageSource(JCSTR &source)
{
    JIF (JTHIS->_sourceFiles == source)
        JRETURN;

    JTHIS->_sourceFiles            = ((JDM::isFileExist(source)) ? source : DefaultImage);
    JTHIS->_willUpdateImageTexture = JTRUE;
}

/**
 * @brief Public: Set Image Opacity and Color
 * 
 * @param color 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::setImageAndOpacityColor(JCONST JDM::ColorRGBA color)
{
    JIF (color.r != JTHIS->_imageColor.r
      || color.g != JTHIS->_imageColor.g
      || color.b != JTHIS->_imageColor.b
      || color.a != JTHIS->_imageColor.a)
    {
        JTHIS->_imageColor             = color;
        JTHIS->_willUpdateImageColor   = JTRUE;
        JTHIS->_willUpdateImageOpacity = JTRUE;
    }
}

/**
 * @brief Public: Set Image Color
 * 
 * @param color 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::setImageColor(JCONST JDM::ColorRGB color)
{
    JIF (color.r != JTHIS->_imageColor.r
      || color.g != JTHIS->_imageColor.g
      || color.b != JTHIS->_imageColor.b)
    {
        JTHIS->_imageColor.rgb       = color;
        JTHIS->_willUpdateImageColor = JTRUE;
    }
}

/**
 * @brief Public: Set Image Opacity
 * 
 * @param opacity 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::setImageOpacity(JCONST JUINT8 opacity)
{
    JIF (JTHIS->_imageColor.a != opacity)
    {
        JTHIS->_imageColor.a           = opacity;
        JTHIS->_willUpdateImageOpacity = JTRUE;
    }
}

/**
 * @brief Public: Set Image RGBA - R
 * 
 * @param rColor 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::setImageColorR(JUINT8 rColor)
{
    JIF (JTHIS->_imageColor.r != rColor)
    {
        JTHIS->_imageColor.r         = rColor;
        JTHIS->_willUpdateImageColor = JTRUE;
    }
}

/**
 * @brief Public: Set Image RGBA - G
 * 
 * @param gColor 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::setImageColorG(JUINT8 gColor)
{
    JIF (JTHIS->_imageColor.g != gColor)
    {
        JTHIS->_imageColor.g         = gColor;
        JTHIS->_willUpdateImageColor = JTRUE;
    }
}

/**
 * @brief Public: Set Image RGBA - B
 * 
 * @param bColor 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::setImageColorB(JUINT8 bColor)
{
    JIF (JTHIS->_imageColor.b != bColor)
    {
        JTHIS->_imageColor.b         = bColor;
        JTHIS->_willUpdateImageColor = JTRUE;
    }
}

/**
 * @brief Public: Set Image Four Arc (T-Left, T-Right, B-Left, B-Right)
 * 
 * @param arc 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::setImageFourArc(JCONST JDM::FourArc arc)
{
    JIF (!(arc.topLeft     != JTHIS->_arc.topLeft
      ||   arc.topRight    != JTHIS->_arc.topRight
      ||   arc.bottomLeft  != JTHIS->_arc.bottomLeft
      ||   arc.bottomRight != JTHIS->_arc.bottomRight))
        JRETURN;

    JTHIS->_arc                    = arc;
    JTHIS->_willUpdateImageTexture = JTRUE;
}

/**
 * @brief Public: Set Image Two Left and Right Arc (Left, Right)
 * 
 * @param arcLR 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::setImageTwoLRArc(JCONST JDM::TwoLRArc arcLR)
{
    JIF (!(arcLR.leftArc  != JTHIS->_arc.topLeft
      ||   arcLR.rightArc != JTHIS->_arc.topRight
      ||   arcLR.leftArc  != JTHIS->_arc.bottomLeft
      ||   arcLR.rightArc != JTHIS->_arc.bottomRight))
        JRETURN;

    JTHIS->_arc.topLeft            = JTHIS->_arc.bottomLeft  = arcLR.leftArc;
    JTHIS->_arc.topRight           = JTHIS->_arc.bottomRight = arcLR.rightArc;
    JTHIS->_willUpdateImageTexture = JTRUE;
}

/**
 * @brief Public: Set Image Two Top and Bottom Arc (Top, Bottom)
 * 
 * @param arcTB 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::setImageTwoTBArc(JCONST JDM::TwoTBArc arcTB)
{
    JIF (!(arcTB.topArc    != JTHIS->_arc.topLeft
      ||   arcTB.topArc    != JTHIS->_arc.topRight
      ||   arcTB.bottomArc != JTHIS->_arc.bottomLeft
      ||   arcTB.bottomArc != JTHIS->_arc.bottomRight))
        JRETURN;

    JTHIS->_arc.topLeft            = JTHIS->_arc.topRight    = arcTB.topArc;
    JTHIS->_arc.bottomLeft         = JTHIS->_arc.bottomRight = arcTB.bottomArc;
    JTHIS->_willUpdateImageTexture = JTRUE;
}

JCVOID JDM::Base::BaseImage::setImageLineWidth(JUINT8 lineWidth)
{
     JIF (JTHIS->_lineWidth != lineWidth)
     {
        JTHIS->_lineWidth = lineWidth;
        JTHIS->_willUpdateImageTexture = JTRUE;
     }
}

JCVOID JDM::Base::BaseImage::setWillUpdateImageColor(JCBOOL imageUpdate)
{
    JTHIS->_willUpdateImageColor = imageUpdate;
}

JCVOID JDM::Base::BaseImage::setImageRegion(JCONST JDM::Region region)
{
    JTHIS->_imageSource = { region.x, region.y, region.w, region.h };
}

/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::ColorRGBA JDM::Base::BaseImage::getImageAndOpacityColor() JCONST
{
    JRETURN JTHIS->_imageColor;
}

JDM::ColorRGB JDM::Base::BaseImage::getImageColor() JCONST
{
    JRETURN JTHIS->_imageColor.rgb;
}

JUINT8 JDM::Base::BaseImage::getImageOpacity() JCONST
{
    JRETURN JTHIS->_imageColor.a;
}
JUINT8 JDM::Base::BaseImage::getImageColorR() JCONST
{
    JRETURN JTHIS->_imageColor.r;
}

JUINT8 JDM::Base::BaseImage::getImageColorG() JCONST
{
    JRETURN JTHIS->_imageColor.g;
}

JUINT8 JDM::Base::BaseImage::getImageColorB() JCONST
{
    JRETURN JTHIS->_imageColor.b;
}

JDM::Region JDM::Base::BaseImage::getImageRegion() JCONST
{
    JRETURN { JTHIS->_imageSource.x, JTHIS->_imageSource.y, JTHIS->_imageSource.w, JTHIS->_imageSource.h };
}

JDM::RegionF JDM::Base::BaseImage::getImageDestination() JCONST
{
    JRETURN { JTHIS->_imageDestination.x, JTHIS->_imageDestination.y, JTHIS->_imageDestination.w, JTHIS->_imageDestination.h };
}

JDM::FourArc JDM::Base::BaseImage::getImageFourArc() JCONST
{
    JRETURN JTHIS->_arc;
}

JUINT8 JDM::Base::BaseImage::getImageLineWidth() JCONST
{
    JRETURN JTHIS->_lineWidth;
}

SDL_Texture *JDM::Base::BaseImage::getImageTexture()
{
    JRETURN JTHIS->_imageTexture;
}

JCSTR JDM::Base::BaseImage::getImageSource()
{
    JRETURN JTHIS->_sourceFiles;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PRIVATE SECTION: @class BaseImage
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Private: Set Image Rectangle Destination
 * 
 * @param posSize 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::_setImageRectDestination(JCONST JDM::PositionSize posSize)
{
    JTHIS->_imageDestination.w = posSize.width;
    JTHIS->_imageDestination.h = posSize.height;
    JTHIS->_imageDestination.x = posSize.x;
    JTHIS->_imageDestination.y = posSize.y;
}

/**
 * @brief Private: Set Image Texture
 * 
 * @param size
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::_setImageTexture(JCONST JDM::Size size)
{
    JTHIS->_willUpdateImageTexture = JFALSE;

    JTHIS->_imageTexture  = JDM::loadRoundedTexture(size, JTHIS->_sourceFiles.c_str(), JTHIS->_arc, JTHIS->_lineWidth);
    JTHIS->_imageSource.x = 0;
    JTHIS->_imageSource.y = 0;

    SDL_QueryTexture           (JTHIS->_imageTexture, NULL, NULL, &JTHIS->_imageSource.w, &JTHIS->_imageSource.h);
    SDL_SetTextureBlendMode    (JTHIS->_imageTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode    (JTHIS->_imageTexture, SDL_ScaleMode::SDL_ScaleModeLinear);

    JTHIS->_updateImageColor   ();
    JTHIS->_updateImageOpacity ();
}

/**
 * @brief Private: Update Image Color
 * 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::_updateImageColor()
{
    JTHIS->_willUpdateImageColor = JFALSE;
    SDL_SetTextureColorMod(JTHIS->_imageTexture, JTHIS->_imageColor.r, JTHIS->_imageColor.g, JTHIS->_imageColor.b);
}

/**
 * @brief Private: Update Image Opacity
 * 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::_updateImageOpacity()
{
    JTHIS->_willUpdateImageOpacity = JFALSE;
    SDL_SetTextureAlphaMod(JTHIS->_imageTexture, JTHIS->_imageColor.a);
}

/**
 * @brief Private: Update Image
 * 
 * @param posSize 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::_updateImage(JCONST JDM::PositionSize posSize)
{
    JTHIS->_setImageRectDestination(posSize);
    JIF(JTHIS->_willUpdateImageTexture)
        JTHIS->_setImageTexture(posSize.size);

    JIF(JTHIS->_willUpdateImageColor)
        JTHIS->_updateImageColor();

    JIF(JTHIS->_willUpdateImageOpacity)
        JTHIS->_updateImageOpacity();
}

/**
 * @brief Private: Render Image
 * 
 * @return JCVOID 
 */
JCVOID JDM::Base::BaseImage::_renderImage()
{
    SDL_RenderCopyF(JDM::renderer, JTHIS->_imageTexture, &JTHIS->_imageSource, &JTHIS->_imageDestination);
}

JCBOOL JDM::Base::BaseImage::_setObjectProperties(ImageProperties propertyName, JSP<JDM::Object> &object)
{
    JSWITCH (propertyName)
    {
        JCASE ImageProperties::SOURCE:
            JTHIS->setImageSource(JDM::getIfString(object));
            JRETURN JTRUE;

        JCASE ImageProperties::IMAGE_COLOR_R:
            JTHIS->setImageColorR(JDM::getUint8Limit(object));
            JRETURN JTRUE;

        JCASE ImageProperties::IMAGE_COLOR_G:
            JTHIS->setImageColorG(JDM::getUint8Limit(object));
            JRETURN JTRUE;

        JCASE ImageProperties::IMAGE_COLOR_B:
            JTHIS->setImageColorB(JDM::getUint8Limit(object));
            JRETURN JTRUE;

        JCASE ImageProperties::IMAGE_COLOR_A:
            JTHIS->setImageOpacity(JDM::getUint8Limit(object));
            JRETURN JTRUE;

        JCASE ImageProperties::IMAGE_COLOR_STR:
            JTHIS->setImageAndOpacityColor(JDM::getColorFromHexA(JDM::getIfString(object)));
            JRETURN JTRUE;

        JCASE ImageProperties::ARC_STR:
            JTHIS->setImageFourArc(JSTATICC<JDM::FourArc>(JDM::getColorFromHex(JDM::getIfString(object))));
            JRETURN JTRUE;

        JCASE ImageProperties::LINEWIDTH:
            JTHIS->setImageLineWidth(JDM::getIfInteger(object));
            JRETURN JTRUE;
    }
    JRETURN JFALSE;
}