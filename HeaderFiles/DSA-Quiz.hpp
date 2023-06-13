#pragma once
#include "JDM/JDM.hpp"

using namespace JDM;
using namespace JDM::Comp;
class DSAQuiz {
public:
    static const std::string WindowTitle;
    static const JDM::ColorRGB backGround;
    static const double WIDTH;
    static const double HEIGHT;

protected:
    std::shared_ptr<Label> label = std::make_shared<Label>("TEST QUESTION FREAKING QUESTION");

    const void initAllObjects() {
        label->setImageColor(JDM::getColorFromHex("dddddd"));
        label->setBold(true);
        label->setSize({700, 250});
        label->setHalign(JDM::Font::LEFT);
        label->setPaddingWidth(20);
        label->setPos({50, 25});

        JDM::Window::addComponents(label);
    }
    const void update() {

    }

};
const std::string DSAQuiz::WindowTitle = "DSAQuiz";
const JDM::ColorRGB DSAQuiz::backGround = JDM::getColorFromHex("ffffff");
const double DSAQuiz::WIDTH = 800;
const double DSAQuiz::HEIGHT = 600;
