#include "JDM/Header/JDMlayout.hpp"
#include "JDM/Header/JDMwindow.hpp"

JCVOID JDM::Layout::BaseLayout::handleChildren()
{
    JFOR (JAUTO &handleComp : JTHIS->_allHandlingComponents)
    {
        JSWITCH (handleComp.second)
        {
            JCASE 'R':
                JTHIS->_childrens.remove(handleComp.first.first);
                JBREAK;
            JCASE 'A':
                JIF (std::find(JTHIS->_childrens.begin(), JTHIS->_childrens.end(), handleComp.first.first) == JTHIS->_childrens.end())
                {
                    JAUTO it = JTHIS->_childrens.begin();
                    std::advance            (it, handleComp.first.second);
                    JTHIS->_childrens.insert (it, handleComp.first.first);
                }
                JBREAK;
        }
    }
    JTHIS->_allHandlingComponents.clear ();
    JTHIS->_functionAfterHandle         ();
    JTHIS->_functionAfterHandle = []() {};
}

JCVOID JDM::Layout::BaseLayout::_updateComponent()
{
    JFOR (JAUTO comp = JTHIS->_childrens.rbegin(); comp != JTHIS->_childrens.rend(); comp++) 
        (*comp)->updateComp();
}

JCVOID JDM::Layout::BaseLayout::_renderComponent()
{
    JFOR (JAUTO comp = JTHIS->_childrens.rbegin(); comp != JTHIS->_childrens.rend(); comp++)
        (*comp)->renderComp();

    JTHIS->handleChildren();
}

JCVOID JDM::Layout::BaseLayout::_mouseUpComp(SDL_MouseButtonEvent &mouse)
{
    JFOR (JAUTO comp = JTHIS->_childrens.begin(); comp != JTHIS->_childrens.end(); comp++)
        (*comp)->mouseUpComp(mouse);
}

JCVOID JDM::Layout::BaseLayout::_mouseDownComp(SDL_MouseButtonEvent &mouse)
{
    JFOR (JAUTO comp = JTHIS->_childrens.begin(); comp != JTHIS->_childrens.end(); comp++)
    {
        JIF (!(*comp)->getDisabled() && (*comp)->mouseDownComp(mouse))
        {
            JAUTO focusedText = JDYNAMICC<JDM::Comp::FocusedTextComponent*>((*comp).get());
            JIF (focusedText != JNULLPTR)
                JDM::Window::focusedTextComponent->isFocused = JTRUE;
        }
    }
}

JCVOID JDM::Layout::BaseLayout::_mouseMotionComp(SDL_MouseMotionEvent &mouse)
{
    JFOR (JAUTO comp = JTHIS->_childrens.begin(); comp != JTHIS->_childrens.end(); comp++)
        (*comp)->mouseMotionComp(mouse);
}

JCVOID JDM::Layout::BaseLayout::addChildren(JCONST JSP<JDM::Comp::Components> &component, JUINT position)
{
    JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, position), 'A'));
}

JCVOID JDM::Layout::BaseLayout::removeChildren(JCONST JSP<JDM::Comp::Components> &component)
{
    JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, 0), 'R'));
}

JCVOID JDM::Layout::BaseLayout::bringToFront(JCONST JSP<JDM::Comp::Components> &component)
{
    JIF (std::find(JTHIS->_childrens.begin(), JTHIS->_childrens.end(), component) != JTHIS->_childrens.end())
    {
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, 0), 'R'));
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, 0), 'A'));
    }
}

JCVOID JDM::Layout::BaseLayout::bringToBack(JCONST JSP<JDM::Comp::Components> &component)
{
    JIF (std::find(JTHIS->_childrens.begin(), JTHIS->_childrens.end(), component) != JTHIS->_childrens.end())
    {
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, 0), 'R'));
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, JTHIS->_childrens.size()-1), 'A'));
    }
}

JCVOID JDM::Layout::BaseLayout::bringToPosition(JCONST JSP<JDM::Comp::Components> &component, JUINT position)
{
    JIF (std::find(JTHIS->_childrens.begin(), JTHIS->_childrens.end(), component) != JTHIS->_childrens.end())
    {
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, 0), 'R'));
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, position), 'A'));
    }
}

JCVOID JDM::Layout::BaseLayout::setFunctionAfterHandle(JFUNCCALL function)
{
    JTHIS->_functionAfterHandle = function;
}

JCVOID JDM::Layout::FloatLayout::update()
{
    BaseLayout::_updateComponent();
}

JCVOID JDM::Layout::FloatLayout::renderComp()
{
    BaseLayout::_renderComponent();
}

JCVOID JDM::Layout::FloatLayout::mouseUpComp(SDL_MouseButtonEvent &mouse)
{
    BaseLayout::_mouseUpComp(mouse);
}

