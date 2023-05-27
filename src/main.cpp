#include "Game.h"
#include "TitleState.h"
#include "StageState.h"
#include <iostream>

int main (int argc, char** args) {
    try {
        Game& game = Game::GetInstance();
        TitleState* title = new TitleState();
        game.Push(title);
        game.Run();
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}