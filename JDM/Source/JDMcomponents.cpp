#include "JDM/Header/JDMcomponents.hpp"



/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class BaseGradient
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JCVOID JDM::Comp::BaseGradient::setGradientAlignment(JCONST JDM::Gradient gradentAlignment)
{
    JTHIS->_gradientAlignment = gradentAlignment;
}

JCVOID JDM::Comp::BaseGradient::setGradientColor(JCONST ColorRGBA first, JCONST ColorRGBA second)
{
    JTHIS->_gradientStartColor = first;
    JTHIS->_gradientEndColor   = second;
}

JCONST JUINT8 JDM::Comp::BaseGradient::_interpolateColorComponent(JUINT8 startComponent, JUINT8 endComponent, JINT position, JINT length) JCONST
{
    JRETURN startComponent + ((endComponent - startComponent) * position) / length;
}

JCVOID JDM::Comp::BaseGradient::_renderGradient(JCONST JDM::PositionSize posSize)
{
    SDL_SetRenderDrawBlendMode (JDM::renderer, SDL_BLENDMODE_BLEND);
    JAUTO drawLine = [&](JCINT index, JCINT size, JCONST JDM::LinePoints &points) {

        JUINT8 r = JTHIS->_interpolateColorComponent (JTHIS->_gradientStartColor.r, JTHIS->_gradientEndColor.r, index, size);
        JUINT8 g = JTHIS->_interpolateColorComponent (JTHIS->_gradientStartColor.g, JTHIS->_gradientEndColor.g, index, size);
        JUINT8 b = JTHIS->_interpolateColorComponent (JTHIS->_gradientStartColor.b, JTHIS->_gradientEndColor.b, index, size);
        JUINT8 a = JTHIS->_interpolateColorComponent (JTHIS->_gradientStartColor.a, JTHIS->_gradientEndColor.a, index, size);

        SDL_SetRenderDrawColor     (JDM::renderer,         r,         g,         b,         a);
        SDL_RenderDrawLine         (JDM::renderer, points.x1, points.y1, points.x2, points.y2);
    };
    JSWITCH (JTHIS->_gradientAlignment)
    {
        JCASE JDM::GRADIENT_VERTICAL:
            JFOR (JINT y = 0; y < posSize.height; y++)
                drawLine(y, posSize.height, {posSize.x, posSize.y + y, posSize.x + posSize.width, posSize.y + y});
            JBREAK;
        JCASE JDM::GRADIENT_HORIZONTAL:
            JFOR (JINT x = 0; x < posSize.width; x++)
                drawLine(x, posSize.width, {posSize.x + x, posSize.y, posSize.x + x, posSize.y + posSize.y});
            JBREAK;
    };
    SDL_SetRenderDrawBlendMode (JDM::renderer, SDL_BLENDMODE_NONE);
}



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
JCVOID JDM::Comp::BaseImage::setImageSource(JCSTR &source)
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
JCVOID JDM::Comp::BaseImage::setImageAndOpacityColor(JCONST JDM::ColorRGBA color)
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
JCVOID JDM::Comp::BaseImage::setImageColor(JCONST JDM::ColorRGB color)
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
JCVOID JDM::Comp::BaseImage::setImageOpacity(JCONST JUINT8 opacity)
{
    JIF (JTHIS->_imageColor.a != opacity)
    {
        JTHIS->_imageColor.a           = opacity;
        JTHIS->_willUpdateImageColor   = JTRUE;
    }
}

/**
 * @brief Public: Set Image RGBA - R
 * 
 * @param rColor 
 * @return JCVOID 
 */
JCVOID JDM::Comp::BaseImage::setImageColorR(JUINT8 rColor)
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
JCVOID JDM::Comp::BaseImage::setImageColorG(JUINT8 gColor)
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
JCVOID JDM::Comp::BaseImage::setImageColorB(JUINT8 bColor)
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
JCVOID JDM::Comp::BaseImage::setImageFourArc(JCONST JDM::FourArc arc)
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
JCVOID JDM::Comp::BaseImage::setImageTwoLRArc(JCONST JDM::TwoLRArc arcLR)
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
JCVOID JDM::Comp::BaseImage::setImageTwoTBArc(JCONST JDM::TwoTBArc arcTB)
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

