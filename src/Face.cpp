#include "Face.h"
#include "Sound.h"

Face::Face (GameObject& associated) : Component (associated) {
    hitpoints = 30;
}

void Face::Damage (int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        Sound* sound = (Sound*) associated.GetComponent("Sound");
        if (sound != nullptr) {
            sound->Play(1);
        }
    }
}

void Face::Update (float dt) {

}

void Face::Render () {

}

bool Face::Is (std::string type) {
    return type == "Face";
}