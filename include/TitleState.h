#ifndef TITLESTATE_H_
#define TITLESTATE_H_
#include "State.h"

class TitleState : public State {
    float textTimer {0.0};
    float textDisplayTime {0.7};
    bool textShowing {false};
    GameObject* titleTextGO {nullptr};

    void EraseObjects ();

 public:
    TitleState ();
    ~TitleState ();
    void LoadAssets ();
    void Update (float dt);
    void Render ();
    void Start ();
    void Pause ();
    void Resume ();
};

#endif