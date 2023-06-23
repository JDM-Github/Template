#include "JDM/Header/JDMlayoutComponents/JDMgridLayout.hpp"
#include "JDM/Header/logger.hpp"

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
        JDM::Base::BaseLayout::addChildren(component, position);
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
    JDM::Base::BaseLayout::_updateComponent();
}

JCVOID JDM::Layout::GridLayout::renderComp()
{
    JDM::Base::BaseLayout::_renderComponent();
}

JCVOID JDM::Layout::GridLayout::mouseUpComp(SDL_MouseButtonEvent & mouse)
{
    JDM::Base::BaseLayout::_mouseUpComp(mouse);
}

JCBOOL JDM::Layout::GridLayout::mouseDownComp(SDL_MouseButtonEvent & mouse)
{
    JDM::Base::BaseLayout::_mouseDownComp(mouse); JRETURN JTRUE;
}

JCVOID JDM::Layout::GridLayout::mouseMotionComp(SDL_MouseMotionEvent &mouse)
{
    JDM::Base::BaseLayout::_mouseMotionComp(mouse);
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
