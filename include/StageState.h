#ifndef STAGESTATE_H_
#define STAGESTATE_H_
#include "State.h"
#include "Music.h"
#include "TileSet.h"

class StageState : public State {
 protected:

  Music music;
  TileSet* bgTileSet;
  std::weak_ptr<GameObject> cameraFocus;
  std::weak_ptr<GameObject> player;

  void Input ();
  void UpdateArray (float dt);
  void EraseObjects ();
  void CheckCollision ();
  void RecordPreviousPosOfObjects ();

  void PrintDebugInfo ();

 public:
  StageState ();
  ~StageState ();
  void LoadAssets ();
  void Update (float dt);
  void Render (float alpha = 1.0);
  void Start ();
  void Pause ();
  void Resume ();

  void AddCameraFocus (std::weak_ptr<GameObject> object);
  void RemoveCameraFocus ();
};

#endif