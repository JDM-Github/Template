#pragma once
#ifndef JDM_COMPONENTS_HPP
#define JDM_COMPONENTS_HPP
#include "JDMinclude.hpp"
#include "JDMfonts.hpp"
#include "logger.hpp"
#include "JDMstructs.hpp"
#include "JDMenum.hpp"
#include "JDMfunctions.hpp"
#include "JDMobjects/JDMobjInc.hpp"

#include "JDMbaseComponents/JDMbaseGradient.hpp"
#include "JDMbaseComponents/JDMbaseImage.hpp"
#include "JDMbaseComponents/JDMbaseText.hpp"

#include "JDMcomponents/JDMcomponent.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Comp
    {
        JCLASS Text : JPUBLIC JDM::Comp::Components, JPUBLIC JDM::Base::BaseText
        {
        JPUBLIC:
            JENUM Properties
            {
                X                     = 0x00,
                Y                     = 0x01,
                WIDTH                 = 0x02,
                HEIGHT                = 0x03,
                DISABLED              = 0x04,
                PICK_ON_BOUNDS        = 0x05,
                WILL_RENDER           = 0x06,
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
            JUINT8        *getPointerRText () JOVERRIDE;
            JUINT8        *getPointerGText () JOVERRIDE;
            JUINT8        *getPointerBText () JOVERRIDE;
            JUINT8        *getPointerAText () JOVERRIDE;

            JCVOID         update          () JOVERRIDE;
            JCVOID         renderComp      () JOVERRIDE;

            JVIRTUAL JCSTR getName         () JCONST;

            Text(
                JCSTR                   &text     = JEMPTYSTRING,
                JCDOUBLE                 xPos     = 0x00,
                JCDOUBLE                 yPos     = 0x00,
                JCDOUBLE                 width    = 0x64,
                JCDOUBLE                 height   = 0x64,
                JCONST JDM::ColorRGBA    color    = {0xff, 0xff, 0xff, 0xff},
                JCINT                    fontSize = 0x0f,
                JCONST JDM::Font::Halign hAlign   = JDM::Font::HCENTER,
                JCONST JDM::Font::Valign vAlign   = JDM::Font::VCENTER
            );
            Text(
                JMAP<Properties, JSP<JDM::Object>> mapComponent);
        };

        JCLASS Image : JPUBLIC JDM::Comp::Components, JPUBLIC JDM::Base::BaseGradient, JPUBLIC JDM::Base::BaseImage
        {
        JPUBLIC:
            JENUM Properties
            {
                X                     = 0x00,
                Y                     = 0x01,
                WIDTH                 = 0x02,
                HEIGHT                = 0x03,
                DISABLED              = 0x04,
                PICK_ON_BOUNDS        = 0x05,
                WILL_RENDER           = 0x06,
                SOURCE                = 0x14,
                IMAGE_COLOR_R         = 0x15,
                IMAGE_COLOR_G         = 0x16,
                IMAGE_COLOR_B         = 0x17,
                IMAGE_COLOR_A         = 0x18,
                IMAGE_COLOR_STR       = 0x19,
                ARC_STR               = 0x1A,
                LINEWIDTH             = 0x1B
            };

        JPUBLIC:
            JUINT8        *getPointerRImage () JOVERRIDE;
            JUINT8        *getPointerGImage () JOVERRIDE;
            JUINT8        *getPointerBImage () JOVERRIDE;
            JUINT8        *getPointerAImage () JOVERRIDE;

            JCVOID         update           () JOVERRIDE;
            JCVOID         renderComp       () JOVERRIDE;

            JVIRTUAL JCSTR getName          () JCONST;

            Image(
                JCSTR                &source   = DefaultImage,
                JCDOUBLE              xPos     = 0x00,
                JCDOUBLE              yPos     = 0x00,
                JCDOUBLE              width    = 0x64,
                JCDOUBLE              height   = 0x64,
                JCONST JDM::ColorRGBA color    = {0xff, 0xff, 0xff, 0xff},
                JCONST FourArc        arc      = {0x00, 0x00, 0x00, 0x00}
            );

            Image(
                JMAP<Properties, JSP<JDM::Object>> mapComponent
            );
        };

        JCLASS Label : JPUBLIC JDM::Comp::Components, JPUBLIC JDM::Base::BaseImage, JPUBLIC JDM::Base::BaseText, JPUBLIC JDM::Base::BaseGradient
        {
        JPUBLIC:
            JENUM Properties
            {
                X                     = 0x00,
                Y                     = 0x01,
                WIDTH                 = 0x02,
                HEIGHT                = 0x03,
                DISABLED              = 0x04,
                PICK_ON_BOUNDS        = 0x05,
                WILL_RENDER           = 0x06,
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
                PADDING_HEIGHT        = 0x13,
                SOURCE                = 0x14,
                IMAGE_COLOR_R         = 0x15,
                IMAGE_COLOR_G         = 0x16,
                IMAGE_COLOR_B         = 0x17,
                IMAGE_COLOR_A         = 0x18,
                IMAGE_COLOR_STR       = 0x19,
                ARC_STR               = 0x1A,
                LINEWIDTH             = 0x1B
            };

        JPUBLIC:
            JUINT8        *getPointerRText  () JOVERRIDE;
            JUINT8        *getPointerGText  () JOVERRIDE;
            JUINT8        *getPointerBText  () JOVERRIDE;
            JUINT8        *getPointerAText  () JOVERRIDE;
            JUINT8        *getPointerRImage () JOVERRIDE;
            JUINT8        *getPointerGImage () JOVERRIDE;
            JUINT8        *getPointerBImage () JOVERRIDE;
            JUINT8        *getPointerAImage () JOVERRIDE;

            JCVOID         update           () JOVERRIDE;
            JCVOID         renderComp       () JOVERRIDE;

            JVIRTUAL JCSTR getName          () JCONST;

            Label(
                JCSTR                   &text       = JEMPTYSTRING,
                JCSTR                   &source     = DefaultImage,
                JCDOUBLE                 xPos       = 0x00,
                JCDOUBLE                 yPos       = 0x00,
                JCDOUBLE                 width      = 0x64,
                JCDOUBLE                 height     = 0x64,
                JCONST JDM::ColorRGBA    color      = {0x00, 0x00, 0x00, 0xff},
                JCONST JDM::ColorRGBA    colorImage = {0xff, 0xff, 0xff, 0xff},
                JCONST FourArc           arc        = {0x00, 0x00, 0x00, 0x00},
                JCINT                    fontSize   = 0x0f,
                JCONST JDM::Font::Halign hAlign     = JDM::Font::HCENTER,
                JCONST JDM::Font::Valign vAlign     = JDM::Font::VCENTER
            );
            Label(
                JMAP<Properties, JSP<JDM::Object>> mapComponent
            );
        };

        JCLASS Button : JPUBLIC Label
        {
        JPUBLIC:
            JCVOID setOriginalColor (JCONST ColorRGBA &color    );
            JCVOID setClickedColor  (JCONST ColorRGBA &color    );
            JCVOID setHoverColor    (JCONST ColorRGBA &color    );
            JCVOID setIsHoverable   (JCBOOL isHoverable         );
            JCVOID mouseUpComp      (SDL_MouseButtonEvent &mouse) JOVERRIDE;
            JCVOID update           (                           ) JOVERRIDE;
            JCBOOL mouseDownComp    (SDL_MouseButtonEvent &mouse) JOVERRIDE;
            JCBOOL getIsHoverable   (                           ) JCONST;

            Button(
                JCSTR                   &text       = JEMPTYSTRING,
                JCSTR                   &source     = DefaultImage,
                JCDOUBLE                 xPos       = 0x00,
                JCDOUBLE                 yPos       = 0x00,
                JCDOUBLE                 width      = 0x64,
                JCDOUBLE                 height     = 0x64,
                JCONST JDM::ColorRGBA    color      = {0x00, 0x00, 0x00, 0x00},
                JCONST JDM::ColorRGBA    colorImage = {0xff, 0xff, 0xff, 0xff},
                JCONST FourArc           arc        = {0x00, 0x00, 0x00, 0x00},
                JCINT                    fontSize   = 0x0f,
                JCONST JDM::Font::Halign hAlign     = JDM::Font::HCENTER,
                JCONST JDM::Font::Valign vAlign     = JDM::Font::VCENTER,
                JCONST ColorRGBA         colorClick = {0x32, 0x32, 0x32, 0xff},
                JCONST ColorRGBA         colorHover = {0xff, 0xff, 0xff, 0xff}
            );

        JPRIVATE:
            ColorRGBA _originalColor = {0x64, 0x64, 0x64, 0xff};
            ColorRGBA _clickedColor  = {0x32, 0x32, 0x32, 0xff};
            ColorRGBA _hoverColor    = {0xff, 0xff, 0xff, 0xff};

            JBOOL     _clicked       = JFALSE;
            JBOOL     _isHoverable   = JFALSE;
        };

        JCLASS FocusedTextComponent : JPUBLIC Label
        {
        JPUBLIC:
            JBOOL     isFocused     = JFALSE;
            JINT      index         = -1;
            JFUNCCALL functionEnter = []() {};
        
        JPUBLIC:
            JCSTR getName() JCONST JOVERRIDE;

        JPROTECTED:
            FocusedTextComponent(
                JCSTR                   &text       = JEMPTYSTRING,
                JCSTR                   &source     = DefaultImage,
                JCDOUBLE                 xPos       = 0x00,
                JCDOUBLE                 yPos       = 0x00,
                JCDOUBLE                 width      = 0x64,
                JCDOUBLE                 height     = 0x64,
                JCONST JDM::ColorRGBA    color      = {0x11, 0x11, 0x11, 0x11},
                JCONST JDM::ColorRGBA    colorImage = {0xcc, 0xcc, 0xcc, 0xcc},
                JCONST FourArc           arc        = {0x1e, 0x1e, 0x1e, 0x1e},
                JCINT                    fontSize   = 0x0f,
                JCONST JDM::Font::Halign hAlign     = JDM::Font::LEFT,
                JCONST JDM::Font::Valign vAlign     = JDM::Font::VCENTER
            );
        
        };

        JCLASS TextInput : JPUBLIC FocusedTextComponent
        {
        JPUBLIC:
            JCVOID setCursorColor(JCONST ColorRGBA color);
            JCVOID renderComp    (                      ) JOVERRIDE;

            TextInput(
                JCSTR                   &text       = JEMPTYSTRING,
                JCSTR                   &source     = DefaultImage,
                JCDOUBLE                 xPos       = 0x00,
                JCDOUBLE                 yPos       = 0x00,
                JCDOUBLE                 width      = 0x64,
                JCDOUBLE                 height     = 0x64,
                JCONST JDM::ColorRGBA    color      = {0x11, 0x11, 0x11, 0x11},
                JCONST JDM::ColorRGBA    colorImage = {0xcc, 0xcc, 0xcc, 0xcc},
                JCONST FourArc           arc        = {0x1e, 0x1e, 0x1e, 0x1e},
                JCINT                    fontSize   = 0x0f,
                JCONST JDM::Font::Halign hAlign     = JDM::Font::LEFT,
                JCONST JDM::Font::Valign vAlign     = JDM::Font::VCENTER
            );            

        JPRIVATE:
            JBOOL     _blinked       = JFALSE;
            JDOUBLE   _blinkDuration = 0.3;
            JDOUBLE   _currentBlink  = _blinkDuration;
            ColorRGBA _colorCursor   = {0xb4, 0xb4, 0xb4, 0xff};
        };
    }
}

#endif