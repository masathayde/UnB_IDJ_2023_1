#include "Vec2.h"
#include <cmath>

Vec2::Vec2 () {}

Vec2::Vec2 (float iX, float iY) {
    x = iX; y = iY;
}

Vec2 Vec2::GetRotated(float angle) {
    float newX = x * cos(angle) - y * sin(angle);
    float newY = y * cos(angle) + x * sin(angle);
    Vec2 rotatedVec(newX, newY);
    return rotatedVec;
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

Vec2 Vec2::operator- (const Vec2& rhs) {
    Vec2 temp;
    temp.x = x - rhs.x;
    temp.y = y - rhs.y;
    return temp;
}

float Vec2::AngleOfLineTo (const Vec2& other) {
    return atan2(other.y-y, other.x-x);
}

float Vec2::DistanceTo (Vec2& other) {
    Vec2 diff = other - *this;
    return sqrt(pow(diff.x, 2) + pow(diff.y, 2));
}

float Vec2::Magnitude () {
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2& Vec2::operator*= (const int& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}

Vec2& Vec2::operator*= (const float& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}

Vec2 operator* (Vec2 vec, const int& rhs) {
    vec *= rhs;
    return vec;
}

Vec2 operator* (Vec2 vec, const float& rhs) {
    vec *= rhs;
    return vec;
}
