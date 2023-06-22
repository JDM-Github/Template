#pragma once
#ifndef JDM_CANVAS_HPP
#define JDM_CANVAS_HPP
#include "defines.hpp"
#include "JDMcomponents/JDMcomponent.hpp"

JNAMESPACE JDM
{
    JNAMESPACE Canvas
    {
        JCLASS Rectangle : JPUBLIC JDM::Comp::Components
        {
        JPUBLIC:
            JINLINE Rectangle(
                JCDOUBLE         xPos   = 0x00,
                JCDOUBLE         yPos   = 0x00,
                JCDOUBLE         width  = 0x64,
                JCDOUBLE         height = 0x64,
                JCONST ColorRGBA color  = {0xff, 0xff, 0xff, 0xff}
            ) :
                Components(xPos, yPos, width, height),
                _rectColor(color                    )
            { }

            JINLINE JCVOID setColor(JCONST ColorRGBA color)
            {
                JTHIS->_rectColor = color;
            }

            JINLINE JCVOID setInterpolatedColorAndFactor(JCONST ColorRGBA &interpolateColor, JDOUBLE interpolateFactor)
            {
                JTHIS->setInterpolatedColor (interpolateColor);
                JTHIS->setInterpolatedFactor(interpolateFactor);
            }

            JINLINE JCVOID setInterpolatedColor(JCONST ColorRGBA &interpolateColor)
            {
                JTHIS->_interpolatedColor = interpolateColor;
            }

            JINLINE JCVOID setInterpolatedFactor(JCDOUBLE interpolateFactor)
            {
                JTHIS->_interpolatedColorFactor = interpolateFactor;
            }

            JCONSTEXPR ColorRGBA getColor() JCONST
            {
                JRETURN JTHIS->_rectColor;
            }

            JINLINE ColorRGBA interpolateColors()
            {
                Uint8 r = JTHIS->_rectColor.r + JSTATICC<Uint8>((JTHIS->_interpolatedColor.r - JTHIS->_rectColor.r) * JTHIS->_interpolatedColorFactor);
                Uint8 g = JTHIS->_rectColor.g + JSTATICC<Uint8>((JTHIS->_interpolatedColor.g - JTHIS->_rectColor.g) * JTHIS->_interpolatedColorFactor);
                Uint8 b = JTHIS->_rectColor.b + JSTATICC<Uint8>((JTHIS->_interpolatedColor.b - JTHIS->_rectColor.b) * JTHIS->_interpolatedColorFactor);
                Uint8 a = JTHIS->_rectColor.a + JSTATICC<Uint8>((JTHIS->_interpolatedColor.a - JTHIS->_rectColor.a) * JTHIS->_interpolatedColorFactor);
                return { r, g, b, a };
            }

            JINLINE JCVOID update() JOVERRIDE
            {
                JTHIS->_setRectangle();
            }

            JINLINE JCVOID renderComp() JOVERRIDE
            {
                JIF (IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight()))
                {
                    ColorRGBA rgba = JTHIS->interpolateColors();
                    SDL_SetRenderDrawColor(JDM::renderer, rgba.r, rgba.g, rgba.b, rgba.a);
                    SDL_RenderFillRectF   (JDM::renderer, &JTHIS->_rect);
                }
            }

        JPRIVATE:
            ColorRGBA _rectColor              = {0xff, 0xff, 0xff, 0xff};
            ColorRGBA _interpolatedColor      = {0x00, 0x00, 0x00, 0x00};
            SDL_FRect _rect                   = {0x00, 0x00, 0x00, 0x00};

            JDOUBLE  _interpolatedColorFactor = 0.0;

        JPRIVATE:
            JINLINE JCVOID _setRectangle()
            {
                JTHIS->_rect.w = JTHIS->getWidth();
                JTHIS->_rect.h = JTHIS->getHeight();
                JTHIS->_rect.x = JTHIS->getX();
                JTHIS->_rect.y = JTHIS->getY();
            }
        };

    // JCLASS Circle : JPUBLIC Components {

    // JPRIVATE:
    //     SDL_Texture *circleTexture;
    //     SDL_FRect rect;
    //     ColorRGBA rectColor;
    //     ColorRGBA startColor = {0, 0, 0, 0};
    //     ColorRGBA endColor = {0, 0, 0, 0};

    //     Gradient gradientAlignment = NONE;

    // JPUBLIC:
    //     JINLINE JCVOID setRect() {
    //         JTHIS->rect.x = JTHIS->getX();
    //         JTHIS->rect.y = JTHIS->getY();
    //         JTHIS->rect.w = JTHIS->getWidth();
    //         JTHIS->rect.h = JTHIS->getHeight();
    //     }
    //     Circle(JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
    //       JCDOUBLE xPos2 = 100, JCDOUBLE yPos2 = 100, ColorRGBA color = {255, 255, 255, 255})
    //       : Components(xPos, yPos, xPos2, yPos2), rectColor(color) {
    //         JTHIS->circleTexture = IMG_LoadTexture(JDM::renderer, CircleImage.c_str());
    //         SDL_SetTextureBlendMode(JTHIS->circleTexture, SDL_BLENDMODE_BLEND);
    //         SDL_SetTextureScaleMode(JTHIS->circleTexture, SDL_ScaleModeLinear);
    //         JTHIS->setColor();
    //     }
    //     JINLINE JUINT8 interpolateColorComponent(JUINT8 startComponent, JUINT8 endComponent, JINT y, JINT height) {
    //         JRETURN startComponent + ((endComponent - startComponent) * y) / height;
    //     }
    //     JINLINE JCVOID setGradient(Gradient grad) { JTHIS->gradientAlignment = grad; }
    //     JINLINE JCVOID setGradiendColor(ColorRGBA first, ColorRGBA second) {
    //         JTHIS->startColor = first;
    //         JTHIS->endColor = second;
    //     }
    //     JINLINE JCVOID setColor() {
    //         SDL_SetTextureColorMod(JTHIS->circleTexture, JTHIS->rectColor.r, JTHIS->rectColor.g, JTHIS->rectColor.b);
    //         SDL_SetTextureAlphaMod(JTHIS->circleTexture, JTHIS->rectColor.a);
    //     }
    //     JINLINE JCVOID update() { JTHIS->setRect(); }
    //     JINLINE JCVOID renderComp() {
    //         JIF (IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight(), JDM::WinWidth, JDM::WinHeight))
    //             SDL_RenderCopyF(JDM::renderer, JTHIS->circleTexture, JNULLPTR, &JTHIS->rect);
    //     }
    // };

    // JCLASS Line : JPUBLIC Components {
    // JPRIVATE:
    //     ColorRGBA rectColor;

    // JPUBLIC:
    //     Line(JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
    //       JCDOUBLE xPos2 = 100, JCDOUBLE yPos2 = 100, ColorRGBA color = {255, 255, 255, 255})
    //       : Components(xPos, yPos, xPos2, yPos2), rectColor(color) { }

    //     JINLINE JCVOID setColor(ColorRGBA color) { JTHIS->rectColor = color; }
    //     JCONSTEXPR ColorRGBA getColor() JCONST { JRETURN JTHIS->rectColor; }

    //     JINLINE JCVOID renderComp() JOVERRIDE {
    //         JIF (IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight(), JDM::WinWidth, JDM::WinHeight)) {
    //             SDL_SetRenderDrawColor(JDM::renderer, JTHIS->rectColor.r, JTHIS->rectColor.g, JTHIS->rectColor.b, JTHIS->rectColor.a);
    //             SDL_RenderDrawLineF(JDM::renderer, JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight());
    //         }
    //     }
    // };
}}
#endif