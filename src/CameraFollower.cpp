#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower (GameObject& gObject) : Component (gObject) {

}

void CameraFollower::Update (float dt) {
    Camera camera;
    associated.box.x = camera.pos.x;
    associated.box.y = camera.pos.y; 
}

void CameraFollower::Render () {

}

bool CameraFollower::Is (std::string type) {
    return type == "CameraFollower";
}