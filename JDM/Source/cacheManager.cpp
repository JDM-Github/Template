#include "JDM/Header/cacheManager.hpp"

JUMAP<JSTR, SDL_Surface *> JDM::CacheManager::surfaceCache = {};

JCBOOL JDM::CacheManager::checkIfPathInSurfaceCache(JCSTR &path)
{
    JRETURN JDM::CacheManager::surfaceCache.count(path);
}

JCVOID JDM::CacheManager::addPathInSurfaceCache(JCSTR &path, SDL_Surface *surface)
{
    JDM::CacheManager::surfaceCache[path] = surface;
}

SDL_Surface* JDM::CacheManager::getSurfaceInCache(JCSTR &path)
{
    JRETURN JDM::CacheManager::surfaceCache[path];
}

JCINT JDM::CacheManager::getSurfaceCacheSize()
{
    JRETURN JDM::CacheManager::surfaceCache.size();
}

JCVOID JDM::CacheManager::clean()
{
    JFOR (JAUTO surface : JDM::CacheManager::surfaceCache)
        SDL_FreeSurface(surface.second);

    JDM::CacheManager::surfaceCache.clear();
}
