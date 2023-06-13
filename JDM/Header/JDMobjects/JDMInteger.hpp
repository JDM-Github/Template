#pragma once
#ifndef JDM_OBJECT_INTEGER_HPP
#define JDM_OBJECT_INTEGER_HPP
#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

JNAMESPACE JDM
{
    JCLASS Integer : JPUBLIC Object
    {
    JPRIVATE:
        JLLONG _integer = 0;

    JPUBLIC:

        Integer(JCLLONG integer) { JTHIS->_integer = integer; }
        Integer(JCONST Integer &integer) { JTHIS->_integer = integer; }
        JCLLONG getValue() JCONST { JRETURN JTHIS->_integer; }

        JCONST Integer &operator=(JCONST Integer& other)
        {
            JTHIS->_integer = other._integer;
            JRETURN *JTHIS;
        }
        JCONST Integer &operator=(JCLLONG number)
        {
            JTHIS->_integer = number;
            JRETURN *JTHIS;
        }
        operator JLLONG() JCONST { JRETURN JTHIS->_integer; }
        JCONST Integer operator+(JCONST Integer& other) JCONST { JRETURN Integer(_integer + other._integer); }
        JCONST Integer operator-(JCONST Integer& other) JCONST { JRETURN Integer(_integer - other._integer); }
        JCONST Integer operator*(JCONST Integer& other) JCONST { JRETURN Integer(_integer * other._integer); }
        JCONST Integer operator/(JCONST Integer& other) JCONST { JRETURN Integer(_integer / other._integer); }
        JCONST Integer operator%(JCONST Integer& other) JCONST { JRETURN Integer(_integer % other._integer); }

        JCONST Integer &operator+=(JCONST Integer& other)
        {
            JTHIS->_integer += other;
            JRETURN *JTHIS;
        }
        JCONST Integer &operator-=(JCONST Integer& other)
        {
            JTHIS->_integer -= other;
            JRETURN *JTHIS;
        }
        JCONST Integer &operator*=(JCONST Integer& other)
        {
            JTHIS->_integer *= other;
            JRETURN *JTHIS;
        }
        JCONST Integer &operator/=(JCONST Integer& other)
        {
            JTHIS->_integer /= other;
            JRETURN *JTHIS;
        }
        JCONST Integer &operator%=(JCONST Integer& other)
        {
            JTHIS->_integer %= other;
            JRETURN *JTHIS;
        }
        JCBOOL operator> (JCONST Integer& other) JCONST { JRETURN _integer >  other._integer; }
        JCBOOL operator< (JCONST Integer& other) JCONST { JRETURN _integer <  other._integer; }
        JCBOOL operator>=(JCONST Integer& other) JCONST { JRETURN _integer >= other._integer; }
        JCBOOL operator<=(JCONST Integer& other) JCONST { JRETURN _integer <= other._integer; }
        JCBOOL operator==(JCONST Integer& other) JCONST { JRETURN _integer == other._integer; }
    };
}

#endif