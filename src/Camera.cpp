#include "Camera.h"
#include "InputManager.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);

void Camera::Follow (GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow () {
    focus = nullptr;
}

void Camera::Update (float dt) {
    // Checar inputs
    if (focus == nullptr) {

        InputManager& im = InputManager::GetInstance();

        if (im.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed.x = 200;
        } else if (im.IsKeyDown(LEFT_ARROW_KEY)) {
            speed.x = -200;
        } else {
            speed.x = 0;
        }

        if (im.IsKeyDown(DOWN_ARROW_KEY)) {
            speed.y = 200;
        } else if (im.IsKeyDown(UP_ARROW_KEY)) {
            speed.y = -200;
        } else {
            speed.y = 0;
        }
    }
    // Atualizar posição. Sem aceleração.
    pos.x = pos.x + speed.x * dt;
    pos.y = pos.y + speed.y * dt;

    // printf("Camera pos: %f %f\n", pos.x, pos.y);
}