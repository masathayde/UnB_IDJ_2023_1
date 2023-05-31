#ifndef TITLESTATE_H_
#define TITLESTATE_H_
#include "State.h"
#include <memory>

class TitleState : public State {
    float textTimer {0.0};
    float textDisplayTime {0.7};
    bool textShowing {false};
    std::weak_ptr<GameObject> titleTextGO;

    void EraseObjects ();

 public:
    TitleState ();
    ~TitleState ();
    void LoadAssets ();
    void Update (float dt);
    void Render (float alpha = 1.0);
    void Start ();
    void Pause ();
    void Resume ();
};

#endif