#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#define DEGRADRATIO 180.0/3.141592653589793238463

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody (GameObject& go) : Component (go) {
    player = this;
}

PenguinBody::~PenguinBody () {
    player = nullptr;
}

void PenguinBody::Start () {
    GameObject* cannonGO = new GameObject(1);
    std::weak_ptr<GameObject> pBodyPtr = Game::GetInstance().GetState().GetObjectPtr(&associated);
    PenguinCannon* newCannon = new PenguinCannon (*cannonGO, pBodyPtr);
    cannonGO->AddComponent(newCannon);
    pcannon = Game::GetInstance().GetState().AddObject(cannonGO);
}

void PenguinBody::Update (float dt) {
    InputManager& im = InputManager::GetInstance();

    float angularSpeed = 3.1416;

    if (im.IsKeyDown(SDLK_w)) {
        linearSpeed += accel;
        linearSpeed = linearSpeed > maxSpeed ? maxSpeed : linearSpeed;
    } else if (im.IsKeyDown(SDLK_s)) {
        linearSpeed -= accel;
        linearSpeed = linearSpeed < minSpeed ? minSpeed : linearSpeed;
    }

    if (im.IsKeyDown(SDLK_a)) {
        angle = SDL_fmod(angle - angularSpeed, 2 * 3.1416);
    } else if (im.IsKeyDown(SDLK_d)) {
        angle = SDL_fmod(angle + angularSpeed, 2 * 3.1416);
    }
    associated.angleDeg = angle * DEGRADRATIO;
    Vec2 currentPos = associated.box.Center();
    Vec2 speedVec(linearSpeed, 0);
    currentPos = currentPos + speedVec.GetRotated(angle) * dt;
    associated.box = associated.box.TopLeftCornerIfCenterIs(currentPos);

    if (hp <= 0) {
        associated.RequestDelete();
    }

}

void PenguinBody::Render () {

}

bool PenguinBody::Is (std::string type) {
    return type == "PenguinBody";
}