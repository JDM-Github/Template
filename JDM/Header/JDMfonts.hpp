#pragma once
#ifndef JDM_FONTS_HPP
#define JDM_FONTS_HPP
#include "defines.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Font
    {
        JENUM AvailableFont
        {
            NONE,
            CONSOLAS
        };
        JENUM Valign
        {
            TOP,
            VCENTER,
            BOTTOM
        };

        JENUM Halign
        {
            LEFT,
            HCENTER,
            RIGHT
        };

        JSTRUCT Font
        {
            JSTR Normal, Italic, Bold, ItalicBold;
        };

        JSTRUCT Consolas : JPUBLIC Font
        {
            Consolas();
        };

        JEXTERN JDM::Font::Font getFont(AvailableFont fontName);
    }
}

#endif
