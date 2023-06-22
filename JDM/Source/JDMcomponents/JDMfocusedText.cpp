#include "JDM/Header/JDMcomponents/JDMfocusedText.hpp"
#include "JDM/Header/JDMfunctions.hpp"
#include "JDM/Header/JDMinclude.hpp"

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