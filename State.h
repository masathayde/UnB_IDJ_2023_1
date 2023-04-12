#ifndef STATE_H_
#define STATE_H_
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class State {

    Sprite bg;
    Music music;
    bool quitRequested;

 public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

};

#endif