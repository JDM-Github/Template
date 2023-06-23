#include "JDM/Header/JDMbaseComponents/JDMbaseLayout.hpp"
#include "JDM/Header/JDMwindow.hpp"

JCVOID JDM::Base::BaseLayout::handleChildren()
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

JCVOID JDM::Base::BaseLayout::_updateComponent()
{
    JFOR (JAUTO comp = JTHIS->_childrens.rbegin(); comp != JTHIS->_childrens.rend(); comp++) 
        (*comp)->updateComp();
}

JCVOID JDM::Base::BaseLayout::_renderComponent()
{
    JFOR (JAUTO comp = JTHIS->_childrens.rbegin(); comp != JTHIS->_childrens.rend(); comp++)
        (*comp)->renderComp();

    JTHIS->handleChildren();
}

JCVOID JDM::Base::BaseLayout::_mouseUpComp(SDL_MouseButtonEvent &mouse)
{
    JFOR (JAUTO comp = JTHIS->_childrens.begin(); comp != JTHIS->_childrens.end(); comp++)
        (*comp)->mouseUpComp(mouse);
}

JCVOID JDM::Base::BaseLayout::_mouseDownComp(SDL_MouseButtonEvent &mouse)
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

JCVOID JDM::Base::BaseLayout::_mouseMotionComp(SDL_MouseMotionEvent &mouse)
{
    JFOR (JAUTO comp = JTHIS->_childrens.begin(); comp != JTHIS->_childrens.end(); comp++)
        (*comp)->mouseMotionComp(mouse);
}

JCVOID JDM::Base::BaseLayout::addChildren(JCONST JSP<JDM::Comp::Components> &component, JUINT position)
{
    JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, position), 'A'));
}

JCVOID JDM::Base::BaseLayout::removeChildren(JCONST JSP<JDM::Comp::Components> &component)
{
    JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, 0), 'R'));
}

JCVOID JDM::Base::BaseLayout::bringToFront(JCONST JSP<JDM::Comp::Components> &component)
{
    JIF (std::find(JTHIS->_childrens.begin(), JTHIS->_childrens.end(), component) != JTHIS->_childrens.end())
    {
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, 0), 'R'));
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, 0), 'A'));
    }
}

JCVOID JDM::Base::BaseLayout::bringToBack(JCONST JSP<JDM::Comp::Components> &component)
{
    JIF (std::find(JTHIS->_childrens.begin(), JTHIS->_childrens.end(), component) != JTHIS->_childrens.end())
    {
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, 0), 'R'));
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, JTHIS->_childrens.size()-1), 'A'));
    }
}

JCVOID JDM::Base::BaseLayout::bringToPosition(JCONST JSP<JDM::Comp::Components> &component, JUINT position)
{
    JIF (std::find(JTHIS->_childrens.begin(), JTHIS->_childrens.end(), component) != JTHIS->_childrens.end())
    {
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, 0), 'R'));
        JTHIS->_allHandlingComponents.push_back(JMPAIR(JMPAIR(component, position), 'A'));
    }
}

JCVOID JDM::Base::BaseLayout::setFunctionAfterHandle(JFUNCCALL function)
{
    JTHIS->_functionAfterHandle = function;
}
