#ifndef SPRITE_H_
#define SPRITE_H_
#include <string>
#include <iostream>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"

// TODO: Setar largura e altura do box do GameObject baseado no carregado pela
// Sprite em seu construtor.

class Sprite : public Component {

    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;

 public:
    Sprite (GameObject& associated);
    Sprite (GameObject& associated, std::string file);
    ~Sprite();
    void Open (std::string file);
    void SetClip (int x, int y, int w, int h);
    // void Render (int x, int y);
    void Render ();
    void Render (float x, float y);
    int GetWidth ();
    int GetHeight ();
    bool IsOpen ();
    bool Is (std::string type);
    void Update (float dt);
};

#endif