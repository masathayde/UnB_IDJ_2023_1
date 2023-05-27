#include "Game.h"
#include "Resources.h"
#include "InputManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Game* Game::instance = nullptr;

Game& Game::GetInstance() {
    if (Game::instance == nullptr)
        Game::instance = new Game("title", 1024, 600);

    return *Game::instance;
}

Game::Game (string title, int width, int height) {

    if (Game::instance != nullptr) {
        // Something went wrong. Trying to create another instance of a singleton class.
        throw std::runtime_error("Error: Cannot create another instance of singleton class");
    }
    Game::instance = this;
    srand(time(NULL));

    int status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (status != 0) {
        // SDL_Init failed. We retrieve the error message.
        string errormsg(SDL_GetError());
        throw std::runtime_error("Error: SDL_Init failed with code " + to_string(status) + "\nError message from SDL_GetError(): " + errormsg);
    }

    // TODO: Add error treatment later.
    status = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    status = Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
    status = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    status = Mix_AllocateChannels(32);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Game::~Game () {
    // Cleanup.
    if (storedState != nullptr) {
        delete storedState;
    }

    while (!stateStack.empty()) {
        stateStack.pop();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

State& Game::GetCurrentState () {
    if (stateStack.empty()) {
        throw std::runtime_error ("Error: Calling GetCurrentState() when state stack is empty");
    }
    return *stateStack.top();
}

void Game::Push (State* state) {
    storedState = state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run () {
    if (storedState == nullptr)
        return;

    stateStack.emplace(storedState);
    storedState = nullptr;
    stateStack.top()->Start();
    while (!stateStack.empty() && stateStack.top()->QuitRequested() == false) {
        if (stateStack.top()->PopRequested()) {
            stateStack.pop();
            if (!stateStack.empty()) {
                stateStack.top()->Resume();
            } else {
                break;
            }
        }
        if (storedState != nullptr) {
            stateStack.top()->Pause();
            stateStack.emplace(storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }
        
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        stateStack.top()->Update(dt);
        stateStack.top()->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

void Game::CalculateDeltaTime () {
    dt = ((float) SDL_GetTicks() - (float) frameStart) / 1000; // ms to s
    frameStart = SDL_GetTicks();
}

float Game::GetDeltaTime () {
    return dt;
}