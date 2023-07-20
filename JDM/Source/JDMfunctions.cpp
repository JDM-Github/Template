#include "JDM/Header/JDMfunctions.hpp"
#include "JDM/Header/JDMinclude.hpp"
#include "JDM/Header/cacheManager.hpp"
#include "JDM/Header/logger.hpp"

JNAMESPACE JDM
{
    JDOUBLE getObjectArithmetic(JSP<JDM::Object> object)
    {
        JAUTO isInteger = JDYNAMICC<Integer *>(object.get());
        JIF (isInteger)
        {
            JRETURN JSTATICC<JDOUBLE>(isInteger->getValue());
        }

        JAUTO isDouble = JDYNAMICC<Double *>(object.get());
        JIF (isDouble)
        {
            JRETURN isDouble->getValue();
        }
        JRETURN 0.0;
    };

    JUINT8 getUint8Limit(JSP<JDM::Object> object)
    {
        JAUTO returnValue = [](JUINT8 value)
        {
            JRETURN (
                (std::max(
                    std::min(
                        value,
                        JSTATICC<JUINT8>(255)),
                    JSTATICC<JUINT8>(0))
                )
            );
        };
        JAUTO isInteger = JDYNAMICC<Integer *>(object.get());
        JIF (isInteger)
        {
            JRETURN returnValue(JSTATICC<JUINT8>(isInteger->getValue()));
        }

        JAUTO isDouble = JDYNAMICC<Double *>(object.get());
        JIF (isDouble)
        {
            JRETURN returnValue(JSTATICC<JUINT8>(isDouble->getValue()));
        }

        JRETURN 0;
    };

    JLLONG getNumberLimit(JSP<JDM::Object> object, JLLONG minimum, JLLONG maximum)
    {
        JAUTO returnValue = [minimum, maximum](JLLONG value)
        {
            JRETURN (
                (std::max(
                    std::min(
                        value,
                        maximum),
                    minimum)
                )
            );
        };
        JAUTO isInteger = JDYNAMICC<Integer *>(object.get());
        JIF (isInteger)
        {
            JRETURN returnValue(isInteger->getValue());
        }

        JAUTO isDouble = JDYNAMICC<Double *>(object.get());
        JIF (isDouble)
        {
            JRETURN returnValue(JSTATICC<JLLONG>(isDouble->getValue()));
        }
        JRETURN 0;
    };

    JBOOL getIfBoolean(JSP<JDM::Object> object)
    {
        JAUTO isBoolean = JDYNAMICC<JDM::Boolean *>(object.get());
        JIF (isBoolean)
        {
            JRETURN isBoolean->getValue();
        }
        JRETURN JFALSE;
    }

    JLLONG getIfInteger(JSP<JDM::Object> object)
    {
        JAUTO isInteger = JDYNAMICC<JDM::Integer *>(object.get());
        JIF (isInteger)
        {
            JRETURN isInteger->getValue();
        }
        JRETURN 0;
    }

    JDOUBLE getIfDouble (JSP<JDM::Object> object)
    {
        JAUTO isDouble = JDYNAMICC<JDM::Double *>(object.get());
        JIF (isDouble)
        {
            JRETURN isDouble->getValue();
        }
        JRETURN 0.0;
    }

    JSTR getIfString (JSP<JDM::Object> object)
    {
        JAUTO isString = JDYNAMICC<JDM::String *>(object.get());
        JIF (isString)
        {
            JRETURN *isString;
        }
        JRETURN JEMPTYSTRING;
    }


    JCVOID subtractCharAtIndex(JSTR &str, JCINT index)
    {
        JIF (index >= 0 && index < str.length())
            str.erase(index, 1);
    }

    JCVOID addCharAtIndex(JSTR &str, JCINT index, JCSTR &ch)
    {
        JIF (index >= 0 && index <= str.size())
            str.insert(index, ch);
    }

    JCSTR retSubtractCharAtIndex(JSTR str, JCINT index)
    {
        JIF (index >= 0 && index < str.length())
            str.erase(index, 1);
        JRETURN str;
    }

    JCSTR retAddCharAtIndex(JSTR str, JCINT index, JCSTR &ch)
    {
        JIF (index >= 0 && index <= str.size())
            str.insert(index, ch);
        JRETURN str;
    }

    JCBOOL isFileExist(JSTRVIEW file)
    {
        JRETURN std::filesystem::exists(file);
    }

    JCONST JDM::ColorRGB getColorFromHex(JSTRVIEW hexColor)
    {
        ColorRGB color;
        JCSTR colorString = (
            (hexColor.at(0) == '#') ?
                JSTR(hexColor.substr(1)) : JSTR(hexColor)
        );

        std::istringstream iss(colorString);
        JUINT hexValue; iss >> std::hex >> hexValue;
        color.r = (hexValue >> 16) & 0xFF;
        color.g = (hexValue >> 8) & 0xFF;
        color.b = hexValue & 0xFF;

        JRETURN color;
    }

    JCONST JDM::ColorRGBA getColorFromHexA(JSTRVIEW hexColor)
    {
        ColorRGBA color;
        JCSTR colorString = ((hexColor.at(0) == '#') ?
            JSTR(hexColor.substr(1)) : JSTR(hexColor)
        );

        std::istringstream iss(colorString);
        JUINT hexValue; iss >> std::hex >> hexValue;

        JIF (colorString.length() <= 6)
        {
            color.r = (hexValue >> 16) & 0xFF;
            color.g = (hexValue >> 8) & 0xFF;
            color.b = hexValue & 0xFF;
            color.a = 255;
        }
        JELSE
        {
            color.r = (hexValue >> 24) & 0xFF;
            color.g = (hexValue >> 16) & 0xFF;
            color.b = (hexValue >> 8) & 0xFF;
            color.a = hexValue & 0xFF;
        }
        JRETURN color;
    }

    JCBOOL IsTextureInWindow(
        JCDOUBLE x,
        JCDOUBLE y,
        JCDOUBLE width,
        JCDOUBLE height)
    {
        JRETURN !(x > JDM::WindowWidth || x + width < 0 || y > JDM::WindowHeight || y + height < 0);
    }

    SDL_Texture *loadRoundedTexture(
        JCONST JDM::Size size,
        JCCHARP path,
        JCONST JDM::FourArc arc,
        JCUINT8 lineWidth)
    {
        SDL_Surface *originalSurface = JNULLPTR;
        JIF (CacheManager::checkIfPathInSurfaceCache(path))
        {
            JDM::Logger("[ INFO ]: GETTING SURFACE FROM CACHE");
            originalSurface = CacheManager::getSurfaceInCache(path);
        }
        JELSE
        {
            JDM::Logger("[ INFO ]: ADDING SURFACE TO CACHE");
            originalSurface = IMG_Load(path);
            CacheManager::addPathInSurfaceCache(path, originalSurface);
        }

        JIF (arc.topLeft == 0 && arc.topRight == 0 && arc.topLeft == 0 && arc.topRight == 0 && lineWidth == 0)
        {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(JDM::renderer, originalSurface);
            JRETURN texture;
        }
        SDL_Surface* resizedSurface = SDL_CreateRGBSurfaceWithFormat(0, size.width, size.height, 32, SDL_PIXELFORMAT_RGBA32);
        SDL_BlitScaled(originalSurface, JNULLPTR, resizedSurface, JNULLPTR);

        JUINT32 transparentColor = SDL_MapRGBA(resizedSurface->format, 0, 0, 0, 0);
        SDL_SetSurfaceBlendMode(resizedSurface, SDL_BLENDMODE_BLEND);

        JAUTO modifyCorner = [&resizedSurface, lineWidth, transparentColor] (
            JINT addX,
            JINT addY,
            JINT size,
            JINT startX,
            JINT startY,
            JINT endX,
            JINT endY)
        {
            JFOR (JINT y = startY; y < endY; ++y)
            {
                JFOR (JINT x = startX; x < endX; ++x)
                {
                    JINT dx = x - size;
                    JINT dy = y - size;
                    JINT distance = std::sqrt(dx * dx + dy * dy);
                    JIF (distance > size || ((lineWidth > 0) ? (distance < size - lineWidth) : false))
                    {
                        JUINT32* pixel = JREINTERPRETC<JUINT32*>(
                            JREINTERPRETC<JUINT8*>(resizedSurface->pixels)
                            + (addY + y) * resizedSurface->pitch
                            + (addX + x) * resizedSurface->format->BytesPerPixel);
                        *pixel = transparentColor;
                    }
                }
            }
        };

        if (lineWidth > 0)
        {
            JFOR (JINT x = arc.topLeft; x < resizedSurface->w - arc.topRight; ++x)
            {
                JFOR (JINT y = lineWidth; y < resizedSurface->h - lineWidth; ++y)
                {
                    JUINT32* pixel = JREINTERPRETC<JUINT32*>(
                        JREINTERPRETC<JUINT8*>(resizedSurface->pixels)
                        + y * resizedSurface->pitch
                        + x * resizedSurface->format->BytesPerPixel);
                        *pixel = transparentColor;
                }
            }
            JFOR (JINT x = lineWidth; x < resizedSurface->w - lineWidth; ++x)
            {
                JFOR (JINT y = arc.bottomLeft; y < resizedSurface->h - arc.bottomRight; ++y)
                {
                    JUINT32* pixel = JREINTERPRETC<JUINT32*>(
                        JREINTERPRETC<JUINT8*>(resizedSurface->pixels)
                        + y * resizedSurface->pitch
                        + x * resizedSurface->format->BytesPerPixel);
                        *pixel = transparentColor;
                }
            }
        }

        JIF (arc.topLeft)
            modifyCorner(
                0, 0,
                arc.topLeft, 0,
                0,
                arc.topLeft, arc.topLeft
            );

        JIF (arc.topRight)
            modifyCorner(
                resizedSurface->w - arc.topRight * 2, 0,
                arc.topRight, arc.topRight,
                0,
                arc.topRight * 2, arc.topRight
            );

        JIF (arc.bottomLeft)
            modifyCorner(
                0, resizedSurface->h - arc.bottomLeft * 2,
                arc.bottomLeft, 0,
                arc.bottomLeft,
                arc.bottomLeft, arc.bottomLeft * 2
            );

        JIF (arc.bottomRight)
            modifyCorner(
                resizedSurface->w - arc.bottomRight * 2,
                resizedSurface->h - arc.bottomRight * 2,
                arc.bottomRight,
                arc.bottomRight, arc.bottomRight,
                arc.bottomRight * 2, arc.bottomRight * 2
            );

        SDL_Texture* texture = SDL_CreateTextureFromSurface(JDM::renderer, resizedSurface);
        SDL_FreeSurface(resizedSurface);
        JRETURN texture;
    }

    SDL_Texture *loadTextTexture(JCCHARP path, JCCHARP text, JCONST ColorRGBA color)
    {
        TTF_Font *tempFont = JNULLPTR;
        JIF (CacheManager::checkIfFontExistCache(path))
        {
            JDM::Logger("[ INFO ]: GETTING FONT FROM CACHE");
            tempFont = CacheManager::getFontInCache(path);
        }
        JELSE
        {
            JDM::Logger("[ INFO ]: ADDING FONT TO CACHE");
            tempFont = TTF_OpenFont(path, 256);
            CacheManager::addFontCache(path, tempFont);
        }
        SDL_Surface *tempsurface = TTF_RenderText_Blended(tempFont, text, SDL_Color{color.r, color.g, color.b});
        SDL_Texture *texture     = SDL_CreateTextureFromSurface(JDM::renderer, tempsurface);
        SDL_FreeSurface (tempsurface);
        JRETURN texture;
    }
};
