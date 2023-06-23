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
        JCLASS GridLayout : JPUBLIC JDM::Comp::Components, JPUBLIC JDM::Base::BaseLayout
        {
        JPUBLIC:
            JCVOID   setRows          (JUINT8 row        );
            JCVOID   setCols          (JUINT8 col        );
            JCVOID   setPaddingWidth  (JDOUBLE paddWidth );
            JCVOID   setPaddingHeight (JDOUBLE paddHeight);
            JCVOID   setSpacing       (JDOUBLE spacing   );

            JCUINT8  getRows          () JCONST;
            JCUINT8  getCols          () JCONST;
            JCDOUBLE getPaddingWidth  () JCONST;
            JCDOUBLE getPaddingHeight () JCONST;
            JCDOUBLE getSpacing       () JCONST;

            JCVOID   update          (                                                                 ) JOVERRIDE;
            JCVOID   renderComp      (                                                                 ) JOVERRIDE;
            JCVOID   mouseUpComp     (SDL_MouseButtonEvent &mouse                                      ) JOVERRIDE;
            JCBOOL   mouseDownComp   (SDL_MouseButtonEvent &mouse                                      ) JOVERRIDE;
            JCVOID   mouseMotionComp (SDL_MouseMotionEvent &mouse                                      ) JOVERRIDE;
            JCVOID   addChildren     (JCONST JSP<JDM::Comp::Components> & component, JUINT position = 0) JOVERRIDE;

            GridLayout(
                JCDOUBLE xPos       = 0x00,
                JCDOUBLE yPos       = 0x00,
                JCDOUBLE width      = 0x64,
                JCDOUBLE height     = 0x64,
                JCUINT8  row        = 0x01,
                JCUINT8  col        = 0x01,
                JCDOUBLE paddWidth  = 0x01,
                JCDOUBLE paddHeight = 0x00,
                JCDOUBLE spacing    = 0x00
            );

        JPRIVATE:
            JUINT8  _rows          = 0x01;
            JUINT8  _cols          = 0x01;
            JDOUBLE _paddingWidth  = 0x00;
            JDOUBLE _paddingHeight = 0x00;
            JDOUBLE _spacing       = 0x00;
        };
    }
}

#endif
