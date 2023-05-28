#include <iostream>
#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;

std::shared_ptr<SDL_Texture> Resources::GetImage (std::string file) {

    std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator it;
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
        std::shared_ptr<SDL_Texture> texturePtr (texture, [](SDL_Texture* p) {SDL_DestroyTexture(p);});
        imageTable.insert(std::make_pair(file, texturePtr));
        return texturePtr;
    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic (std::string file) {
    std::unordered_map<std::string, std::shared_ptr<Mix_Music>>::iterator it;
    it = musicTable.find(file);
    if (it != musicTable.end()) {
        return it->second;
    } else {
        Mix_Music* music = Mix_LoadMUS(file.c_str());
        if (music == nullptr) {
            std::string errormsg(SDL_GetError());
            throw std::runtime_error("Error: Mix_LoadMUS failed.\nError message from SDL_GetError(): " + errormsg);
        }
        std::shared_ptr<Mix_Music> musicPtr (music, [](Mix_Music* p) {Mix_FreeMusic(p);});
        musicTable.emplace(std::make_pair(file, musicPtr));
        return musicPtr;
    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound (std::string file) {
    std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>::iterator it;
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
        std::shared_ptr<Mix_Chunk> chunkPtr (chunk, [](Mix_Chunk* p) {Mix_FreeChunk(p);});
        soundTable.emplace(file, chunkPtr);
        return chunkPtr;
    }
}


void Resources::ClearImages () {
    std::vector<std::string> imagesToClear;
    for (auto it : imageTable) {
        if (it.second.unique()) {
            imagesToClear.push_back(it.first);
        }
    }
    for (auto name : imagesToClear) {
        imageTable.erase(name);
    }
}

void Resources::ClearMusics () {
    std::vector<std::string> musicsToClear;
    for (auto it : musicTable) {
        if (it.second.unique()) {
            musicsToClear.push_back(it.first);
        }
    }
    for (auto name : musicsToClear) {
        musicTable.erase(name);
    }
}

void Resources::ClearSounds () {
    std::vector<std::string> soundsToClear;
    for (auto it : soundTable) {
        if (it.second.unique()) {
            soundsToClear.push_back(it.first);
        }
    }
    for (auto name : soundsToClear) {
        soundTable.erase(name);
    }
}

void Resources::ClearAll () {
    ClearImages();
    ClearMusics();
    ClearSounds();
}