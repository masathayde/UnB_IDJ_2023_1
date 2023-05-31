#ifndef ENDSTATE_H_
#define ENDSTATE_H_
#include "State.h"
#include "Music.h"

class EndState : public State {

    Music backgroundMusic;
    float textTimer {0.0};
    float textDisplayTime {0.7};
    bool textShowing {false};
    GameObject* titleTextGO {nullptr};

    void EraseObjects ();

 public:
    EndState ();
    ~EndState ();

    void LoadAssets ();
    void Update (float dt);
    void Render (float alpha = 1.0);
    void Start ();
    void Pause ();
    void Resume ();
};

#endif