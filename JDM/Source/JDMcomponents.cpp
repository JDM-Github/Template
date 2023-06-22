#include "JDM/Header/JDMcomponents.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class Text
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class Text
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::Text::Text(
    JCSTR                &text,
    JCDOUBLE              xPos,
    JCDOUBLE              yPos,
    JCDOUBLE              width,
    JCDOUBLE              height,
    JCONST JDM::ColorRGBA color,
    JCINT                 fontSize,
    JDM::Font::Halign     hAlign,
    JDM::Font::Valign     vAlign
) :
    JDM::Comp::Components(xPos, yPos, width, height)
{
    JTHIS->setTextMessage(text);
    JTHIS->_textColor = color;
    JTHIS->_fontSize  = fontSize;
    JTHIS->_halign    = hAlign;
    JTHIS->_valign    = vAlign;
    JTHIS->_setTextTexture();
}

JDM::Comp::Text::Text(
    JMAP<Properties, JSP<JDM::Object>> mapComponent
)
{
    JFOR (JAUTO [propertyName, object]: mapComponent)
    {
        JIF(!JDM::Comp::Components::setObjectProperties(JSTATICC<JDM::Comp::Components::Properties>(propertyName), object))
            JDM::Base::BaseText::_setObjectProperties(JSTATICC<JDM::Base::BaseText::TextProperties>(propertyName), object);
    }
    JTHIS->_setTextTexture();
}

JUINT8 *JDM::Comp::Text::getPointerRText()
{
    JRETURN &JTHIS->_textColor.r;
}

JUINT8 *JDM::Comp::Text::getPointerGText()
{
    JRETURN &JTHIS->_textColor.g;
}

JUINT8 *JDM::Comp::Text::getPointerBText()
{
    JRETURN &JTHIS->_textColor.b;
}

JUINT8 *JDM::Comp::Text::getPointerAText()
{
    JRETURN &JTHIS->_textColor.a;
}

JCSTR JDM::Comp::Text::getName() JCONST
{
    JRETURN "Text";
}

JCVOID JDM::Comp::Text::update()
{
    JTHIS->_updateText(JTHIS->getSizePos());
}

