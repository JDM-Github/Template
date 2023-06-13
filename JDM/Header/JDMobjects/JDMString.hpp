#pragma once
#ifndef JDM_OBJECT_STRING_HPP
#define JDM_OBJECT_STRING_HPP
#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

JNAMESPACE JDM
{
    JCLASS String : JPUBLIC JSTR, JPUBLIC Object
    {
    JPUBLIC:
        String (JCSTR &string)
        :
            JSTR(string)
        { }
        String (JCONST String &string)
        :  
            JSTR(string)
        { }
    };
}

#endif