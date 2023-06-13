#pragma once
#include "JDM/JDM.hpp"

using namespace JDM;
using namespace JDM::Comp;
using namespace JDM::Canvas;

const double cardWidth = (800-(8*10)) / 7.0;
const double cardHeight = cardWidth * 1.5;

enum CardDesign {
    HEART,
    GLOVE,
    DIAMOND,
    SPADE
};

class Solitaire {
public:
    static const std::string WindowTitle;
    static const JDM::ColorRGB backGround;
    static const double WIDTH;
    static const double HEIGHT;

private:

private:
    class Card : public Image {
    public:
        CardDesign cardSign;
        bool flipped = true;
        double dragX = 0;
        double dragY = 0;

        Solitaire *solitaire = nullptr;
        std::shared_ptr<Rectangle> rect;
        std::shared_ptr<Image> design;

        Card(Solitaire *solitaire, CardDesign sign, int number)
        : solitaire(solitaire), cardSign(sign), Image(DefaultImage, 100 + (10 * (6 + 1)) + cardWidth * 6, 10, cardWidth, cardHeight, JDM::getColorFromHexA(JDM::Color::GHOST_WHITE)) {
            rect = std::make_shared<Rectangle>(this->getX() - 2, this->getY() - 2, cardWidth + 4, cardHeight + 4, JDM::getColorFromHexA("445577"));
            design = std::make_shared<Image>("Assets/cardDesign.png", this->getX() + (cardWidth * 0.25), this->getY() + (cardHeight / 2 - cardWidth * 0.25), cardWidth * 0.5, cardWidth * 0.5);

            design->setImageRegion({(250*sign), 0, 250, 250});
            this->setRendering(false);
            design->setRendering(false);

            this->setPickOnTop(true);
            rect->setPickOnBounds(false);
            design->setPickOnBounds(false);

            this->setmouseDownFunction(std::bind([](SDL_MouseButtonEvent &mouse, Card *card){
                card->dragX = mouse.x - card->getX();
                card->dragY = mouse.y - card->getY();
            }, std::placeholders::_1, this));

            this->setmouseMotionFunction(std::bind([](SDL_MouseMotionEvent &mouse, Card *card){
                card->setX(mouse.x - card->dragX);
                card->setY(mouse.y - card->dragY);
                card->rect->setX(card->getX()-2);
                card->rect->setY(card->getY()-2);
                card->design->setX(card->getX() + (cardWidth * 0.25));
                card->design->setY(card->getY() + (cardHeight / 2 - cardWidth * 0.25));
            }, std::placeholders::_1, this));
        }
    public:
        const void update() {
            Image::update();
            if (this->flipped) { this->setRendering(true); design->setRendering(true); }
            else { this->setRendering(false); design->setRendering(false); }
        }
    };
    class CardStacker : public Rectangle {
    public:
        int position;
        CardStacker(int pos)
            : Rectangle(100 + (10 * (pos + 1)) + cardWidth * pos, 20 + cardHeight, cardWidth, cardHeight, JDM::getColorFromHexA(JDM::Color::LIME_GREEN)) {
            this->position = pos;
        }
    };
    std::vector<std::vector<std::shared_ptr<Card>>> allCards;
    std::vector<std::shared_ptr<CardStacker>> allStacker;

protected:
    const void initAllObjects() {
        for (int i = 0; i < 7; i++) {
            auto stacker = std::make_shared<CardStacker>(i);
            JDM::Window::addComponents(stacker);
        }
        for (int i = 0; i < 4; i++) {
            std::vector<std::shared_ptr<Card>> vecCard;
            for (int j = 0; j < 13; j++) {
                auto card = std::make_shared<Card>(this, static_cast<CardDesign>(i));
                JDM::Window::addComponents(card->rect);
                JDM::Window::addComponents(card);
                JDM::Window::addComponents(card->design);
                vecCard.push_back(card);
            }
            allCards.push_back(vecCard);
        }
    }
    const void update() { }

};
const std::string Solitaire::WindowTitle = "Solitaire";
const JDM::ColorRGB Solitaire::backGround = JDM::getColorFromHex(JDM::Color::DARK_GREEN);
const double Solitaire::WIDTH = 1000;
const double Solitaire::HEIGHT = 700;
