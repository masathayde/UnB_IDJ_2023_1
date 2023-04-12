#ifndef SPRITE_H_
#define SPRITE_H_
#include <string>
#include <iostream>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Sprite {

    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;

 public:
    Sprite ();
    Sprite (std::string file);
    ~Sprite();
    void Open (std::string file);
    void SetClip (int x, int y, int w, int h);
    void Render (int x, int y);
    int GetWidth ();
    int GetHeight ();
    bool IsOpen ();
};

#endif