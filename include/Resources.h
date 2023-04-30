#ifndef RESOURCES_H_
#define RESOURCES_H_
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>
#include <unordered_map>

class Resources {

    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;

 public:
    static SDL_Texture* GetImage (std::string file);
    static void ClearImages ();
    static Mix_Music* GetMusic (std::string file);
    static void ClearMusics ();
    static Mix_Chunk* GetSound (std::string file);
    static void ClearSounds ();
};

#endif