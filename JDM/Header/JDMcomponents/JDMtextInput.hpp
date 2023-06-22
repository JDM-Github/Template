#pragma once
#ifndef JDM_COMP_TEXTINPUT_HPP
#define JDM_COMP_TEXTINPUT_HPP

#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMstructs.hpp"
#include "JDM/Header/JDMenum.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

#include "JDM/Header/JDMcomponents/JDMfocusedText.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Comp
    {
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