#pragma once
#ifndef JDM_OBJECT_BOOLEAN_HPP
#define JDM_OBJECT_BOOLEAN_HPP
#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

JNAMESPACE JDM
{
    JCLASS Boolean : JPUBLIC Object
    {
    JPRIVATE:
        JBOOL _bool = 0;

    JPUBLIC:
        Boolean(JCBOOL BooleanNum) { JTHIS->_bool = BooleanNum; }
        Boolean(JCONST Boolean &BooleanNum) { JTHIS->_bool = BooleanNum; }
        JCBOOL getValue() JCONST { JRETURN JTHIS->_bool; }

        JCONST Boolean &operator=(JCONST Boolean& other)
        {
            JTHIS->_bool = other._bool;
            JRETURN *JTHIS;
        }
        JCONST Boolean &operator=(JCBOOL number)
        {
            JTHIS->_bool = number;
            JRETURN *JTHIS;
        }
        operator JBOOL() JCONST { JRETURN JTHIS->_bool; }
        JCBOOL operator> (JCONST Boolean& other) JCONST { JRETURN _bool >  other._bool; }
        JCBOOL operator< (JCONST Boolean& other) JCONST { JRETURN _bool <  other._bool; }
        JCBOOL operator>=(JCONST Boolean& other) JCONST { JRETURN _bool >= other._bool; }
        JCBOOL operator<=(JCONST Boolean& other) JCONST { JRETURN _bool <= other._bool; }
        JCBOOL operator==(JCONST Boolean& other) JCONST { JRETURN _bool == other._bool; }
    };
}

#endif