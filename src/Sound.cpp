#include <iostream>
#include "Sound.h"

Sound::Sound (GameObject& associated) : Component (associated) {
    chunk = nullptr;
}

Sound::Sound (GameObject& associated, std::string file) : Component (associated) {
    chunk = nullptr;
    Open(file);
}

Sound::~Sound () {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }
}

// Temporariamente alterando o retorno da função para int
int Sound::Play (int times) {
    channel = Mix_PlayChannel(-1, chunk, times);
    return channel;
}

void Sound::Stop () {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open (std::string file) {
    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == nullptr) {
        // Failed to Load Sound
        std::string errormsg(SDL_GetError());
        throw std::runtime_error("Error: Mix_LoadWAV failed.\nError message from SDL_GetError(): " + errormsg);
    }
    printf("Chunk: %ld\n", (long int) chunk);
}

bool Sound::Is (std::string type) {
    return type == "Sound";
}

void Sound::Update(float dt) {

}

void Sound::Render () {

}