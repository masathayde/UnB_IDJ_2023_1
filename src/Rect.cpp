#include "Rect.h"

Rect::Rect () {}

Rect::Rect (float iX, float iY, float iW, float iH) {
    x = iX; y = iY; w = iW; h = iH;
}

bool Rect::Contains (float iX, float iY) {
    float borderX = x + w;
    float borderY = y + h;

    if ( iX >= x && iX <= borderX && iY >= y && iY <= borderY) {
        return true;
    } else
        return false;
}

Vec2 Rect::Center () {
    float centerX = x + (w/2.0);
    float centerY = y + (h/2.0);
    return Vec2(centerX, centerY);
}

Rect Rect::TopLeftCornerIfCenterIs (const Vec2& point) {
    Rect TopLeftCorner = *this;
    TopLeftCorner.x = point.x - (w/2);
    TopLeftCorner.y = point.y - (h/2);
    return TopLeftCorner;
}

float Rect::CenterDistanceTo (Rect other) {
    Vec2 thisCenter = Center();
    Vec2 otherCenter = other.Center();
    return thisCenter.DistanceTo(otherCenter);
}

Rect& Rect::AddVec2 (const Vec2& other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}