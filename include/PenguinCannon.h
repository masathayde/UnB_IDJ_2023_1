#ifndef PENGUINCANNON_H_
#define PENGUINCANNON_H_
#include "Component.h"
#include "Timer.h"

class PenguinCannon : public Component {

    std::weak_ptr<GameObject> pbody;
    float angle {0};
    Timer shotCooldown;
    float cooldownTime {0.333}; // in s

 public:
    
    PenguinCannon (GameObject& associated, std::weak_ptr<GameObject> penguinBody);
    void Update (float dt);
    void Render ();
    bool Is (std::string type);
    void Shoot ();
};

#endif