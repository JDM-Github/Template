#pragma once
#ifndef JDM_OBJECT_DOUBLE_HPP
#define JDM_OBJECT_DOUBLE_HPP
#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

JNAMESPACE JDM
{
    JCLASS Double : JPUBLIC Object
    {
    JPRIVATE:
        JDOUBLE _double = 0;

    JPUBLIC:
        Double(JCDOUBLE doubleNum) { JTHIS->_double = doubleNum; }
        Double(JCONST Double &doubleNum) { JTHIS->_double = doubleNum; }
        JCDOUBLE getValue() JCONST { JRETURN JTHIS->_double; }

        JCONST Double &operator=(JCONST Double& other)
        {
            JTHIS->_double = other._double;
            JRETURN *JTHIS;
        }
        JCONST Double &operator=(JCDOUBLE number)
        {
            JTHIS->_double = number;
            JRETURN *JTHIS;
        }
        operator JDOUBLE() JCONST { JRETURN JTHIS->_double; }
        JCONST Double operator+(JCONST Double& other) JCONST { JRETURN Double(_double + other._double); }
        JCONST Double operator-(JCONST Double& other) JCONST { JRETURN Double(_double - other._double); }
        JCONST Double operator*(JCONST Double& other) JCONST { JRETURN Double(_double * other._double); }
        JCONST Double operator/(JCONST Double& other) JCONST { JRETURN Double(_double / other._double); }

        JCONST Double &operator+=(JCONST Double& other)
        {
            JTHIS->_double += other;
            JRETURN *JTHIS;
        }
        JCONST Double &operator-=(JCONST Double& other)
        {
            JTHIS->_double -= other;
            JRETURN *JTHIS;
        }
        JCONST Double &operator*=(JCONST Double& other)
        {
            JTHIS->_double *= other;
            JRETURN *JTHIS;
        }
        JCONST Double &operator/=(JCONST Double& other)
        {
            JTHIS->_double /= other;
            JRETURN *JTHIS;
        }

        JCBOOL operator> (JCONST Double& other) JCONST { JRETURN _double >  other._double; }
        JCBOOL operator< (JCONST Double& other) JCONST { JRETURN _double <  other._double; }
        JCBOOL operator>=(JCONST Double& other) JCONST { JRETURN _double >= other._double; }
        JCBOOL operator<=(JCONST Double& other) JCONST { JRETURN _double <= other._double; }
        JCBOOL operator==(JCONST Double& other) JCONST { JRETURN _double == other._double; }
    };
}

#endif