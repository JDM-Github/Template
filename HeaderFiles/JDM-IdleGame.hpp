#pragma once
#include "JDM/JDM.hpp"
#include "HeaderFiles/IDLE_Header/entity.hpp"

class IDLEGame {
public:
    static const std::string WindowTitle;
    static const JDM::ColorRGB backGround;
    static const double WIDTH;
    static const double HEIGHT;

private:
    std::shared_ptr<JDM::Canvas::Rectangle> field = std::make_shared<JDM::Canvas::Rectangle>(0, 720-300, 1200, 300);
    std::shared_ptr<MainBuilding> mainBuilding = std::make_shared<MainBuilding>();
    std::vector<std::shared_ptr<EnemyEntity>> allEnemyEntity;

protected:
    const void initAllObjects() {
        SRand(std::time(NULL));
        JDM::Window::addComponents(field);
        JDM::Window::addComponents(mainBuilding);
        for (int i = 0; i < 1; i++) {
            auto entity = std::make_shared<EnemyEntity>();
            allEnemyEntity.push_back(entity);
            JDM::Window::addComponents(entity);
        }
    }
    const void update() {
    }

private:
};
const std::string IDLEGame::WindowTitle = "IDLE-Game V1";
const JDM::ColorRGB IDLEGame::backGround = {0, 0, 0};
const double IDLEGame::WIDTH = 1200;
const double IDLEGame::HEIGHT = 720;
