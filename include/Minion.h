#ifndef MINION_H_
#define MINION_H_
#include "Component.h"
#include "GameObject.h"

class Minion : public Component {

    std::weak_ptr<GameObject> alienCenter;
    float arc;

 public:
    
    Minion (GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
    void Update (float dt);
    void Render ();
    bool Is (std::string type);
    void Shoot (Vec2 target);
};

#endif