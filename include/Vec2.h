#ifndef VEC2_H_
#define VEC2_H_

class Vec2 {
 public:
    float x {0}, y {0};
    Vec2 ();
    Vec2 (float x, float y);
    Vec2 GetRotated (float angle);
    float AngleOfLineTo (const Vec2& other);
    float DistanceTo (Vec2& other);
    float Magnitude ();
    Vec2& operator+= (const Vec2& rhs);
    Vec2 operator+ (const Vec2& rhs);
    Vec2 operator- (const Vec2& rhs);
    Vec2& operator*= (const int& rhs);
    friend Vec2 operator* (Vec2 vec, const int& rhs);
    Vec2& operator*= (const float& rhs);
    friend Vec2 operator* (Vec2 vec, const float& rhs);
};

#endif