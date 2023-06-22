#include "JDM/Header/JDMbaseComponents/JDMbaseGradient.hpp"
#include "JDM/Header/JDMinclude.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class BaseGradient
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JCVOID JDM::Base::BaseGradient::setGradientAlignment(JCONST JDM::Gradient gradentAlignment)
{
    JTHIS->_gradientAlignment = gradentAlignment;
}

JCVOID JDM::Base::BaseGradient::setGradientColor(JCONST JDM::ColorRGBA first, JCONST JDM::ColorRGBA second)
{
    JTHIS->_gradientStartColor = first;
    JTHIS->_gradientEndColor   = second;
}

JCONST JUINT8 JDM::Base::BaseGradient::_interpolateColorComponent(JUINT8 startComponent, JUINT8 endComponent, JINT position, JINT length) JCONST
{
    JRETURN startComponent + ((endComponent - startComponent) * position) / length;
}

JCVOID JDM::Base::BaseGradient::_renderGradient(JCONST JDM::PositionSize posSize)
{
    SDL_SetRenderDrawBlendMode (JDM::renderer, SDL_BLENDMODE_BLEND);
    JAUTO drawLine = [&](JCINT index, JCINT size, JCONST JDM::LinePoints &points) {

        JUINT8 r = JTHIS->_interpolateColorComponent (JTHIS->_gradientStartColor.r, JTHIS->_gradientEndColor.r, index, size);
        JUINT8 g = JTHIS->_interpolateColorComponent (JTHIS->_gradientStartColor.g, JTHIS->_gradientEndColor.g, index, size);
        JUINT8 b = JTHIS->_interpolateColorComponent (JTHIS->_gradientStartColor.b, JTHIS->_gradientEndColor.b, index, size);
        JUINT8 a = JTHIS->_interpolateColorComponent (JTHIS->_gradientStartColor.a, JTHIS->_gradientEndColor.a, index, size);

        SDL_SetRenderDrawColor     (JDM::renderer,         r,         g,         b,         a);
        SDL_RenderDrawLine         (JDM::renderer, points.x1, points.y1, points.x2, points.y2);
    };
    JSWITCH (JTHIS->_gradientAlignment)
    {
        JCASE JDM::GRADIENT_VERTICAL:
            JFOR (JINT y = 0; y < posSize.height; y++)
                drawLine(y, posSize.height, {posSize.x, posSize.y + y, posSize.x + posSize.width, posSize.y + y});
            JBREAK;
        JCASE JDM::GRADIENT_HORIZONTAL:
            JFOR (JINT x = 0; x < posSize.width; x++)
                drawLine(x, posSize.width, {posSize.x + x, posSize.y, posSize.x + x, posSize.y + posSize.y});
            JBREAK;
    };
    SDL_SetRenderDrawBlendMode (JDM::renderer, SDL_BLENDMODE_NONE);
}

