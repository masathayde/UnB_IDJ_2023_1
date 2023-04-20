#ifndef VEC2_H_
#define VEC2_H_

class Vec2 {


 public:
    float x {0}, y {0};
    Vec2 ();
    Vec2 (float x, float y);
    Vec2& GetRotated (float angle);
    Vec2& operator+= (const Vec2& rhs);
    Vec2 operator+ (const Vec2& rhs);
};

#endif