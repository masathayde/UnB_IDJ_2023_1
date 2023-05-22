#include "PenguinCannon.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Game.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#define DEGRADRATIO 180.0/3.141592653589793238463

PenguinCannon::PenguinCannon (GameObject& go, std::weak_ptr<GameObject> penguinBody) : Component (go) {
    pbody = penguinBody;
    Sprite* sprite = new Sprite(associated, "img/cubngun.png");
    associated.AddComponent(sprite);
}


void PenguinCannon::Update (float dt) {
    if (pbody.expired()) {
        associated.RequestDelete();
        return;
    }
    Vec2 pBodyCenter = pbody.lock()->box.GetCenter();
    // associated.box = associated.box.TopLeftCornerIfCenterIs(pBodyCenter);

    InputManager& im = InputManager::GetInstance();
    Camera camera;
    Vec2 mousePos(im.GetMouseX() + camera.pos.x, im.GetMouseY() + camera.pos.y);

    angle = pBodyCenter.AngleOfLineTo(mousePos);
    associated.angleDeg = angle * DEGRADRATIO;

    if (im.MousePress(LEFT_MOUSE_BUTTON)) {
        Shoot();
    }
}

void PenguinCannon::Render () {

}

bool PenguinCannon::Is (std::string type) {
    return type == "PenguinCannon";
}

void PenguinCannon::Shoot () {
    Vec2 bulletSpawnPos = associated.box.GetCenter() + Vec2(50,0).GetRotated(angle);
    std::string bulletSprite = "img/minionbullet2.png";
    GameObject* bulletGo = new GameObject(1);
    Bullet* bullet = new Bullet(*bulletGo, angle, 200, 1, 800, bulletSprite);
    bulletGo->AddComponent(bullet);
    bulletGo->box = bulletGo->box.TopLeftCornerIfCenterIs(bulletSpawnPos);
    Game::GetInstance().GetState().AddObject(bulletGo);
}