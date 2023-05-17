#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include "RenderQueue.h"

Sprite::Sprite (GameObject& associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite (GameObject& associated, std::string file) : Component(associated) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite () {

}

void Sprite::Open (std::string file) {

    texture = Resources::GetImage(file);
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
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
    dstRect.x = x - camera.pos.x;
    dstRect.y = y - camera.pos.y;
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