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
    Vec2 scale {Vec2(1,1)};
    int frameCount;
    float frameTime;
    int currentFrame {0};
    float timeElapsed {0.0};
    float maxAnimationLoops;
    bool isAnimated;
    bool animationIsInfinite;

 public:
    Sprite (GameObject& associated);
    Sprite (GameObject& associated, std::string file, int frameCount = 1, float frameTime = 1.0, bool isAnimated = false, bool isInfinite = false, float maxAnimationLoops = 1);
    ~Sprite();
    void Open (std::string file);
    void SetClip (int x, int y, int w, int h);
    // void Render (int x, int y);
    void Render ();
    void Render (float x, float y, float z = 0);
    int GetWidth ();
    int GetHeight ();
    bool IsOpen ();
    bool Is (std::string type);
    void Update (float dt);
    void SetScaleX (float scaleX, float scaleY);
    Vec2 GetScale ();
    void SetFrame (int frame);
    void SetFrameCount (int frameCount);
    void SetFrameTime (float frameTime);
};

#endif