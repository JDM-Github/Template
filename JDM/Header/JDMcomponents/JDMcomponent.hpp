#pragma once
#ifndef JDM_COMP_COMPONENTS_HPP
#define JDM_COMP_COMPONENTS_HPP

#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMstructs.hpp"
#include "JDM/Header/JDMenum.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Comp
    {
        JCLASS Components
        {
        JPUBLIC:
            JENUM Properties
            {
                X                = 0x00,
                Y                = 0x01,
                WIDTH            = 0x02,
                HEIGHT           = 0x03,
                DISABLED         = 0x04,
                PICK_ON_BOUNDS   = 0x05,
                WILL_RENDER      = 0x06
            };

        JPUBLIC:
            JCBOOL              contains               (JCDOUBLE xPos, JCDOUBLE yPos                                  ) JCONST;
            JCVOID              setSizePos             (JCONST PositionSize sPos                                      );
            JCVOID              setPos                 (JCONST Position pos                                           );
            JCVOID              setSize                (JCONST Size size                                              );
            JCVOID              setX                   (JCDOUBLE xPos                                                 );
            JCVOID              setY                   (JCDOUBLE yPos                                                 );
            JCVOID              setWidth               (JCDOUBLE Width                                                );
            JCVOID              setHeight              (JCDOUBLE Height                                               );
            JCVOID              setDisabled            (JCBOOL disabled                                               );
            JCVOID              setPickOnBounds        (JCBOOL bounds                                                 );
            JCVOID              setPickOnTop           (JCBOOL top                                                    );
            JCVOID              setRendering           (JCBOOL isRendering                                            );
            JCVOID              setUpdateFunction      (JCONST JFUNCCALL function                                     );
            JCVOID              setmouseDownFunction   (JCONST JFUNCTION<JCVOID(SDL_MouseButtonEvent &mouse)> function);
            JCVOID              setmouseMotionFunction (JCONST JFUNCTION<JCVOID(SDL_MouseMotionEvent &mouse)> function);
            JCVOID              setmouseUpFunction     (JCONST JFUNCTION<JCVOID(SDL_MouseButtonEvent &mouse)> function);

            JCONST PositionSize getSizePos             () JCONST;
            JCONST Position     getPos                 () JCONST;
            JCONST Size         getSize                () JCONST;
            JCDOUBLE            getX                   () JCONST;
            JCDOUBLE            getY                   () JCONST;
            JCDOUBLE            getWidth               () JCONST;
            JCDOUBLE            getHeight              () JCONST;
            JCBOOL              getDisabled            () JCONST;
            JCBOOL              getRendering           () JCONST;
            JCBOOL              getPickOnBounds        () JCONST;
            JCBOOL              getPickOnTop           () JCONST;
            JCBOOL              getMouseClick          () JCONST;
            JDOUBLE            *getPointerX            ();
            JDOUBLE            *getPointerY            ();
            JDOUBLE            *getPointerWidth        ();
            JDOUBLE            *getPointerHeight       ();

            JVIRTUAL JUINT8    *getPointerRImage       ();
            JVIRTUAL JUINT8    *getPointerGImage       ();
            JVIRTUAL JUINT8    *getPointerBImage       ();
            JVIRTUAL JUINT8    *getPointerAImage       ();
            JVIRTUAL JUINT8    *getPointerRText        ();
            JVIRTUAL JUINT8    *getPointerGText        ();
            JVIRTUAL JUINT8    *getPointerBText        ();
            JVIRTUAL JUINT8    *getPointerAText        ();
            JVIRTUAL JCSTR      getName                () JCONST;

            JCONST JFUNCCALL                                     getUpdateFunction      () JCONST;
            JCONST JFUNCTION<JVOID(SDL_MouseButtonEvent &mouse)> getmouseDownFunction   () JCONST;
            JCONST JFUNCTION<JVOID(SDL_MouseMotionEvent &mouse)> getmouseMotionFunction () JCONST;
            JCONST JFUNCTION<JVOID(SDL_MouseButtonEvent &mouse)> getmouseUpFunction     () JCONST;

            JVIRTUAL JCBOOL         mouseDownComp   (SDL_MouseButtonEvent &mouse);
            JVIRTUAL JCVOID         mouseMotionComp (SDL_MouseMotionEvent &mouse);
            JVIRTUAL JCVOID         mouseUpComp     (SDL_MouseButtonEvent &mouse);
            JCVOID                  updateComp      (                           );
            JINLINE JVIRTUAL JCVOID renderComp      (                           ) {}            

            Components(
                JCDOUBLE xPos   = 0x00,
                JCDOUBLE yPos   = 0x00,
                JCDOUBLE width  = 0x64,
                JCDOUBLE height = 0x64
            );
            Components(
                JMAP<Properties, JSP<JDM::Object>> mapComponent
            );

        JPROTECTED:
            JCVOID                  setMouseClick       (JCBOOL set                                       );
            JCBOOL                  setObjectProperties (Properties propertyName, JSP<JDM::Object> &object);
            JINLINE JVIRTUAL JCVOID update              (                                                 ) {}

        JPRIVATE:
            JFUNCCALL                                      _updateFunction      = [](                           ) {}; 
            JFUNCTION<JCVOID(SDL_MouseButtonEvent& mouse)> _mouseDownFunction   = [](SDL_MouseButtonEvent &mouse) {};
            JFUNCTION<JCVOID(SDL_MouseMotionEvent& mouse)> _mouseMotionFunction = [](SDL_MouseMotionEvent &mouse) {};
            JFUNCTION<JCVOID(SDL_MouseButtonEvent& mouse)> _mouseUpFunction     = [](SDL_MouseButtonEvent &mouse) {};

            JBOOL        _mouseClicked   = JFALSE;
            JBOOL        _pickOnTop      = JFALSE;
            JBOOL        _pickOnBounds   = JTRUE;
            JBOOL        _stopRendering  = JFALSE;
            JBOOL        _disabled       = JFALSE;
            PositionSize _sizePos        = {0x00, 0x00, 0x64, 0x64};
        };
    }
}

#endif