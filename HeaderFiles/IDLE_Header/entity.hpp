#include "JDM/JDM.hpp"

class Entity {
public:
    int SPEED = 0;
    int DAMAGE = 0;
    int HEALTH = 100;
    int DEFENSE = 0;
};

class MainBuilding : public Entity, public JDM::Comp::Image {
public:
    MainBuilding() 
    : JDM::Comp::Image(DefaultImage, -290, 60, 600, 650, JDM::getColorFromHexA("222222")) {
        this->HEALTH = 3000;
        this->DEFENSE = 10;
    }
};

class EnemyEntity : public Entity, public JDM::Comp::Image {
public:
    EnemyEntity()
    : JDM::Comp::Image(DefaultImage, 1200, 620-(5+(Random() % 250)), 75, 100, JDM::getColorFromHexA("ff0000")) {
        this->SPEED = 30;
        this->DAMAGE = 20;
        this->HEALTH = 100;
        this->DEFENSE = Random() % 3;
    }

public:
    void prepareAttack() {}
    const void update() {
        JDM::Comp::Image::update();
        this->setX(this->getX() - (SPEED * JDM::TimeFrame));
    }
};
