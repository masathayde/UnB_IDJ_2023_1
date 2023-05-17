#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include <cmath>
#define PI 3.1416
#define DEGRADRATIO 180.0/3.141592653589793238463

Minion::Minion (GameObject& go, std::weak_ptr<GameObject> iAlienCenter, float arcOffSetDeg) : Component (go) {
    if (!iAlienCenter.expired()) {
        alienCenter = iAlienCenter;
    }
    float size = rand() % 6;
    size = (size/10) + 1.0;
    arc = arcOffSetDeg;
    Sprite* sprite = new Sprite(go, "img/minionbullet1.png");
    sprite->SetScaleX(size, size);
    associated.AddComponent(sprite);
    // Calcular box
    associated.box.w = sprite->GetWidth();
    associated.box.h = sprite->GetHeight();
    associated.angleDeg = arc * DEGRADRATIO;
}

void Minion::Update (float dt) {
    // Checar se Alien dono morreru.
    if (alienCenter.expired()) {
        associated.RequestDelete();
        return;
    }

    float angularSpeed = PI/3;
    Vec2 distanceFromAlien(200, 0);
    arc = fmod(arc + angularSpeed * dt, 2 * PI);
    associated.angleDeg = arc * DEGRADRATIO;
    Vec2 position = distanceFromAlien.GetRotated(arc) + (alienCenter.lock())->box.Center();
    associated.box = associated.box.TopLeftCornerIfCenterIs(position);
}

void Minion::Render () {

}

bool Minion::Is (std::string type) {
    return type == "Minion";
}

void Minion::Shoot (Vec2 pos) {
    std::string spriteFile = "img/minionbullet1.png";
    Vec2 currentPos = associated.box.Center();
    float angle = currentPos.AngleOfLineTo(pos);
    GameObject* bulletGo = new GameObject(1);
    Bullet* bullet = new Bullet(*bulletGo, angle, 400, 1, 600, spriteFile);
    bulletGo->AddComponent(bullet);
    bulletGo->box = bulletGo->box.TopLeftCornerIfCenterIs(currentPos);
    Game::GetInstance().GetState().AddObject(bulletGo);
}