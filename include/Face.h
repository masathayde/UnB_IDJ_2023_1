#ifndef FACE_H_
#define FACE_H_
#include "Component.h"


class Face : public Component {
    int hitpoints;

 public:
    Face (GameObject& associated);
    void Damage (int damage);
    void Update (float dt);
    void Render ();
    bool Is (std::string type);
};


#endif