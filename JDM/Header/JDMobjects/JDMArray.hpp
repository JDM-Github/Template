#pragma once
#ifndef JDM_OBJECT_ARRAY_HPP
#define JDM_OBJECT_ARRAY_HPP
#include <initializer_list>
#include "JDM/Header/defines.hpp"
#include "JDM/Header/JDMobjects/JDMobject.hpp"

JNAMESPACE JDM
{
    JTEMPLATE <JCLASS T>
    JCLASS Array : JPUBLIC JVECTOR<T>, JPUBLIC Object
    {
    JPUBLIC:
        Array(std::initializer_list<T> arrayList)
            : JVECTOR<T>(arrayList) {}
    };
}


#endif