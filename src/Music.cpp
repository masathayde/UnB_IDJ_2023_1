#include "Music.h"
#include <iostream>

Music::Music () {
    music = nullptr;
}

Music::Music (std::string file) {
    Open(file);
}

void Music::Play (int times) {
    if (music == nullptr) {
        throw std::runtime_error("Error: music pointer is null.");
    }
    Mix_PlayMusic(music, times);
}

void Music::Stop (int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open (std::string file) {
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::string errormsg(SDL_GetError());
        throw std::runtime_error("Error: Mix_LoadMUS failed.\nError message from SDL_GetError(): " + errormsg);
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}

Music::~Music() {
    Stop(0);
    Mix_FreeMusic(music);
}