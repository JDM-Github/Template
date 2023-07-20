#include "JDM/Header/cacheManager.hpp"

JUMAP<JSTR, SDL_Surface *> JDM::CacheManager::surfaceCache = {};
JUMAP<JSTR, TTF_Font *> JDM::CacheManager::fontCache = {};

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

JCVOID JDM::CacheManager::cleanSurfaceCache()
{
    JFOR (JAUTO surface : JDM::CacheManager::surfaceCache)
        SDL_FreeSurface(surface.second);

    JDM::CacheManager::surfaceCache.clear();
}



JCBOOL JDM::CacheManager::checkIfFontExistCache(JCSTR &font)
{
    JRETURN JDM::CacheManager::fontCache.count(font);
}

JCVOID JDM::CacheManager::addFontCache(JCSTR &font, TTF_Font *fontTTf)
{
    JDM::CacheManager::fontCache[font] = fontTTf;
}

TTF_Font* JDM::CacheManager::getFontInCache(JCSTR &font)
{
    JRETURN JDM::CacheManager::fontCache[font];
}

JCINT JDM::CacheManager::getFontCacheSize()
{
    JRETURN JDM::CacheManager::fontCache.size();
}

JCVOID JDM::CacheManager::cleanFontCache()
{
    JFOR (JAUTO font : JDM::CacheManager::fontCache)
        TTF_CloseFont(font.second);

    JDM::CacheManager::fontCache.clear();
}

