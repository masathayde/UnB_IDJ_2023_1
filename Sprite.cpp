#include "Sprite.h"

Sprite::Sprite () {
    texture = nullptr;
}

Sprite::Sprite (std::string file) {
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
    texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr) {
        // Failed to Load Texture
        std::string errormsg(SDL_GetError());
        throw std::runtime_error("Error: IMG_LoadTexture failed.\nError message from SDL_GetError(): " + errormsg);
    }
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

}