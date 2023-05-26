#ifndef PENGUINBODY_H_
#define PENGUINBODY_H_
#include "Component.h"

class PenguinBody : public Component {

    std::weak_ptr<GameObject> pcannon;
    Vec2 speed {Vec2(0,0)};
    float linearSpeed {0};
    float angle {0};
    int hp;
    float maxSpeed {400};
    float minSpeed {-400};
    float accel {25};

 public:
    PenguinBody (GameObject& associated);
    ~PenguinBody ();
    void Start ();
    void Update (float dt);
    void Render ();
    bool Is (std::string type);
    void NotifyCollision (GameObject& other);
    static PenguinBody* player;
    Rect GetPos ();
};

#endif