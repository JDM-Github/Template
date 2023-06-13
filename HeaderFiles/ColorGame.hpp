#pragma once
#include "JDM/JDM.hpp"

using namespace JDM;
using namespace JDM::Comp;
using namespace JDM::Canvas;

class ColorGame {
public:
    static const std::string WindowTitle;
    static const JDM::ColorRGB backGround;
    static const double WIDTH;
    static const double HEIGHT;

private:

protected:
    const void initAllObjects() {
        JDM::Window::addComponents(rectangle);
    }
    const void update() { }

};
const std::string ColorGame::WindowTitle = "ColorGame";
const JDM::ColorRGB ColorGame::backGround = JDM::getColorFromHex(JDM::Color::SKY_BLUE);
const double ColorGame::WIDTH = 500;
const double ColorGame::HEIGHT = 500;
