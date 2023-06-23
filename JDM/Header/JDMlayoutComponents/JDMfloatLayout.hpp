#pragma once
#ifndef JDM_LAYOUT_FLOAT_HPP
#define JDM_LAYOUT_FLOAT_HPP

#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMcomponents/JDMcomponent.hpp"
#include "JDM/Header/JDMbaseComponents/JDMbaseLayout.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Layout
    {
        JCLASS FloatLayout : JPUBLIC JDM::Comp::Components, JPUBLIC JDM::Base::BaseLayout
        {
        JPUBLIC:
            JCVOID update          (                            ) JOVERRIDE;
            JCVOID renderComp      (                            ) JOVERRIDE;
            JCVOID mouseUpComp     (SDL_MouseButtonEvent & mouse) JOVERRIDE;
            JCBOOL mouseDownComp   (SDL_MouseButtonEvent & mouse) JOVERRIDE;
            JCVOID mouseMotionComp (SDL_MouseMotionEvent & mouse) JOVERRIDE;

            FloatLayout() : JDM::Comp::Components() { }

        JPRIVATE:
            JUSING JDM::Comp::Components::setSizePos;
            JUSING JDM::Comp::Components::setSize;
            JUSING JDM::Comp::Components::setPos;
            JUSING JDM::Comp::Components::setWidth;
            JUSING JDM::Comp::Components::setHeight;
            JUSING JDM::Comp::Components::setX;
            JUSING JDM::Comp::Components::setY;

            JUSING JDM::Comp::Components::getSizePos;
            JUSING JDM::Comp::Components::getSize;
            JUSING JDM::Comp::Components::getPos;
            JUSING JDM::Comp::Components::getWidth;
            JUSING JDM::Comp::Components::getHeight;
            JUSING JDM::Comp::Components::getX;
            JUSING JDM::Comp::Components::getY;
        };
    }
}

#endif
