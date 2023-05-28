#include <iostream>
#include "Sound.h"
#include "Resources.h"

Sound::Sound (GameObject& associated) : Component (associated) {
    chunk.reset();
}

Sound::Sound (GameObject& associated, std::string file) : Component (associated) {
    chunk.reset();
    Open(file);
}

Sound::~Sound () {
}

void Sound::Play (int times) {
    channel = Mix_PlayChannel(-1, chunk.get(), times);
}

void Sound::Stop () {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open (std::string file) {
    chunk = Resources::GetSound(file);
}

bool Sound::Is (std::string type) {
    return type == "Sound";
}

void Sound::Update(float dt) {

}

void Sound::Render () {

}