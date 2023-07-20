#include "JDM/JDM.hpp"
#include "HeaderFiles/Tree.hpp"

using Game = Tree;
class GameWindow : public JDM::Window, public Game {
private:
public:
    GameWindow() : JDM::Window(
        Game::WindowTitle,
        {JDM_UNDEFINED_POS, JDM_UNDEFINED_POS, Game::WIDTH, Game::HEIGHT},
        Game::backGround
    ) { JDM::SETTER::JDMSetFPS(120); }

private:
    const void initAllObjects() { Game::initAllObjects(); }
    const void update() { Game::update(); }
};

int main(int argc, char** argv) {
    std::make_shared<GameWindow>()->run();
    return 0;
}
