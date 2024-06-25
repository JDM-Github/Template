#pragma once
#ifndef JDM_LAYOUT_HPP
#define JDM_LAYOUT_HPP
#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMcomponents/JDMcomponent.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Base
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

            JINLINE JCVOID clearChildrens()
            {
                JFOR (JAUTO &children : JTHIS->_childrens)
                {
                    JTHIS->removeChildren(children);
                }
            }

        JPROTECTED:
            BaseLayout() {}
        
        JPROTECTED:
            JCVOID _updateComponent (                           );
            JCVOID _renderComponent (                           );
            JCVOID _mouseUpComp     (SDL_MouseButtonEvent &mouse);
            JCVOID _mouseDownComp   (SDL_MouseButtonEvent &mouse);
            JCVOID _mouseMotionComp (SDL_MouseMotionEvent &mouse);

        JPROTECTED:
            JLIST<JSP<JDM::Comp::Components>>                             _childrens             = {};
            JLIST<JPAIR<JPAIR<JSP<JDM::Comp::Components>, JUINT>, JCHAR>> _allHandlingComponents = {};
            JFUNCCALL                                                     _functionAfterHandle   = []() {};
        };
    }
}


#endif
