#include "Sprite.h"
#include "Game.h"



Sprite::Sprite (GameObject& associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite (GameObject& associated, std::string file) : Component(associated) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite () {
    SDL_DestroyTexture(texture);
}

void Sprite::Open (std::string file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    // Como usar o membro de renderer de Game aqui?

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        // Failed to Load Texture
        std::string errormsg(SDL_GetError());
        throw std::runtime_error("Error: IMG_LoadTexture failed.\nError message from SDL_GetError(): " + errormsg);
    }
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

// void Sprite::Render (int x, int y) {

//     SDL_Rect dstRect;
//     dstRect.x = x;
//     dstRect.y = y;
//     dstRect.w = clipRect.w;
//     dstRect.h = clipRect.h;
//     int status = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
//     if (status != 0) {
//         std::string errormsg(SDL_GetError());
//         throw std::runtime_error("Error: SDL_RenderCopy failed with code " + std::to_string(status) + "\nError message from SDL_GetError(): " + errormsg);
//     }
// }

void Sprite::Render () {
    Render(associated.box.x, associated.box.y);
}

void Sprite::Render (float x, float y) {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
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