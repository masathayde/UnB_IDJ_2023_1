#include "Bullet.h"
#include "Sprite.h"
#define DEGRADRATIO 180.0/3.141592653589793238463

Bullet::Bullet (GameObject& go, float iAngle, float iSpeed, int iDamage, float maxDistance, std::string spriteFile) : Component (go) {
    Sprite* sprite = new Sprite(go, spriteFile);
    associated.AddComponent(sprite);
    speed = Vec2(iSpeed, 0);
    damage = iDamage;
    distanceLeft = maxDistance;
    associated.angleDeg = iAngle * DEGRADRATIO;
    angle = iAngle;
    associated.box.h = sprite->GetHeight();
    associated.box.w = sprite->GetWidth();
}

void Bullet::Update (float dt) {
    Vec2 currentpos = associated.box.Center();
    Vec2 distanceToTravel = speed.GetRotated(angle) * dt;
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