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
    arc = arcOffSetDeg;
    Sprite* sprite = new Sprite(go, "img/minion.png");
    associated.AddComponent(sprite);
    // Calcular box
}

void Minion::Update (float dt) {
    // Checar se Alien dono morreru.
    if (alienCenter.expired()) {
        associated.RequestDelete();
        return;
    }

    float angularSpeed = PI/2;
    Vec2 distanceFromAlien(200, 0);
    arc = fmod(arc + angularSpeed * dt, 2 * PI);
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
    Bullet* bullet = new Bullet(*bulletGo, angle, 200, 1, 600, spriteFile);
    bulletGo->AddComponent(bullet);
    bulletGo->box = bulletGo->box.TopLeftCornerIfCenterIs(currentPos);
    Game::GetInstance().GetState().AddObject(bulletGo);
}