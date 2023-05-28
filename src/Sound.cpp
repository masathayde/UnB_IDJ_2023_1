#include <iostream>
#include "Sound.h"
#include "Resources.h"

Sound::Sound (GameObject& associated) : Component (associated) {
    chunk = nullptr;
}

Sound::Sound (GameObject& associated, std::string file) : Component (associated) {
    chunk = nullptr;
    Open(file);
}

Sound::~Sound () {
}

void Sound::Play (int times) {
    channel = Mix_PlayChannel(-1, chunk, times);
}

void Sound::Stop () {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open (std::string file) {
    chunk = Resources::GetSound(file).get();
}

bool Sound::Is (std::string type) {
    return type == "Sound";
}

void Sound::Update(float dt) {

}

void Sound::Render () {

}