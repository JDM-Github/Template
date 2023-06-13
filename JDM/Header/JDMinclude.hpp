#pragma once
#ifndef RJDM_INCLUDE_HPP
#define RJDM_INCLUDE_HPP

#include "defines.hpp"

JNAMESPACE JDM
{
    JEXTERN SDL_Renderer *renderer;
    JEXTERN JDOUBLE       TimeFrame;
    JEXTERN JDOUBLE       FPS;
    JEXTERN JDOUBLE       ElapseTime;
    JEXTERN JINT          WindowX;
    JEXTERN JINT          WindowY;
    JEXTERN JINT          WindowWidth;
    JEXTERN JINT          WindowHeight;
    JEXTERN JBOOL         alreadyTouched;

    JNAMESPACE Mouse
    {
        JEXTERN JBOOL LeftMouseDown;
        JEXTERN JBOOL RightMouseDown;
        JEXTERN JINT  MouseX;
        JEXTERN JINT  MouseY;
        JEXTERN JINT  GlobalMouseX;
        JEXTERN JINT  GlobalMouseY;
    }
}

#endif