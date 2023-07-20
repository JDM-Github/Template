#include "JDM/Header/JDMbaseComponents/JDMbaseText.hpp"
#include "JDM/Header/JDMfunctions.hpp"
#include "JDM/Header/JDMinclude.hpp"

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

JCVOID JDM::Base::BaseText::setTextMessage(JCSTR &text)
{
    JIF (JTHIS->_textMessage == text)
        JRETURN;

    JTHIS->_textMessage           = text;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Base::BaseText::setTextAndOpacityColor(JCONST JDM::ColorRGBA color)
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

JCVOID JDM::Base::BaseText::setTextColor(JCONST JDM::ColorRGB color)
{
    JIF (color.r != JTHIS->_textColor.r
      || color.g != JTHIS->_textColor.g
      || color.b != JTHIS->_textColor.b)
    {
        JTHIS->_textColor.rgb       = color;
        JTHIS->_willUpdateTextColor = JTRUE;
    }
}

JCVOID JDM::Base::BaseText::setTextOpacity(JCONST JUINT8 opacity) {
    JIF (JTHIS->_textColor.a != opacity)
    {
        JTHIS->_textColor.a = opacity;
        JTHIS->_willUpdateTextOpacity = JTRUE;
    }
}

JCVOID JDM::Base::BaseText::setTextColorR(JUINT8 rColor)
{
    JIF (JTHIS->_textColor.r != rColor)
    {
        JTHIS->_textColor.r = rColor;
        JTHIS->_willUpdateTextColor = JTRUE;
    }
}

JCVOID JDM::Base::BaseText::setTextColorG(JUINT8 gColor)
{
    JIF (JTHIS->_textColor.g != gColor)
    {
        JTHIS->_textColor.g = gColor;
        JTHIS->_willUpdateTextColor = JTRUE;
    }
}

JCVOID JDM::Base::BaseText::setTextColorB(JUINT8 bColor)
{
    JIF (JTHIS->_textColor.b != bColor)
    {
        JTHIS->_textColor.b         = bColor;
        JTHIS->_willUpdateTextColor = JTRUE;
    }
}

JCVOID JDM::Base::BaseText::setTextRegion(JCONST JDM::Region region)
{
    JTHIS->_textSource = { region.x, region.y, region.w, region.h };
}

JCVOID JDM::Base::BaseText::setFontSize(JCUINT size)
{
    JTHIS->_fontSize = size;
}

JCVOID JDM::Base::BaseText::setBold(JCBOOL bold)
{
    JIF (JTHIS->_isBold == bold)
        JRETURN;

    JTHIS->_isBold                = bold;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Base::BaseText::setItalic(JCBOOL italic)
{
    JIF (JTHIS->_isItalic == italic)
        JRETURN;

    JTHIS->_isItalic              = italic;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Base::BaseText::setFont(JCONST JDM::Font::Font font)
{
    JIF (!(JTHIS->_font.Normal     != font.Normal
       ||  JTHIS->_font.Bold       != font.Bold
       ||  JTHIS->_font.Italic     != font.Italic
       ||  JTHIS->_font.ItalicBold != font.ItalicBold))
        JRETURN;

    JTHIS->_font                  = font;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Base::BaseText::setFontRegular(JCSTR &str)
{
    JIF (JTHIS->_font.Normal == str)
        JRETURN;

    JTHIS->_font.Normal           = str;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Base::BaseText::setFontBold(JCSTR &str)
{
    JIF (JTHIS->_font.Bold == str)
        JRETURN;

    JTHIS->_font.Bold             = str;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Base::BaseText::setFontItalic(JCSTR &str)
{
    JIF (JTHIS->_font.Italic == str)
        JRETURN;

    JTHIS->_font.Italic           = str;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Base::BaseText::setFontBoldItalic(JCSTR &str)
{
    JIF (JTHIS->_font.ItalicBold == str)
        JRETURN;

    JTHIS->_font.ItalicBold       = str;
    JTHIS->_willUpdateTextTexture = JTRUE;
}

JCVOID JDM::Base::BaseText::setValign(JDM::Font::Valign valign)
{
    JTHIS->_valign = valign;
}

JCVOID JDM::Base::BaseText::setHalign(JDM::Font::Halign halign)
{
    JTHIS->_halign = halign;
}

JCVOID JDM::Base::BaseText::setPaddingWidth(JCDOUBLE padWidth)
{
    JTHIS->_paddingWidth = padWidth;
}

JCVOID JDM::Base::BaseText::setPaddingHeight(JCDOUBLE padHeight)
{
    JTHIS->_paddingHeight = padHeight;
}

/////////////////////////////////////////////////////////////////////////////////////////////////


JCUINT JDM::Base::BaseText::getFontSize() JCONST
{
    JRETURN JTHIS->_fontSize;
}

JCDOUBLE JDM::Base::BaseText::getCopyFontSize() JCONST
{
    JRETURN JTHIS->_copyFontSize;
}

JCBOOL JDM::Base::BaseText::getBold() JCONST
{
    JRETURN JTHIS->_isBold;
}

JCBOOL JDM::Base::BaseText::getItalic() JCONST
{
    JRETURN JTHIS->_isItalic;
}

JDM::Font::Valign JDM::Base::BaseText::getValign() JCONST
{
    JRETURN JTHIS->_valign;
}

JDM::Font::Halign JDM::Base::BaseText::getHalign() JCONST
{
    JRETURN JTHIS->_halign;
}

JCDOUBLE JDM::Base::BaseText::getPaddingWidth() JCONST
{
    JRETURN JTHIS->_paddingWidth;
}

JCDOUBLE JDM::Base::BaseText::getPaddingHeight() JCONST
{
    JRETURN JTHIS->_paddingHeight;
}

JDM::ColorRGBA JDM::Base::BaseText::getTextAndOpacityColor() JCONST
{
    JRETURN JTHIS->_textColor;
}

JDM::ColorRGB JDM::Base::BaseText::getTextColor() JCONST
{
    JRETURN JTHIS->_textColor.rgb;
}

JUINT8 JDM::Base::BaseText::getTextOpacity() JCONST
{
    JRETURN JTHIS->_textColor.a;
}

JUINT8 JDM::Base::BaseText::getTextColorR() JCONST
{
    JRETURN JTHIS->_textColor.r;
}

JUINT8 JDM::Base::BaseText::getTextColorG() JCONST
{
    JRETURN JTHIS->_textColor.g;
}

JUINT8 JDM::Base::BaseText::getTextColorB() JCONST
{
    JRETURN JTHIS->_textColor.b;
}

JDM::Region JDM::Base::BaseText::getTextRegion() JCONST
{
    JRETURN { JTHIS->_textSource.x, JTHIS->_textSource.y, JTHIS->_textSource.w, JTHIS->_textSource.h };
}

JDM::RegionF JDM::Base::BaseText::getTextDestination() JCONST
{
    JRETURN { JTHIS->_textDestination.x, JTHIS->_textDestination.y, JTHIS->_textDestination.w, JTHIS->_textDestination.h };
}

SDL_Texture *JDM::Base::BaseText::getTextTexture()
{
    JRETURN JTHIS->_textTexture;
}

JCSTR JDM::Base::BaseText::getText()
{
    JRETURN JTHIS->_textMessage;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PRIVATE SECTION: @class BaseText
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JCVOID JDM::Base::BaseText::_setTextRectDestination(JCONST JDM::PositionSize posSize)
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

JCVOID JDM::Base::BaseText::_setTextTexture()
{
    JTHIS->_willUpdateTextTexture = JFALSE;

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

JCVOID JDM::Base::BaseText::_updateTextColor()
{
    SDL_SetTextureColorMod(JTHIS->_textTexture, JTHIS->_textColor.r, JTHIS->_textColor.g, JTHIS->_textColor.b);
    JTHIS->_willUpdateTextColor = JFALSE;
}

JCVOID JDM::Base::BaseText::_updateTextOpacity()
{
    SDL_SetTextureAlphaMod(JTHIS->_textTexture, JTHIS->_textColor.a);
    JTHIS->_willUpdateTextOpacity = JFALSE;
}

JCVOID JDM::Base::BaseText::_updateText(JCONST JDM::PositionSize posSize)
{
    JTHIS->_setTextRectDestination(posSize);
    JIF(JTHIS->_willUpdateTextTexture)
        JTHIS->_setTextTexture();

    JIF(JTHIS->_willUpdateTextColor)
        JTHIS->_updateTextColor();

    JIF(JTHIS->_willUpdateTextOpacity)
        JTHIS->_updateTextOpacity();
}

JCVOID JDM::Base::BaseText::_renderText()
{
    SDL_RenderCopyF(JDM::renderer, JTHIS->_textTexture, &JTHIS->_textSource, &JTHIS->_textDestination);
}

JCBOOL JDM::Base::BaseText::_setObjectProperties(TextProperties propertyName, JSP<JDM::Object> &object)
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