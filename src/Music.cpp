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
    Mix_PlayMusic(music.get(), times);
}

void Music::Stop (int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open (std::string file) {
    music = Resources::GetMusic(file);
}

bool Music::IsOpen() {
    return music != nullptr;
}

Music::~Music() {
    Stop(0);
}