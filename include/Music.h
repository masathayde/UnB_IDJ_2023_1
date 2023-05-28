#ifndef MUSIC_H_
#define MUSIC_H_
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>

class Music {

    Mix_Music* music;

 public:
    Music();
    ~Music();
    Music(std::string file);
    void Play (int times = -1);
    void Stop (int msToStop = 1500);
    void Open (std::string file);
    bool IsOpen ();
};

#endif