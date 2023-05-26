#include "Bullet.h"
#include "Collider.h"
#define DEGRADRATIO 180.0/3.141592653589793238463

Bullet::Bullet (GameObject& go, float angle, float iSpeed, int iDamage, float maxDistance, Sprite* sprite, bool iTargetsPlayer) : Component (go) {
    sprite->SetScaleX(2,2);
    associated.AddComponent(sprite);
    speed = Vec2(iSpeed, 0).GetRotated(angle);
    damage = iDamage;
    distanceLeft = maxDistance;
    targetsPlayer = iTargetsPlayer;
    associated.angleDeg = angle * DEGRADRATIO;
    associated.box.h = sprite->GetHeight();
    associated.box.w = sprite->GetWidth();

    Collider* collider = new Collider(go);
    associated.AddComponent(collider);
}

void Bullet::Update (float dt) {
    Vec2 currentpos = associated.box.GetCenter();
    Vec2 distanceToTravel = speed * dt;
    currentpos += distanceToTravel;
    distanceLeft -= distanceToTravel.Magnitude();
    associated.box = associated.box.TopLeftCornerIfCenterIs(currentpos);
    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render () {

}

bool Bullet::Is (std::string type) {
    return type == "Bullet";
}

int Bullet::GetDamage () {
    return damage;
}

void Bullet::NotifyCollision (GameObject& other) {
    // No momento, Bullet só se importa com Minions, Aliens e PenguinBody
    if (targetsPlayer) {
        Component* component = nullptr;
        component = other.GetComponent("PenguinBody");
        if (component != nullptr) {
            associated.RequestDelete();
        }
    } else {
        Component* component = nullptr;
        component = other.GetComponent("Alien");
        if (component != nullptr) {
            associated.RequestDelete();
        }
    }
}