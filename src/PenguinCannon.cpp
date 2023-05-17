#include "PenguinCannon.h"

PenguinCannon::PenguinCannon (GameObject& go, std::weak_ptr<GameObject> penguinBody) : Component (go) {
    pbody = penguinBody;
}


void PenguinCannon::Update (float dt) {

}

void PenguinCannon::Render () {

}

bool PenguinCannon::Is (std::string type) {
    return type == "PenguinCannon";
}

void PenguinCannon::Shoot () {

}