JCBOOL JDM::Layout::FloatLayout::mouseDownComp(SDL_MouseButtonEvent &mouse)
{
    BaseLayout::_mouseDownComp(mouse); JRETURN JTRUE;
}

JCVOID JDM::Layout::FloatLayout::mouseMotionComp(SDL_MouseMotionEvent &mouse)
{
    BaseLayout::_mouseMotionComp(mouse);
}


JDM::Layout::GridLayout::GridLayout(
    JCDOUBLE xPos,
    JCDOUBLE yPos,
    JCDOUBLE width,
    JCDOUBLE height,
    JCUINT8  row,
    JCUINT8  col,
    JCDOUBLE paddWidth,
    JCDOUBLE paddHeight,
    JCDOUBLE spacing
) :
    JDM::Comp::Components(xPos, yPos, width, height)
{
    JTHIS->_rows          = row;
    JTHIS->_cols          = col;
    JTHIS->_paddingWidth  = paddWidth;
    JTHIS->_paddingHeight = paddHeight;
    JTHIS->_spacing       = spacing;
}

JCVOID JDM::Layout::GridLayout::setRows(JUINT8 row)
{
    JTHIS->_rows = row;
}

JCVOID JDM::Layout::GridLayout::setCols(JUINT8 col)
{
    JTHIS->_cols = col;
}

JCVOID JDM::Layout::GridLayout::setPaddingWidth(JDOUBLE paddWidth)
{
    JTHIS->_paddingWidth = paddWidth;
}

JCVOID JDM::Layout::GridLayout::setPaddingHeight(JDOUBLE paddHeight)
{
    JTHIS->_paddingHeight = paddHeight;
}

JCVOID JDM::Layout::GridLayout::setSpacing(JDOUBLE spacing)
{
    JTHIS->_spacing = spacing;
}

JCVOID JDM::Layout::GridLayout::addChildren(JCONST JSP<JDM::Comp::Components> &component, JUINT position)
{
    JIF (JTHIS->_rows*JTHIS->_cols > JTHIS->_childrens.size())
        BaseLayout::addChildren(component, position);
    JELSE
        JDM::Logger("The is ignored, please increase the Cols or Rows before adding children.");
}

JCVOID JDM::Layout::GridLayout::update()
{
    JINT r = 0, c = 0;
    JFOR (JAUTO &comp : JTHIS->_childrens)
    {
        comp->setWidth  (((JTHIS->getWidth() - (JTHIS->_paddingWidth*2)) - (JTHIS->_spacing*(JTHIS->_cols-1))) / JTHIS->_cols);
        comp->setHeight (((JTHIS->getHeight() - (JTHIS->_paddingHeight*2)) - (JTHIS->_spacing*(JTHIS->_rows-1))) / JTHIS->_rows);
        comp->setX      (JTHIS->getX() + JTHIS->_paddingWidth + (comp->getWidth() * c) + (JTHIS->_spacing * c));
        comp->setY      (JTHIS->getY() + JTHIS->_paddingHeight + (comp->getHeight() * r) + (JTHIS->_spacing * r));

        JIF (++c >= JTHIS->_cols)
        {
            c = 0;
            r++;
        }
    }
    BaseLayout::_updateComponent();
}

JCVOID JDM::Layout::GridLayout::renderComp()
{
    BaseLayout::_renderComponent();
}

JCVOID JDM::Layout::GridLayout::mouseUpComp(SDL_MouseButtonEvent & mouse)
{
    BaseLayout::_mouseUpComp(mouse);
}

JCBOOL JDM::Layout::GridLayout::mouseDownComp(SDL_MouseButtonEvent & mouse)
{
    BaseLayout::_mouseDownComp(mouse); JRETURN JTRUE;
}

JCVOID JDM::Layout::GridLayout::mouseMotionComp(SDL_MouseMotionEvent &mouse)
{
    BaseLayout::_mouseMotionComp(mouse);
}

JCUINT8 JDM::Layout::GridLayout::getRows() JCONST
{
    JRETURN JTHIS->_rows;
}

JCUINT8 JDM::Layout::GridLayout::getCols() JCONST
{
    JRETURN JTHIS->_cols;
}

JCDOUBLE JDM::Layout::GridLayout::getPaddingWidth() JCONST
{
    JRETURN JTHIS->_paddingWidth;
}

JCDOUBLE JDM::Layout::GridLayout::getPaddingHeight() JCONST
{
    JRETURN JTHIS->_paddingHeight;
}

JCDOUBLE JDM::Layout::GridLayout::getSpacing() JCONST
{
    JRETURN JTHIS->_spacing;
}

