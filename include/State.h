#ifndef STATE_H_
#define STATE_H_
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include "TileSet.h"
#include <memory>

class State {

    Music music;
    TileSet* bgTileSet;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;

    void Input ();
    void AddObject (int mouseX, int mouseY);


 public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

};

#endif