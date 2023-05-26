#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include "RenderQueue.h"
#include <cmath>

Sprite::Sprite (GameObject& associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite (GameObject& associated, std::string file, int iFrameCount, float iFrameTime,
bool animated, bool infinite, float iMaxAnimationLoops, float iSecondsToDie) : Component(associated) {

    texture = nullptr;
    frameCount = iFrameCount;
    frameTime = iFrameTime;
    isAnimated = animated;
    animationIsInfinite = infinite;
    maxAnimationLoops = iMaxAnimationLoops;
    secondsToSelfDestruct = iSecondsToDie;
    Open(file);
}

Sprite::~Sprite () {

}

void Sprite::Open (std::string file) {
    texture = Resources::GetImage(file);
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    width = width / frameCount;
    SetClip(0, 0, width, height);
    associated.box.w = width;
    associated.box.h = height;
}

void Sprite::SetClip (int x, int y, int width, int height) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = width;
    clipRect.h = height;
}

void Sprite::Render () {
    // Render(associated.box.x, associated.box.y);
    RenderQueue& rq = RenderQueue::GetInstance();
    rq.QueueJob(this, associated.box.x, associated.box.y, associated.z, clipRect.x, clipRect.y, clipRect.w, clipRect.h);
}

void Sprite::Render (float x, float y, float z) {
    SDL_Rect dstRect;
    Camera camera;
    dstRect.x = round(x - camera.pos.x);
    dstRect.y = round(y - camera.pos.y);
    dstRect.w = clipRect.w * scale.x;
    dstRect.h = clipRect.h * scale.y;
    // int status = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
    int status = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (status != 0) {
        std::string errormsg(SDL_GetError());
        throw std::runtime_error("Error: SDL_RenderCopy failed with code " + std::to_string(status) + "\nError message from SDL_GetError(): " + errormsg);
    }
    // status = SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &dstRect);
}

int Sprite::GetHeight () {
    return height * scale.y;
}

int Sprite::GetWidth () {
    return width * scale.x;
}

bool Sprite::IsOpen () {
    return texture != nullptr;
}

bool Sprite::Is (std::string type) {
    return type == "Sprite";
}

void Sprite::Update (float dt) {

    float totalTime = (float) frameCount * frameTime;
    timeElapsed = timeElapsed + dt;
    float animationLoops = (timeElapsed/totalTime);

    if (!isAnimated || (!animationIsInfinite && animationLoops >= maxAnimationLoops)) {
        return;
    } 

    timeElapsed = SDL_fmod(timeElapsed, totalTime);

    if (!animationIsInfinite && animationLoops >= maxAnimationLoops) {
        currentFrame = frameCount - 1; // Last frame
    } else {
        currentFrame = (int) SDL_floor(timeElapsed / frameTime);
    }
    SetClip(width*currentFrame, 0, width, height);

    selfDestructCount.Update(dt);
    if (secondsToSelfDestruct > 0 && selfDestructCount.Get() >= secondsToSelfDestruct) {
        associated.RequestDelete();
    }
}

void Sprite::SetScaleX (float scaleX, float scaleY) {
    float newScaleX = scaleX != 0 ? scaleX : scale.x;
    float newScaleY = scaleY != 0 ? scaleY : scale.y;
    scale = Vec2(newScaleX, newScaleY);
    associated.box.w *= scale.x;
    associated.box.h *= scale.y;
}

Vec2 Sprite::GetScale () {
    return scale;
}

void Sprite::SetFrame (int iFrame) {
    currentFrame = iFrame;
}

void Sprite::SetFrameCount (int iFrameCount) {
    frameCount = iFrameCount;
}

void Sprite::SetFrameTime (float iFrameTime) {
    frameTime = iFrameTime;
}