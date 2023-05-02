#ifndef CAMERA_H_
#define CAMERA_H_
#include "GameObject.h"
#include "Vec2.h"

class Camera {
    static GameObject* focus;

 public:
    static Vec2 pos;
    static Vec2 speed;
    static void Follow (GameObject* newFocus);
    static void Unfollow ();
    static void Update (float dt);
};

#endif