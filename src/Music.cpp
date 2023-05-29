#include "Music.h"
#include "Resources.h"
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
    int status = Mix_PlayMusic(music, times);
    if (status == -1) {
        std::string errormsg(SDL_GetError());
        throw std::runtime_error("Error: Mix_PlayMusic failed\nError message from SDL_GetError(): " + errormsg);
    }
}

void Music::Stop (int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open (std::string file) {
    music = Resources::GetMusic(file).get();
}

bool Music::IsOpen() {
    return music != nullptr;
}

Music::~Music() {
    // Stop(100);
}