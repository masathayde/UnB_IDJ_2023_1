#ifndef RECT_H_
#define RECT_H_
#include "Vec2.h"

// x,y = coordenadas do canto superior esquerdo
// w,h = largura e altura, a partir da coordenada x,y

class Rect {

 public:
    float x {0}, y {0}, w {0}, h {0};
    Rect ();
    Rect (float x, float y, float w, float h);
    bool Contains (float x, float y);
    Vec2 GetCenter ();
    Rect TopLeftCornerIfCenterIs (const Vec2& point);
    float CenterDistanceTo (Rect other);
    Rect& AddVec2 (const Vec2& other);
};

#endif