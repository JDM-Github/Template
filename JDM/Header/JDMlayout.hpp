#pragma once
#ifndef JDM_LAYOUT_HPP
#define JDM_LAYOUT_HPP
#include "defines.hpp"
#include "JDMcomponents.hpp"


JNAMESPACE JDM
{
    JNAMESPACE Layout
    {
        JCLASS BaseLayout
        {
        JPUBLIC:
            JCVOID          handleChildren         (                                                                );
            JCVOID          setFunctionAfterHandle (JFUNCCALL function                                              );
            JVIRTUAL JCVOID addChildren            (JCONST JSP<JDM::Comp::Components> &component, JUINT position = 0);
            JVIRTUAL JCVOID removeChildren         (JCONST JSP<JDM::Comp::Components> &component                    );
            JVIRTUAL JCVOID bringToFront           (JCONST JSP<JDM::Comp::Components> &component                    );
            JVIRTUAL JCVOID bringToBack            (JCONST JSP<JDM::Comp::Components> &component                    );
            JVIRTUAL JCVOID bringToPosition        (JCONST JSP<JDM::Comp::Components> &component, JUINT position    );

            JINLINE JLIST<JSP<JDM::Comp::Components>> getAllChildren() JCONST
            {
                JRETURN JTHIS->_childrens;
            }

        JPRIVATE:
            BaseLayout() {}
        
        JPRIVATE:
            JCVOID _updateComponent (                           );
            JCVOID _renderComponent (                           );
            JCVOID _mouseUpComp     (SDL_MouseButtonEvent &mouse);
            JCVOID _mouseDownComp   (SDL_MouseButtonEvent &mouse);
            JCVOID _mouseMotionComp (SDL_MouseMotionEvent &mouse);

        JPRIVATE:
            JLIST<JSP<JDM::Comp::Components>>                             _childrens             = {};
            JLIST<JPAIR<JPAIR<JSP<JDM::Comp::Components>, JUINT>, JCHAR>> _allHandlingComponents = {};
            JFUNCCALL                                                     _functionAfterHandle   = []() {};

        JFRIEND JCLASS FloatLayout;
        JFRIEND JCLASS GridLayout;
        };

        JCLASS FloatLayout : JPUBLIC JDM::Comp::Components, JPUBLIC BaseLayout
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

        JCLASS GridLayout : JPUBLIC JDM::Comp::Components, JPUBLIC BaseLayout
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
