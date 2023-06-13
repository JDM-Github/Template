#pragma once
#ifndef JDM_CACHE_MANAGER_HPP
#define JDM_CACHE_MANAGER_HPP
#include "defines.hpp"

JNAMESPACE JDM
{
    JCLASS CacheManager
    {
    JPUBLIC:
        JSTATIC JCBOOL       checkIfPathInSurfaceCache (JCSTR &path                       );
        JSTATIC JCVOID       addPathInSurfaceCache     (JCSTR &path, SDL_Surface * surface);
        JSTATIC JCVOID       clean                     (                                  );
        JSTATIC JCINT        getSurfaceCacheSize       (                                  );
        JSTATIC SDL_Surface *getSurfaceInCache         (JCSTR &path                       );

    JPRIVATE:
        JINLINE CacheManager() {}
        JSTATIC JUMAP<JSTR, SDL_Surface *> surfaceCache;
    };
}

#endif
