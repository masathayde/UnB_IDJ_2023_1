#ifndef BULLET_H_
#define BULLET_H_
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {

    Vec2 speed;
    float distanceLeft;
    int damage;
    float angle;

 public:
    Bullet (GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
    void Update (float dt);
    void Render ();
    bool Is (std::string type);
    int GetDamage ();
};

#endif