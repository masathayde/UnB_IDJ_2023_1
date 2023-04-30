#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;

SDL_Texture* Resources::GetImage (std::string file) {

    std::unordered_map<std::string,SDL_Texture*>::iterator it;
    it = imageTable.find(file);
    if (it != imageTable.end()) {
        return it->second;
    } else {
        SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if (texture == nullptr) {
            // Failed to Load Texture
            std::string errormsg(SDL_GetError());
            throw std::runtime_error("Error: IMG_LoadTexture failed.\nError message from SDL_GetError(): " + errormsg);
        }
        imageTable.emplace(file, texture);
        return texture;
    }
}

Mix_Music* Resources::GetMusic (std::string file) {
    std::unordered_map<std::string, Mix_Music*>::iterator it;
    it = musicTable.find(file);
    if (it != musicTable.end()) {
        return it->second;
    } else {
        Mix_Music* music = Mix_LoadMUS(file.c_str());
        if (music == nullptr) {
            std::string errormsg(SDL_GetError());
            throw std::runtime_error("Error: Mix_LoadMUS failed.\nError message from SDL_GetError(): " + errormsg);
        }
        musicTable.emplace(file, music);
        return music;
    }
}

Mix_Chunk* Resources::GetSound (std::string file) {
    std::unordered_map<std::string, Mix_Chunk*>::iterator it;
    it = soundTable.find(file);
    if (it != soundTable.end()) {
        return it->second;
    } else {
        Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
        if (chunk == nullptr) {
            // Failed to Load Sound
            std::string errormsg(SDL_GetError());
            throw std::runtime_error("Error: Mix_LoadWAV failed.\nError message from SDL_GetError(): " + errormsg);
        }
        soundTable.emplace(file, chunk);
        return chunk;
    }
}


void Resources::ClearImages () {
    for (auto it : imageTable) {
        SDL_DestroyTexture(it.second);
    }
}

void Resources::ClearMusics () {
    for (auto it : musicTable) {
        Mix_FreeMusic(it.second);
    }
}

void Resources::ClearSounds () {
    for (auto it : soundTable) {
        Mix_FreeChunk(it.second);
    }
}