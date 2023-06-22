#include "JDM/Header/JDMcomponents/JDMtextInput.hpp"
#include "JDM/Header/JDMfunctions.hpp"
#include "JDM/Header/JDMinclude.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class TextInput
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class TextInput
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::TextInput::TextInput(
    JCSTR              &text,
    JCSTR              &source,
    JCDOUBLE            xPos,
    JCDOUBLE            yPos,
    JCDOUBLE            width,
    JCDOUBLE            height,
    JCONST ColorRGBA    color,
    JCONST ColorRGBA    colorImage,
    JCONST JDM::FourArc arc,
    JCINT               fontSize,
    JDM::Font::Halign   hAlign,
    JDM::Font::Valign   vAlign
) :
    JDM::Comp::FocusedTextComponent(text, source, xPos, yPos, width, height, color, colorImage, arc, fontSize, hAlign, vAlign)
{ }

JCVOID JDM::Comp::TextInput::setCursorColor(JCONST ColorRGBA color)
{
    JTHIS->_colorCursor = color;
}

JCVOID JDM::Comp::TextInput::renderComp()
{
    JIF (IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight()))
    {
        Label::renderComp();
        JTHIS->_currentBlink -= JDM::TimeFrame;

        JIF (JTHIS->isFocused)
        {
            JIF (JTHIS->_currentBlink > 0)
            {
                JIF (JTHIS->_blinked)
                {
                    SDL_SetRenderDrawColor(JDM::renderer, JTHIS->_colorCursor.r, JTHIS->_colorCursor.g, JTHIS->_colorCursor.b, JTHIS->_colorCursor.a);
                    SDL_RenderDrawLineF   (JDM::renderer,
                        JTHIS->getTextDestination().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()), JTHIS->getTextDestination().y + 15,
                        JTHIS->getTextDestination().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()), JTHIS->getTextDestination().y + JTHIS->getCopyFontSize() + 5);

                    SDL_RenderDrawLineF(JDM::renderer,
                        JTHIS->getTextDestination().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()) + 1, JTHIS->getTextDestination().y,
                        JTHIS->getTextDestination().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()) + 1, JTHIS->getTextDestination().y + JTHIS->getCopyFontSize() + 5);
                }
            }
            JELSE
            {
                JTHIS->_currentBlink = JTHIS->_blinkDuration;
                JTHIS->_blinked = !JTHIS->_blinked;
            }
        }
    }
}
