#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <string>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "State.h"

// Singleton.
class Game {

    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
    int frameStart {0};
    float dt {0};
    void CalculateDeltaTime ();
    Game (std::string title, int width, int height);

 public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    float GetDeltaTime ();
};

#endif