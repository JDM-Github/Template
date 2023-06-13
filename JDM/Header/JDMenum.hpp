#pragma once
#ifndef JDM_ENUM_HPP
#define JDM_ENUM_HPP
#include "defines.hpp"

JNAMESPACE JDM
{
    JENUM Gradient
    {
        GRADIENT_NONE       = 0x00,
        GRADIENT_VERTICAL   = 0x01,
        GRADIENT_HORIZONTAL = 0x02
    };

    JENUM AnimationSpeed
    {
        ANIMATION_VERYSLOW = 0x1388,
        ANIMATION_SLOW     = 0x0BB8,
        ANIMATION_NORMAL   = 0x03E8,
        ANIMATION_FAST     = 0x01F4,
        ANIMATION_VERYFAST = 0x012C
    };
}

#endif