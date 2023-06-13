#pragma once
#ifndef JDM_SETTER_HPP
#define JDM_SETTER_HPP
#include "defines.hpp"
#include "JDMinclude.hpp"

JNAMESPACE JDM
{
    JNAMESPACE SETTER
    {
        JINLINE JCVOID JDMSetFPS(JCUINT8 FPS)
        {
            JDM::FPS = FPS;
        }
    }
}

#endif