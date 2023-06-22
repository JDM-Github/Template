#pragma once
#ifndef JDM_COMP_TEXT_HPP
#define JDM_COMP_TEXT_HPP

#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMstructs.hpp"
#include "JDM/Header/JDMenum.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

#include "JDM/Header/JDMbaseComponents/JDMbaseGradient.hpp"
#include "JDM/Header/JDMbaseComponents/JDMbaseText.hpp"
#include "JDM/Header/JDMcomponents/JDMcomponent.hpp"

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

    }
}


#endif