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