JCVOID JDM::Comp::BaseImage::setImageLineWidth(JUINT8 lineWidth)
{
     JIF (JTHIS->_lineWidth != lineWidth)
     {
        JTHIS->_lineWidth = lineWidth;
        JTHIS->_willUpdateImageTexture = JTRUE;
     }
}

JCVOID JDM::Comp::BaseImage::setWillUpdateImageColor(JCBOOL imageUpdate)
{
    JTHIS->_willUpdateImageColor = imageUpdate;
}

JCVOID JDM::Comp::BaseImage::setImageRegion(JCONST JDM::Region region)
{
    JTHIS->_imageSource = { region.x, region.y, region.w, region.h };
}

/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::ColorRGBA JDM::Comp::BaseImage::getImageAndOpacityColor() JCONST
{
    JRETURN JTHIS->_imageColor;
}

JDM::ColorRGB JDM::Comp::BaseImage::getImageColor() JCONST
{
    JRETURN JTHIS->_imageColor.rgb;
}

JUINT8 JDM::Comp::BaseImage::getImageOpacity() JCONST
{
    JRETURN JTHIS->_imageColor.a;
}
JUINT8 JDM::Comp::BaseImage::getImageColorR() JCONST
{
    JRETURN JTHIS->_imageColor.r;
}

JUINT8 JDM::Comp::BaseImage::getImageColorG() JCONST
{
    JRETURN JTHIS->_imageColor.g;
}

JUINT8 JDM::Comp::BaseImage::getImageColorB() JCONST
{
    JRETURN JTHIS->_imageColor.b;
}

JDM::Region JDM::Comp::BaseImage::getImageRegion() JCONST
{
    JRETURN { JTHIS->_imageSource.x, JTHIS->_imageSource.y, JTHIS->_imageSource.w, JTHIS->_imageSource.h };
}

JDM::RegionF JDM::Comp::BaseImage::getImageDestination() JCONST
{
    JRETURN { JTHIS->_imageDestination.x, JTHIS->_imageDestination.y, JTHIS->_imageDestination.w, JTHIS->_imageDestination.h };
}

JDM::FourArc JDM::Comp::BaseImage::getImageFourArc() JCONST
{
    JRETURN JTHIS->_arc;
}

JUINT8 JDM::Comp::BaseImage::getImageLineWidth() JCONST
{
    JRETURN JTHIS->_lineWidth;
}

SDL_Texture *JDM::Comp::BaseImage::getImageTexture()
{
    JRETURN JTHIS->_imageTexture;
}

JCSTR JDM::Comp::BaseImage::getImageSource()
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
JCVOID JDM::Comp::BaseImage::_setImageRectDestination(JCONST JDM::PositionSize posSize)
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
JCVOID JDM::Comp::BaseImage::_setImageTexture(JCONST JDM::Size size)
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
JCVOID JDM::Comp::BaseImage::_updateImageColor()
{
    JTHIS->_willUpdateImageColor = JFALSE;
    SDL_SetTextureColorMod(JTHIS->_imageTexture, JTHIS->_imageColor.r, JTHIS->_imageColor.g, JTHIS->_imageColor.b);
}

/**
 * @brief Private: Update Image Opacity
 * 
 * @return JCVOID 
 */
JCVOID JDM::Comp::BaseImage::_updateImageOpacity()
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
JCVOID JDM::Comp::BaseImage::_updateImage(JCONST JDM::PositionSize posSize)
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
JCVOID JDM::Comp::BaseImage::_renderImage()
{
    SDL_RenderCopyF(JDM::renderer, JTHIS->_imageTexture, &JTHIS->_imageSource, &JTHIS->_imageDestination);
}

JCBOOL JDM::Comp::BaseImage::_setObjectProperties(ImageProperties propertyName, JSP<JDM::Object> &object)
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