JCVOID JDM::Comp::Text::renderComp()
{
    JIF (IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight()))
    {
        JTHIS->_renderText();
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class Image
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class Image
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::Image::Image(
    JCSTR                &source,
    JCDOUBLE              xPos,
    JCDOUBLE              yPos,
    JCDOUBLE              width,
    JCDOUBLE              height,
    JCONST JDM::ColorRGBA color,
    JCONST FourArc        arc
) :
    JDM::Comp::Components(xPos, yPos, width, height)
{
    JTHIS->setImageSource (source);
    JTHIS->_imageColor = color;
    JTHIS->_arc        = arc;
    JTHIS->_setImageTexture (JTHIS->getSize());
}

JDM::Comp::Image::Image(
    JMAP<Properties, JSP<JDM::Object>> mapComponent
)
{
    JFOR (JAUTO [propertyName, object]: mapComponent)
    {
        JIF(!JDM::Comp::Components::setObjectProperties(JSTATICC<JDM::Comp::Components::Properties>(propertyName), object))
            JDM::Base::BaseImage::_setObjectProperties(JSTATICC<JDM::Base::BaseImage::ImageProperties>(propertyName), object);
    }
    JTHIS->setImageSource  (JTHIS->getImageSource());
    JTHIS->_setImageTexture(JTHIS->getSize());
}

JUINT8 *JDM::Comp::Image::getPointerRImage()
{
    JRETURN &JTHIS->_imageColor.r;
}

JUINT8 *JDM::Comp::Image::getPointerGImage()
{
    JRETURN &JTHIS->_imageColor.g;
}

JUINT8 *JDM::Comp::Image::getPointerBImage()
{
    JRETURN &JTHIS->_imageColor.b;
}

JUINT8 *JDM::Comp::Image::getPointerAImage()
{
    JRETURN &JTHIS->_imageColor.a;
}

JCSTR JDM::Comp::Image::getName() JCONST
{
    JRETURN "Image";
}

JCVOID JDM::Comp::Image::update()
{
    JTHIS->_updateImage(JTHIS->getSizePos());
}

JCVOID JDM::Comp::Image::renderComp()
{
    JIF (JDM::IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight()))
    {
        JTHIS->_renderImage    ();
        JTHIS->_renderGradient (JTHIS->getSizePos());
    }
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class Label
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class Label
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::Label::Label(
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
    JDM::Comp::Components(xPos, yPos, width, height)
{
    JTHIS->setTextMessage (text  );
    JTHIS->setImageSource (source);
    JTHIS->_textColor  = color;
    JTHIS->_imageColor = colorImage;
    JTHIS->_arc        = arc;
    JTHIS->_fontSize   = fontSize;
    JTHIS->_halign     = hAlign;
    JTHIS->_valign     = vAlign;
    JTHIS->_setTextTexture  ();
    JTHIS->_setImageTexture (JTHIS->getSize());
}

JDM::Comp::Label::Label(
    JMAP<Properties, JSP<JDM::Object>> mapComponent
)
{
    JFOR (JAUTO [propertyName, object]: mapComponent)
    {
        JIF(!JDM::Comp::Components::setObjectProperties(JSTATICC<JDM::Comp::Components::Properties>(propertyName), object))
            JIF(!JDM::Base::BaseImage::_setObjectProperties(JSTATICC<JDM::Base::BaseImage::ImageProperties>(propertyName), object))
                JDM::Base::BaseText::_setObjectProperties(JSTATICC<JDM::Base::BaseText::TextProperties>(propertyName), object);
    }
    JTHIS->_setTextTexture();
    JTHIS->setImageSource  (JTHIS->getImageSource());
    JTHIS->_setImageTexture(JTHIS->getSize());
}

JUINT8 *JDM::Comp::Label::getPointerRText()
{
    JRETURN &JTHIS->_textColor.r;
}

JUINT8 *JDM::Comp::Label::getPointerGText()
{
    JRETURN &JTHIS->_textColor.g;
}

JUINT8 *JDM::Comp::Label::getPointerBText()
{
    JRETURN &JTHIS->_textColor.b;
}

JUINT8 *JDM::Comp::Label::getPointerAText()
{
    JRETURN &JTHIS->_textColor.a;
}

JUINT8 *JDM::Comp::Label::getPointerRImage()
{
    JRETURN &JTHIS->_imageColor.r;
}

JUINT8 *JDM::Comp::Label::getPointerGImage()
{
    JRETURN &JTHIS->_imageColor.g;
}

JUINT8 *JDM::Comp::Label::getPointerBImage()
{
    JRETURN &JTHIS->_imageColor.b;
}

JUINT8 *JDM::Comp::Label::getPointerAImage()
{
    JRETURN &JTHIS->_imageColor.a;
}

JCVOID JDM::Comp::Label::update()
{
    JTHIS->_updateImage (JTHIS->getSizePos());
    JTHIS->_updateText  (JTHIS->getSizePos());
}

JCVOID JDM::Comp::Label::renderComp()
{
    JIF (JDM::IsTextureInWindow(JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight()))
    {
        JTHIS->_renderImage    ();
        JTHIS->_renderGradient (JTHIS->getSizePos());
        JTHIS->_renderText     ();
    }
}

JCSTR JDM::Comp::Label::getName() JCONST
{
    JRETURN "Label";
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class Button
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class Button
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::Button::Button(
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
    JDM::Font::Valign   vAlign,
    JCONST ColorRGBA    colorClick,
    JCONST ColorRGBA    colorHover
) :
    JDM::Comp::Label(text, source, xPos, yPos, width, height, color, colorImage, arc, fontSize, hAlign, vAlign)
{
    JTHIS->setOriginalColor(colorImage);
    JTHIS->_clickedColor = colorClick;
    JTHIS->_hoverColor   = colorHover;
}

JCBOOL JDM::Comp::Button::mouseDownComp(SDL_MouseButtonEvent &mouse)
{
    JIF (JTHIS->getPickOnBounds())
    {
        JIF(JTHIS->getPickOnTop() && JDM::alreadyTouched)
            JRETURN JFALSE;

        JIF (JTHIS->contains(mouse.x, mouse.y))
        {
            JTHIS->getmouseDownFunction()  (mouse);
            JTHIS->setImageAndOpacityColor (JTHIS->_clickedColor);
            JTHIS->setMouseClick           (JTRUE);
            JDM::alreadyTouched = JTRUE;
            JRETURN JTRUE;
        }
    }
    JRETURN JFALSE;
}

JCVOID JDM::Comp::Button::setOriginalColor(JCONST ColorRGBA &color)
{
    JTHIS->_originalColor = color;
    JTHIS->setImageAndOpacityColor(JTHIS->_originalColor);
}

JCVOID JDM::Comp::Button::setClickedColor(JCONST ColorRGBA &color)
{
    JTHIS->_clickedColor = color;
}

JCVOID JDM::Comp::Button::setHoverColor(JCONST ColorRGBA &color)
{
    JTHIS->_hoverColor = color;
}

JCVOID JDM::Comp::Button::mouseUpComp(SDL_MouseButtonEvent &mouse)
{
    JIF (JTHIS->getMouseClick())
    {
        JIF (JTHIS->_isHoverable)
        {
            JIF (JTHIS->contains(JDM::Mouse::MouseX, JDM::Mouse::MouseY))
            {
                JTHIS->setImageAndOpacityColor(JTHIS->_hoverColor);
            }
            JELSE
                JTHIS->setImageAndOpacityColor(JTHIS->_originalColor);
        }
        JELSE
            JTHIS->setImageAndOpacityColor(JTHIS->_originalColor);
    }
    Label::mouseUpComp(mouse);
}

JCVOID JDM::Comp::Button::update()
{
    Label::update();
    JIF (JTHIS->getMouseClick())
        JRETURN;

    JIF (JTHIS->_isHoverable)
    {
        JIF (JTHIS->contains(JDM::Mouse::MouseX, JDM::Mouse::MouseY))
        {
            JTHIS->setImageAndOpacityColor(JTHIS->_hoverColor);
        }
        JELSE
            JTHIS->setImageAndOpacityColor(JTHIS->_originalColor);
    }
    JELSE
        JTHIS->setImageAndOpacityColor(JTHIS->_originalColor);
}

JCVOID JDM::Comp::Button::setIsHoverable(JCBOOL isHoverable)
{
    JTHIS->_isHoverable = isHoverable;
}

JCBOOL JDM::Comp::Button::getIsHoverable() JCONST
{
    JRETURN JTHIS->_isHoverable;
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * 
 * 
 * 
 *  ----->  @class FocusedTextComponent
 * 
 * 
 * 
 * 
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * PUBLIC SECTION: @class FocusedTextComponent
 */
/////////////////////////////////////////////////////////////////////////////////////////////////

JDM::Comp::FocusedTextComponent::FocusedTextComponent(
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
    JDM::Comp::Label(text, source, xPos, yPos, width, height, color, colorImage, arc, fontSize, hAlign, vAlign)
{ }

JCSTR JDM::Comp::FocusedTextComponent::getName() JCONST
{
    JRETURN "FocusedTextComponent";
}



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

