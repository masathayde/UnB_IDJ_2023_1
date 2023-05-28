#ifndef RESOURCES_H_
#define RESOURCES_H_
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>
#include <unordered_map>
#include <memory>

class Resources {

    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;

 public:
    static std::shared_ptr<SDL_Texture> GetImage (std::string file);
    static void ClearImages ();
    static std::shared_ptr<Mix_Music> GetMusic (std::string file);
    static void ClearMusics ();
    static std::shared_ptr<Mix_Chunk> GetSound (std::string file);
    static void ClearSounds ();
    static void ClearAll ();
};

#endif