/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class BaseText
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class BaseText
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JCVOID JDM::Comp::BaseText::setTextMessage(JCSTR &text)
{
    JIF (JTHIS->_textMessage == text)
        JRETURN;

    JTHIS->_textMessage           = text;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Comp::BaseText::setTextAndOpacityColor(JCONST JDM::ColorRGBA color)
{
    JIF (color.r != JTHIS->_textColor.r
      || color.g != JTHIS->_textColor.g
      || color.b != JTHIS->_textColor.b
      || color.a != JTHIS->_textColor.a)
    {
        JTHIS->_textColor             = color;
        JTHIS->_willUpdateTextColor   = JTRUE;
        JTHIS->_willUpdateTextOpacity = JTRUE;
    }
}

JCVOID JDM::Comp::BaseText::setTextColor(JCONST JDM::ColorRGB color)
{
    JIF (color.r != JTHIS->_textColor.r
      || color.g != JTHIS->_textColor.g
      || color.b != JTHIS->_textColor.b)
    {
        JTHIS->_textColor.rgb       = color;
        JTHIS->_willUpdateTextColor = JTRUE;
    }
}

JCVOID JDM::Comp::BaseText::setTextOpacity(JCONST JUINT8 opacity) {
    JIF (JTHIS->_textColor.a != opacity)
    {
        JTHIS->_textColor.a = opacity;
        JTHIS->_willUpdateTextColor = JTRUE;
    }
}

JCVOID JDM::Comp::BaseText::setTextColorR(JUINT8 rColor)
{
    JIF (JTHIS->_textColor.r != rColor)
    {
        JTHIS->_textColor.r = rColor;
        JTHIS->_willUpdateTextColor = JTRUE;
    }
}

JCVOID JDM::Comp::BaseText::setTextColorG(JUINT8 gColor)
{
    JIF (JTHIS->_textColor.g != gColor)
    {
        JTHIS->_textColor.g = gColor;
        JTHIS->_willUpdateTextColor = JTRUE;
    }
}

JCVOID JDM::Comp::BaseText::setTextColorB(JUINT8 bColor)
{
    JIF (JTHIS->_textColor.b != bColor)
    {
        JTHIS->_textColor.b         = bColor;
        JTHIS->_willUpdateTextColor = JTRUE;
    }
}

JCVOID JDM::Comp::BaseText::setTextRegion(JCONST JDM::Region region)
{
    JTHIS->_textSource = { region.x, region.y, region.w, region.h };
}

JCVOID JDM::Comp::BaseText::setFontSize(JCUINT size)
{
    JTHIS->_fontSize = size;
}

JCVOID JDM::Comp::BaseText::setBold(JCBOOL bold)
{
    JIF (JTHIS->_isBold == bold)
        JRETURN;

    JTHIS->_isBold                = bold;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Comp::BaseText::setItalic(JCBOOL italic)
{
    JIF (JTHIS->_isItalic == italic)
        JRETURN;

    JTHIS->_isItalic              = italic;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Comp::BaseText::setFont(JCONST JDM::Font::Font font)
{
    JIF (!(JTHIS->_font.Normal     != font.Normal
       ||  JTHIS->_font.Bold       != font.Bold
       ||  JTHIS->_font.Italic     != font.Italic
       ||  JTHIS->_font.ItalicBold != font.ItalicBold))
        JRETURN;

    JTHIS->_font                  = font;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Comp::BaseText::setFontRegular(JCSTR &str)
{
    JIF (JTHIS->_font.Normal == str)
        JRETURN;

    JTHIS->_font.Normal           = str;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Comp::BaseText::setFontBold(JCSTR &str)
{
    JIF (JTHIS->_font.Bold == str)
        JRETURN;

    JTHIS->_font.Bold             = str;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Comp::BaseText::setFontItalic(JCSTR &str)
{
    JIF (JTHIS->_font.Italic == str)
        JRETURN;

    JTHIS->_font.Italic           = str;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Comp::BaseText::setFontBoldItalic(JCSTR &str)
{
    JIF (JTHIS->_font.ItalicBold == str)
        JRETURN;

    JTHIS->_font.ItalicBold       = str;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Comp::BaseText::setValign(JDM::Font::Valign valign)
{
    JTHIS->_valign = valign;
}

JCVOID JDM::Comp::BaseText::setHalign(JDM::Font::Halign halign)
{
    JTHIS->_halign = halign;
}

JCVOID JDM::Comp::BaseText::setPaddingWidth(JCDOUBLE padWidth)
{
    JTHIS->_paddingWidth = padWidth;
}

JCVOID JDM::Comp::BaseText::setPaddingHeight(JCDOUBLE padHeight)
{
    JTHIS->_paddingHeight = padHeight;
}

/////////////////////////////////////////////////////////////////////////////////////////////////


JCUINT JDM::Comp::BaseText::getFontSize() JCONST
{
    JRETURN JTHIS->_fontSize;
}

JCDOUBLE JDM::Comp::BaseText::getCopyFontSize() JCONST
{
    JRETURN JTHIS->_copyFontSize;
}

JCBOOL JDM::Comp::BaseText::getBold() JCONST
{
    JRETURN JTHIS->_isBold;
}

JCBOOL JDM::Comp::BaseText::getItalic() JCONST
{
    JRETURN JTHIS->_isItalic;
}

JDM::Font::Valign JDM::Comp::BaseText::getValign() JCONST
{
    JRETURN JTHIS->_valign;
}

JDM::Font::Halign JDM::Comp::BaseText::getHalign() JCONST
{
    JRETURN JTHIS->_halign;
}

JCDOUBLE JDM::Comp::BaseText::getPaddingWidth() JCONST
{
    JRETURN JTHIS->_paddingWidth;
}

JCDOUBLE JDM::Comp::BaseText::getPaddingHeight() JCONST
{
    JRETURN JTHIS->_paddingHeight;
}

JDM::ColorRGBA JDM::Comp::BaseText::getTextAndOpacityColor() JCONST
{
    JRETURN JTHIS->_textColor;
}

JDM::ColorRGB JDM::Comp::BaseText::getTextColor() JCONST
{
    JRETURN JTHIS->_textColor.rgb;
}

JUINT8 JDM::Comp::BaseText::getTextOpacity() JCONST
{
    JRETURN JTHIS->_textColor.a;
}

JUINT8 JDM::Comp::BaseText::getTextColorR() JCONST
{
    JRETURN JTHIS->_textColor.r;
}

JUINT8 JDM::Comp::BaseText::getTextColorG() JCONST
{
    JRETURN JTHIS->_textColor.g;
}

JUINT8 JDM::Comp::BaseText::getTextColorB() JCONST
{
    JRETURN JTHIS->_textColor.b;
}

JDM::Region JDM::Comp::BaseText::getTextRegion() JCONST
{
    JRETURN { JTHIS->_textSource.x, JTHIS->_textSource.y, JTHIS->_textSource.w, JTHIS->_textSource.h };
}

JDM::RegionF JDM::Comp::BaseText::getTextDestination() JCONST
{
    JRETURN { JTHIS->_textDestination.x, JTHIS->_textDestination.y, JTHIS->_textDestination.w, JTHIS->_textDestination.h };
}

SDL_Texture *JDM::Comp::BaseText::getTextTexture()
{
    JRETURN JTHIS->_textTexture;
}

JCSTR JDM::Comp::BaseText::getText()
{
    JRETURN JTHIS->_textMessage;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PRIVATE SECTION: @class BaseText
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JCVOID JDM::Comp::BaseText::_setTextRectDestination(JCONST JDM::PositionSize posSize)
{
    JTHIS->_textDestination.w = JSTATICC<JFLOAT>(JTHIS->_textMessage.length() * JTHIS->_fontSize);
    JIF (posSize.width - (JTHIS->_paddingWidth*2) < JTHIS->_textDestination.w)
    {
        JTHIS->_textDestination.w = (posSize.width - (JTHIS->_paddingWidth * 2));
        JTHIS->_copyFontSize = JTHIS->_textDestination.w / JTHIS->_textMessage.length();
    }
    JELSE
        JTHIS->_copyFontSize = JTHIS->_fontSize;

    JTHIS->_textDestination.h = JSTATICC<JFLOAT>(JTHIS->_copyFontSize + (JTHIS->_copyFontSize));

    JSWITCH (JTHIS->_halign)
    {
        JCASE JDM::Font::Halign::LEFT:
            JTHIS->_textDestination.x = posSize.x + JTHIS->_paddingWidth;
            JBREAK;
        JCASE JDM::Font::Halign::HCENTER:
            JTHIS->_textDestination.x = posSize.x + ((posSize.width - JTHIS->_textDestination.w) / 2.f);
            JBREAK;
        JCASE JDM::Font::Halign::RIGHT:
            JTHIS->_textDestination.x = posSize.x + (posSize.width - JTHIS->_textDestination.w) - JTHIS->_paddingWidth;
            JBREAK;
    }
    JSWITCH (JTHIS->_valign)
    {
        JCASE JDM::Font::Valign::TOP:
            JTHIS->_textDestination.y = posSize.y - JTHIS->_paddingHeight;
            JBREAK;
        JCASE JDM::Font::Valign::VCENTER:
            JTHIS->_textDestination.y = posSize.y + ((posSize.height - JTHIS->_textDestination.h) / 2.f);
            JBREAK;
        JCASE JDM::Font::Valign::BOTTOM:
            JTHIS->_textDestination.y = posSize.y + (posSize.height - JTHIS->_textDestination.h) + JTHIS->_paddingHeight;
            JBREAK;
    }
}

JCVOID JDM::Comp::BaseText::_setTextTexture()
{
   JTHIS->_textTexture = loadTextTexture(
        ((JTHIS->_isBold && JTHIS->_isItalic) ?     
            JTHIS->_font.ItalicBold    .c_str() : ((JTHIS->_isBold)   ? 
                JTHIS->_font.Bold      .c_str() : ((JTHIS->_isItalic) ?
                    JTHIS->_font.Italic.c_str() : JTHIS->_font.Normal.c_str()
                )
            )
        ),
        JTHIS->_textMessage.c_str(),
        JTHIS->_textColor
    );
    JTHIS->_textSource.x = 0;
    JTHIS->_textSource.y = 0;
    SDL_QueryTexture         (JTHIS->_textTexture, NULL, NULL, &JTHIS->_textSource.w, &JTHIS->_textSource.h);
    SDL_SetTextureBlendMode  (JTHIS->_textTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode  (JTHIS->_textTexture, SDL_ScaleMode::SDL_ScaleModeLinear);

    JTHIS->_updateTextColor   ();
    JTHIS->_updateTextOpacity ();
}

JCVOID JDM::Comp::BaseText::_updateTextColor()
{
    SDL_SetTextureColorMod(JTHIS->_textTexture, JTHIS->_textColor.r, JTHIS->_textColor.g, JTHIS->_textColor.b);
    JTHIS->_willUpdateTextColor = JFALSE;
}

JCVOID JDM::Comp::BaseText::_updateTextOpacity()
{
    SDL_SetTextureAlphaMod(JTHIS->_textTexture, JTHIS->_textColor.a);
    JTHIS->_willUpdateTextOpacity = JFALSE;
}

JCVOID JDM::Comp::BaseText::_updateText(JCONST JDM::PositionSize posSize)
{
    JTHIS->_setTextRectDestination(posSize);
    JIF(JTHIS->_willUpdateTextTexture)
        JTHIS->_setTextTexture();

    JIF(JTHIS->_willUpdateTextColor)
        JTHIS->_updateTextColor();

   JIF(JTHIS->_willUpdateTextOpacity)
    JTHIS->_updateTextOpacity();
}

JCVOID JDM::Comp::BaseText::_renderText()
{
    SDL_RenderCopyF(JDM::renderer, JTHIS->_textTexture, &JTHIS->_textSource, &JTHIS->_textDestination);
}

JCBOOL JDM::Comp::BaseText::_setObjectProperties(TextProperties propertyName, JSP<JDM::Object> &object)
{
    JSWITCH (propertyName)
    {
        JCASE TextProperties::BOLD:
            JTHIS->setBold(JDM::getIfBoolean(object));
            JRETURN JTRUE;

        JCASE TextProperties::ITALIC:
            JTHIS->setItalic(JDM::getIfBoolean(object));
            JRETURN JTRUE;

        JCASE TextProperties::TEXT:
            JTHIS->setTextMessage(JDM::getIfString(object));
            JRETURN JTRUE;

        JCASE TextProperties::TEXT_COLOR_R:
            JTHIS->setTextColorR(JDM::getUint8Limit(object));
            JRETURN JTRUE;

        JCASE TextProperties::TEXT_COLOR_G:
            JTHIS->setTextColorG(JDM::getUint8Limit(object));
            JRETURN JTRUE;

        JCASE TextProperties::TEXT_COLOR_B:
            JTHIS->setTextColorB(JDM::getUint8Limit(object));
            JRETURN JTRUE;

        JCASE TextProperties::TEXT_COLOR_A:
            JTHIS->setTextOpacity(JDM::getUint8Limit(object));
            JRETURN JTRUE;

        JCASE TextProperties::TEXT_COLOR_STR:
            JTHIS->setTextAndOpacityColor(JDM::getColorFromHexA(JDM::getIfString(object)));
            JRETURN JTRUE;

        JCASE TextProperties::VERTICAL_ALIGNMENT:
            JTHIS->setValign(JSTATICC<JDM::Font::Valign>(JDM::getNumberLimit(object, 0, 2)));
            JRETURN JTRUE;

        JCASE TextProperties::HORIZONTAL_ALIGNMENT:
            JTHIS->setHalign(JSTATICC<JDM::Font::Halign>(JDM::getNumberLimit(object, 0, 2)));
            JRETURN JTRUE;

        JCASE TextProperties::PADDING_WIDTH:
            JTHIS->setPaddingWidth(JDM::getObjectArithmetic(object));
            JRETURN JTRUE;

        JCASE TextProperties::PADDING_HEIGHT:
            JTHIS->setPaddingHeight(JDM::getObjectArithmetic(object));
            JRETURN JTRUE;
    }
    JRETURN JFALSE;
}


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
            JDM::Comp::BaseText::_setObjectProperties(JSTATICC<JDM::Comp::BaseText::TextProperties>(propertyName), object);
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
    JIF (IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight()))
    {
        JTHIS->_renderText();
    }
}



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
            JDM::Comp::BaseImage::_setObjectProperties(JSTATICC<JDM::Comp::BaseImage::ImageProperties>(propertyName), object);
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
            JIF(!JDM::Comp::BaseImage::_setObjectProperties(JSTATICC<JDM::Comp::BaseImage::ImageProperties>(propertyName), object))
                JDM::Comp::BaseText::_setObjectProperties(JSTATICC<JDM::Comp::BaseText::TextProperties>(propertyName), object);
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



/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class FocusedTextComponent
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class FocusedTextComponent
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::FocusedTextComponent::FocusedTextComponent(
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
    JDM::Comp::Label(text, source, xPos, yPos, width, height, color, colorImage, arc, fontSize, hAlign, vAlign)
{ }

JCSTR JDM::Comp::FocusedTextComponent::getName() JCONST
{
    JRETURN "FocusedTextComponent";
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class TextInput
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class TextInput
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::TextInput::TextInput(
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
    JDM::Comp::FocusedTextComponent(text, source, xPos, yPos, width, height, color, colorImage, arc, fontSize, hAlign, vAlign)
{ }

JCVOID JDM::Comp::TextInput::setCursorColor(JCONST ColorRGBA color)
{
    JTHIS->_colorCursor = color;
}

JCVOID JDM::Comp::TextInput::renderComp()
{
    JIF (IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight()))
    {
        Label::renderComp();
        JTHIS->_currentBlink -= JDM::TimeFrame;

        JIF (JTHIS->isFocused)
        {
            JIF (JTHIS->_currentBlink > 0)
            {
                JIF (JTHIS->_blinked)
                {
                    SDL_SetRenderDrawColor(JDM::renderer, JTHIS->_colorCursor.r, JTHIS->_colorCursor.g, JTHIS->_colorCursor.b, JTHIS->_colorCursor.a);
                    SDL_RenderDrawLineF   (JDM::renderer,
                        JTHIS->getTextDestination().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()), JTHIS->getTextDestination().y + 15,
                        JTHIS->getTextDestination().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()), JTHIS->getTextDestination().y + JTHIS->getCopyFontSize() + 5);

                    SDL_RenderDrawLineF(JDM::renderer,
                        JTHIS->getTextDestination().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()) + 1, JTHIS->getTextDestination().y,
                        JTHIS->getTextDestination().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()) + 1, JTHIS->getTextDestination().y + JTHIS->getCopyFontSize() + 5);
                }
            }
            JELSE
            {
                JTHIS->_currentBlink = JTHIS->_blinkDuration;
                JTHIS->_blinked = !JTHIS->_blinked;
            }
        }
    }
}

