#pragma once
#include "JDM/JDM.hpp"

JUSING JNAMESPACE JDM;
JUSING JNAMESPACE JDM::Comp;
JCLASS Template
{
JPUBLIC:
    JSTATIC JCONST std::string WindowTitle;
    JSTATIC JCONST JDM::ColorRGB backGround;
    JSTATIC JCONST JDOUBLE WIDTH;
    JSTATIC JCONST JDOUBLE HEIGHT;

JPROTECTED:
    JCVOID initAllObjects()
    {
        JSP<Button> comp = JMS<Button>("TEST");
        comp->setSizePos({0, 0, WIDTH, HEIGHT});
        comp->setIsHoverable(true);
        Window::addComponents(comp);
    }
    JCVOID update() { }
};
JCONST std::string Template::WindowTitle = "Template";
JCONST JDM::ColorRGB Template::backGround = JDM::getColorFromHex("000000");
JCONST JDOUBLE Template::WIDTH = 500;
JCONST JDOUBLE Template::HEIGHT = 500;
