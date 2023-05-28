#ifndef GAME_H_
#define GAME_H_
#include <string>
#include <stack>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "State.h"

// Singleton.
class Game {

    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* storedState {nullptr};
    std::stack<std::unique_ptr<State>> stateStack;
    int frameStart {0};
    float dt {0};
    void CalculateDeltaTime ();
    Game (std::string title, int width, int height);

 public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetCurrentState();
    static Game& GetInstance();
    float GetDeltaTime ();
    void Push (State* state);
};

#endif