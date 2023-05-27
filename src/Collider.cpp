#include "Collider.h"
#define PI 3.141592653589793238463
#define RADDEGRATIO PI/180
#ifdef DEBUG
#include "Camera.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include "RenderQueue.h"
#endif // DEBUG

Collider::Collider (GameObject& go, Vec2 iScale, Vec2 iOffset) : Component (go) {
    scale = iScale;
    offset = iOffset;
}

void Collider::Update (float dt) {
    box = associated.box;
    box.w *= scale.x;
    box.h *= scale.y;
    float angle = associated.angleDeg * RADDEGRATIO;
    Vec2 newCenter = associated.box.GetCenter() + offset.GetRotated(angle);
    box = box.TopLeftCornerIfCenterIs(newCenter);
}

void Collider::Render () {
#ifdef DEBUG
	// RenderQueue::GetInstance().QueueCollisionBoxRender(box, associated.angleDeg/(180/PI));
	
	// Vec2 center( box.GetCenter() );
	// SDL_Point points[5];

	// Vec2 point = (Vec2(box.x, box.y) - center).GetRotated( associated.angleDeg/(180/PI) )
	// 				+ center - Camera::pos;
	// points[0] = {(int)point.x, (int)point.y};
	// points[4] = {(int)point.x, (int)point.y};
	
	// point = (Vec2(box.x + box.w, box.y) - center).GetRotated( associated.angleDeg/(180/PI) )
	// 				+ center - Camera::pos;
	// points[1] = {(int)point.x, (int)point.y};
	
	// point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( associated.angleDeg/(180/PI) )
	// 				+ center - Camera::pos;
	// points[2] = {(int)point.x, (int)point.y};
	
	// point = (Vec2(box.x, box.y + box.h) - center).GetRotated( associated.angleDeg/(180/PI) )
	// 				+ center - Camera::pos;
	// points[3] = {(int)point.x, (int)point.y};

	// SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	// SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is (std::string type) {
    return type == "Collider";
}

void Collider::SetScale (Vec2 newScale) {
    scale = newScale;
}

void Collider::SetOffset (Vec2 newOffset) {
    offset = newOffset;
}
