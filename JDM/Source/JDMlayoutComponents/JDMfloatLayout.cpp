#include "JDM/Header/JDMlayoutComponents/JDMfloatLayout.hpp"

JCVOID JDM::Layout::FloatLayout::update()
{
    JDM::Base::BaseLayout::_updateComponent();
}

JCVOID JDM::Layout::FloatLayout::renderComp()
{
    JDM::Base::BaseLayout::_renderComponent();
}

JCVOID JDM::Layout::FloatLayout::mouseUpComp(SDL_MouseButtonEvent &mouse)
{
    JDM::Base::BaseLayout::_mouseUpComp(mouse);
}

JCBOOL JDM::Layout::FloatLayout::mouseDownComp(SDL_MouseButtonEvent &mouse)
{
    JDM::Base::BaseLayout::_mouseDownComp(mouse); JRETURN JTRUE;
}

JCVOID JDM::Layout::FloatLayout::mouseMotionComp(SDL_MouseMotionEvent &mouse)
{
    JDM::Base::BaseLayout::_mouseMotionComp(mouse);
}
