#include "Vec2.h"
#include <cmath>

Vec2::Vec2 () {}

Vec2::Vec2 (float iX, float iY) {
    x = iX; y = iY;
}

Vec2& Vec2::GetRotated(float angle) {
    float newX = x * cos(angle) - y * sin(angle);
    float newY = y * cos(angle) + x * sin(angle);
    x = newX;
    y = newY;
    return *this;
}

Vec2& Vec2::operator+= (const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2 Vec2::operator+ (const Vec2& rhs) {
    Vec2 temp;
    temp.x = x + rhs.x;
    temp.y = y + rhs.y;
    return temp;
}
