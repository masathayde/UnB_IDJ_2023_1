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
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;
    int status = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
    if (status != 0) {
        std::string errormsg(SDL_GetError());
        throw std::runtime_error("Error: SDL_RenderCopy failed with code " + std::to_string(status) + "\nError message from SDL_GetError(): " + errormsg);
    }
}

int Sprite::GetHeight () {
    return height;
}

int Sprite::GetWidth () {
    return width;
}

bool Sprite::IsOpen () {
    return texture != nullptr;
}

bool Sprite::Is (std::string type) {
    return type == "Sprite";
}

void Sprite::Update (float dt) {

}