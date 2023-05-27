#include "Game.h"
#include "StageState.h"
#include <iostream>

int main (int argc, char** args) {
    try {
        Game& game = Game::GetInstance();
        StageState* stage = new StageState();
        game.Push(stage);
        game.Run();

    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}