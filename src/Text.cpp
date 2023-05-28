#include "Text.h"
#include "RenderQueue.h"
#include "Resources.h"
#include "Game.h"
#include <iostream>

Text::Text (GameObject& go, std::string ifontFile, int ifontSize,
TextStyle istyle, std::string itext, SDL_Color icolor) : Component (go) {

    fontFile = ifontFile;
    fontSize = ifontSize;
    style = istyle;
    text = itext;
    color = icolor;
    texture = nullptr;
    RemakeTexture ();
}

Text::~Text () {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update (float dt) {

}

void Text::Render () {
    RenderQueue& rq = RenderQueue::GetInstance();
    rq.QueueJob(texture, associated.box.x, associated.box.y, associated.z, 0, 0, associated.box.w, associated.box.h);
}

bool Text::Is (std::string type) {
    return type == "Text";
}

void Text::SetText (std::string itext) {
    text = itext;
    RemakeTexture();
}

void Text::SetColor (SDL_Color icolor) {
    color = icolor;
    RemakeTexture();
}

void Text::SetStyle (TextStyle istyle) {
    style = istyle;
    RemakeTexture();
}

void Text::SetFontSize (int ifontSize) {
    fontSize = ifontSize;
    RemakeTexture();
}

void Text::SetFontFile (std::string ifontFile) {
    fontFile = ifontFile;
    RemakeTexture();
}

void Text::RemakeTexture () {
    font = Resources::GetFont(fontFile, fontSize).get();
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    SDL_Surface* textSurface;
    switch (style) {
        default:
        case SOLID:
            textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;
        case SHADED:
            textSurface = TTF_RenderText_Shaded(font, text.c_str(), color, ChooseColor(BLACK_TEXT));
            break;
        case BLENDED:
            textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
            break;
    }
    if (textSurface == NULL) {
        std::string errormsg(SDL_GetError());
        throw std::runtime_error("Error: TTF_RenderText failed\nError message from SDL_GetError(): " + errormsg);
    }
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), textSurface);
    if (texture == NULL) {
        std::string errormsg(SDL_GetError());
        throw std::runtime_error("Error: SDL_CreateTextureFromSurface failed\nError message from SDL_GetError(): " + errormsg);
    }
    int width, height;
    int status = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    if (status != 0) {
        std::string errormsg(SDL_GetError());
        throw std::runtime_error("Error: SDL_QueryTexture failed\nError message from SDL_GetError(): " + errormsg);
    }
    associated.box.w = width;
    associated.box.h = height;
}

SDL_Color Text::ChooseColor (CommonTextColor colorName) {
    SDL_Color newColor;
    switch (colorName) {
        default:
        case WHITE_TEXT:
            newColor = {255, 255, 255, 255};
            break;
        case BLACK_TEXT:
            newColor = {0, 0, 0, 255};
            break;
    }
    return newColor;
}
