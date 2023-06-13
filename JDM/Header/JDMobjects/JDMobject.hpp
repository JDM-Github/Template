#pragma once
#ifndef JDM_OBJECT_HPP
#define JDM_OBJECT_HPP
#include "JDM/Header/defines.hpp"

JNAMESPACE JDM
{
    JCLASS Object
    {
    JPROTECTED:
        Object() = default;

    JPUBLIC:
        JVIRTUAL ~Object() {};
    };
}

#endif