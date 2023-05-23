#include "Bullet.h"
#define DEGRADRATIO 180.0/3.141592653589793238463

Bullet::Bullet (GameObject& go, float angle, float iSpeed, int iDamage, float maxDistance, Sprite* sprite) : Component (go) {
    sprite->SetScaleX(2,2);
    associated.AddComponent(sprite);
    speed = Vec2(iSpeed, 0).GetRotated(angle);
    damage = iDamage;
    distanceLeft = maxDistance;
    associated.angleDeg = angle * DEGRADRATIO;
    associated.box.h = sprite->GetHeight();
    associated.box.w = sprite->GetWidth();
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