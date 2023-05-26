#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "Collider.h"
#include "Bullet.h"
#define DEGRADRATIO 180.0/3.141592653589793238463

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody (GameObject& go) : Component (go) {
    player = this;
    associated.AddComponent(this);
    Sprite* sprite = new Sprite(associated, "img/penguin.png");
    associated.AddComponent(sprite);
    Collider* collider = new Collider(go);
    associated.AddComponent(collider);
}

PenguinBody::~PenguinBody () {
    player = nullptr;
    Camera::Unfollow();
}

void PenguinBody::Start () {
    GameObject* cannonGO = new GameObject(associated.z + 1);
    std::weak_ptr<GameObject> pBodyPtr = Game::GetInstance().GetState().GetObjectPtr(&associated);
    PenguinCannon* newCannon = new PenguinCannon (*cannonGO, pBodyPtr);
    cannonGO->AddComponent(newCannon);
    Vec2 bodyCenter = associated.box.GetCenter();
    cannonGO->box = cannonGO->box.TopLeftCornerIfCenterIs(bodyCenter);
    pcannon = Game::GetInstance().GetState().AddObject(cannonGO);
    Game::GetInstance().GetState().cannon = pcannon;
}

void PenguinBody::Update (float dt) {
    InputManager& im = InputManager::GetInstance();

    float angularSpeed = 3.1416/25.0;

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
    Vec2 currentPos = associated.box.GetCenter();
    Vec2 speedVec(linearSpeed, 0);
    currentPos = currentPos + speedVec.GetRotated(angle) * dt;
    associated.box = associated.box.TopLeftCornerIfCenterIs(currentPos);
    // Atualizando posição do canhão.
    if (pcannon.expired() == false) {
        pcannon.lock()->box = pcannon.lock()->box.TopLeftCornerIfCenterIs(currentPos);
        // Hack para consertar tremida
        pcannon.lock()->box.x -= 0.2;
    }

    if (hp <= 0) {
        associated.RequestDelete();
    }
}

void PenguinBody::Render () {

}

bool PenguinBody::Is (std::string type) {
    return type == "PenguinBody";
}

void PenguinBody::NotifyCollision (GameObject& other) {
    Bullet* bullet = (Bullet*) other.GetComponent("Bullet");
    if (bullet != nullptr && bullet->targetsPlayer) {
        this->hp -= bullet->GetDamage();
    }
}