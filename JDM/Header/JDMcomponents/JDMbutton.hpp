#pragma once
#ifndef JDM_COMP_IMAGE_HPP
#define JDM_COMP_IMAGE_HPP

#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMstructs.hpp"
#include "JDM/Header/JDMenum.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

#include "JDM/Header/JDMcomponents/JDMlabel.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Comp
    {
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
    }
}


#endif