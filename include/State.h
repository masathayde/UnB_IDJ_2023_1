#ifndef STATE_H_
#define STATE_H_
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include "TileSet.h"
#include <memory>
#include <list>

class State {

    Music music;
    TileSet* bgTileSet;
    bool quitRequested;
    bool started;
    // std::vector<std::unique_ptr<GameObject>> objectArray;
    // std::unordered_map<GameObject*, std::shared_ptr<GameObject>> objectArray;
    std::list<std::shared_ptr<GameObject>> objectArray;
    std::weak_ptr<GameObject> cameraFocus;

    void Input ();
    void UpdateObjects (float dt);
    void EraseObjects ();

 public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start ();
    std::weak_ptr<GameObject> AddObject (GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr (GameObject* go);
    void AddCameraFocus (std::weak_ptr<GameObject> object);
    void RemoveCameraFocus ();

};

#endif