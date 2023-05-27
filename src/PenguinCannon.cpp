#include "PenguinCannon.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#define DEGRADRATIO 180.0/3.141592653589793238463

PenguinCannon::PenguinCannon (GameObject& go, std::weak_ptr<GameObject> penguinBody) : Component (go) {
    pbody = penguinBody;
    Sprite* sprite = new Sprite(associated, "img/cubngun.png");
    associated.AddComponent(sprite);
    Collider* collider = new Collider(go);
    associated.AddComponent(collider);
    shotCooldown.Update(cooldownTime);
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

    shotCooldown.Update(dt);
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
    if (shotCooldown.Get() < cooldownTime) {
        return;
    }
    shotCooldown.Restart();
    Vec2 bulletSpawnPos = associated.box.GetCenter() + Vec2(50,0).GetRotated(angle);
    std::string spriteFile = "img/penguinbullet.png";
    GameObject* bulletGo = new GameObject(1);
    Sprite* sprite = new Sprite(*bulletGo, spriteFile, 4, 0.2, true, false, 1);
    new Bullet(*bulletGo, angle, 250, 1, 800, sprite, false);
    bulletGo->box = bulletGo->box.TopLeftCornerIfCenterIs(bulletSpawnPos);
    Game::GetInstance().GetCurrentState().AddObject(bulletGo);
}