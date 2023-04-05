#include <iostream>
#include <string>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Game {

    Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    Game (std::string title, int width, int height);

 public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    Game& GetInstance();

};