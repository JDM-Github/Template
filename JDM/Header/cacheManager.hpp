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

        JSTATIC JCVOID       cleanSurfaceCache         (                                  );
        JSTATIC JCINT        getSurfaceCacheSize       (                                  );
        JSTATIC SDL_Surface *getSurfaceInCache         (JCSTR &path                       );


        JSTATIC JCBOOL       checkIfFontExistCache     (JCSTR &font                       );
        JSTATIC JCVOID       addFontCache              (JCSTR &font, TTF_Font * fontTTf   );
        JSTATIC JCVOID       cleanFontCache            (                                  );

        JSTATIC JCINT        getFontCacheSize          (                                  );
        JSTATIC TTF_Font    *getFontInCache            (JCSTR &font                       );

    JPRIVATE:
        JINLINE CacheManager() {}
        JSTATIC JUMAP<JSTR, SDL_Surface *> surfaceCache;
        JSTATIC JUMAP<JSTR, TTF_Font *> fontCache;
    };
}

#endif
