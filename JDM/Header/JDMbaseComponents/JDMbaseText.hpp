#pragma once
#ifndef JDM_BASE_TEXT_HPP
#define JDM_BASE_TEXT_HPP

#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMstructs.hpp"
#include "JDM/Header/JDMenum.hpp"
#include "JDM/Header/JDMfonts.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Base
    {
        JCLASS BaseText
        {
        JPUBLIC:
            JENUM TextProperties
            {
                BOLD                  = 0x07,
                ITALIC                = 0x08,
                TEXT                  = 0x09,
                TEXT_COLOR_R          = 0x0A,
                TEXT_COLOR_G          = 0x0B,
                TEXT_COLOR_B          = 0x0C,
                TEXT_COLOR_A          = 0x0D,
                TEXT_COLOR_STR        = 0x0E,
                FONT_SIZE             = 0x0F,
                VERTICAL_ALIGNMENT    = 0x10,
                HORIZONTAL_ALIGNMENT  = 0x11,
                PADDING_WIDTH         = 0x12,
                PADDING_HEIGHT        = 0x13
            };

        JPUBLIC:
            JINLINE ~BaseText()
            {
                SDL_DestroyTexture(JTHIS->_textTexture);
            }

        JPUBLIC:
            JCVOID            setTextMessage         (JCSTR &text                );
            JCVOID            setTextAndOpacityColor (JCONST JDM::ColorRGBA color);
            JCVOID            setTextColor           (JCONST JDM::ColorRGB color );
            JCVOID            setTextOpacity         (JCONST JUINT8 opacity      );
            JCVOID            setTextColorR          (JUINT8 rColor              );
            JCVOID            setTextColorG          (JUINT8 gColor              );
            JCVOID            setTextColorB          (JUINT8 bColor              );
            JCVOID            setTextRegion          (JCONST JDM::Region region  );
            JCVOID            setFontSize            (JCUINT size                );
            JCVOID            setBold                (JCBOOL bold                );
            JCVOID            setItalic              (JCBOOL italic              );
            JCVOID            setFont                (JCONST JDM::Font::Font font);
            JCVOID            setFontRegular         (JCSTR &str                 );
            JCVOID            setFontBold            (JCSTR &str                 );
            JCVOID            setFontItalic          (JCSTR &str                 );
            JCVOID            setFontBoldItalic      (JCSTR &str                 );
            JCVOID            setValign              (JDM::Font::Valign valign   );
            JCVOID            setHalign              (JDM::Font::Halign halign   );
            JCVOID            setPaddingWidth        (JCDOUBLE padWidth          );
            JCVOID            setPaddingHeight       (JCDOUBLE padHeight         );

            JCUINT            getFontSize            () JCONST;
            JCDOUBLE          getCopyFontSize        () JCONST;
            JCBOOL            getBold                () JCONST;
            JCBOOL            getItalic              () JCONST;
            JDM::Font::Valign getValign              () JCONST;
            JDM::Font::Halign getHalign              () JCONST;
            JCDOUBLE          getPaddingWidth        () JCONST;
            JCDOUBLE          getPaddingHeight       () JCONST;
            JDM::ColorRGBA    getTextAndOpacityColor () JCONST;
            JDM::ColorRGB     getTextColor           () JCONST;
            JUINT8            getTextOpacity         () JCONST;
            JUINT8            getTextColorR          () JCONST;
            JUINT8            getTextColorG          () JCONST;
            JUINT8            getTextColorB          () JCONST;
            Region            getTextRegion          () JCONST;
            RegionF           getTextDestination     () JCONST;
            SDL_Texture      *getTextTexture         ();
            JCSTR             getText                ();
        
        JPROTECTED:
            JINLINE BaseText() {}

        JPROTECTED:
            JBOOL             _willUpdateTextTexture = JFALSE;   
            JBOOL             _willUpdateTextColor   = JFALSE;     
            JBOOL             _willUpdateTextOpacity = JFALSE;

            JBOOL             _isBold                = JFALSE;
            JBOOL             _isItalic              = JFALSE;

            JSTR              _textMessage           = JEMPTYSTRING;
            ColorRGBA         _textColor             = {0xff, 0xff, 0xff, 0xff};
            SDL_Rect          _textSource            = {0x00, 0x00, 0x00, 0x00}; 
            SDL_FRect         _textDestination       = {0x00, 0x00, 0x00, 0x00};
            SDL_Texture      *_textTexture           = JNULLPTR;

            JUINT             _fontSize              = 0x0f;
            JDOUBLE           _copyFontSize          = 0x0f;

            JDM::Font::Valign _valign                = JDM::Font::Valign::VCENTER;
            JDM::Font::Halign _halign                = JDM::Font::Halign::HCENTER;
            JDM::Font::Font   _font                  = JDM::Font::Consolas(); 

            JDOUBLE           _paddingWidth          = JNONE;
            JDOUBLE           _paddingHeight         = JNONE;

        JPROTECTED:
            JCVOID _setTextRectDestination (JCONST JDM::PositionSize posSize                     );
            JCVOID _updateText             (JCONST JDM::PositionSize posSize                     );
            JCVOID _setTextTexture         (                                                     );
            JCVOID _updateTextColor        (                                                     );
            JCVOID _updateTextOpacity      (                                                     );
            JCVOID _renderText             (                                                     );
            JCBOOL _setObjectProperties    (TextProperties propertyName, JSP<JDM::Object> &object);
        };
    }
}

#endif