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
        JSP<Text> comp = JMS<Text>(
            JMAP<Text::Properties, JSP<Object>> {
            { Text::TEXT,           JMS<String> ("TEST"  )},
            { Text::X,              JMS<Integer>(50      )},
            { Text::Y,              JMS<Integer>(50      )},
            { Text::TEXT_COLOR_STR, JMS<String> ("ffffff")}
        });
        Window::addComponents(comp);
    }
    JCVOID update() { }
};
JCONST std::string Template::WindowTitle = "Template";
JCONST JDM::ColorRGB Template::backGround = JDM::getColorFromHex("000000");
JCONST JDOUBLE Template::WIDTH = 500;
JCONST JDOUBLE Template::HEIGHT = 500;
