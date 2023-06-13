#pragma once
#ifndef JDM_LOGGER_HPP
#define JDM_LOGGER_HPP
#include "defines.hpp"

JNAMESPACE JDM
{
    JINLINE JVOID Logger()
    {
        std::cout << std::endl;
    }

    JTEMPLATE <JCLASS X, JCLASS... Args>
    JINLINE JVOID Logger(JCONST X &x, JCONST Args... args)
    {
        std::cout << x;
        Logger(args...);
    }
}

#endif