#ifndef COLLIDER_H_
#define COLLIDER_H_
#include "Component.h"

class Collider : public Component {
    Vec2 scale;
    Vec2 offset;

 public:
    Collider (GameObject& associated, Vec2 scale = {1,1}, Vec2 offset = {0,0});
    Rect box;
    void Update (float dt);
    void Render ();
    bool Is (std::string type);
    void SetScale (Vec2 scale);
    void SetOffset (Vec2 offset);
};

#endif