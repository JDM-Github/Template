#pragma once
#ifndef JDM_BASE_GRADIENT_HPP
#define JDM_BASE_GRADIENT_HPP

#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMstructs.hpp"
#include "JDM/Header/JDMenum.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Base
    {
        JCLASS BaseGradient
        {
        JPUBLIC:
            JCVOID setGradientAlignment (JCONST JDM::Gradient gradientAlignment         );
            JCVOID setGradientColor     (JCONST JDM::ColorRGBA first, JCONST JDM::ColorRGBA second);

        JPROTECTED:
            JINLINE BaseGradient() {}

        JPROTECTED:
            JDM::Gradient      _gradientAlignment  = JDM::Gradient::GRADIENT_NONE;
            JDM::ColorRGBA     _gradientStartColor = {0x00, 0x00, 0x00, 0x00};
            JDM::ColorRGBA     _gradientEndColor   = {0x00, 0x00, 0x00, 0x00}; 

        JPROTECTED:
            JCONST JUINT8 _interpolateColorComponent (JUINT8 startComponent, JUINT8 endComponent, JINT position, JINT length) JCONST;
            JCVOID        _renderGradient            (JCONST JDM::PositionSize posSize                                      );
        };
    }
}

#endif