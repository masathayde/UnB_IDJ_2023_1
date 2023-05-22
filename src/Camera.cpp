#include "Camera.h"
#include "InputManager.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Game.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);

void Camera::Follow (GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow () {
    focus = nullptr;
    Game::GetInstance().GetState().RemoveCameraFocus();
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
        // Atualizar posição. Sem aceleração.
        pos.x = pos.x + speed.x * dt;
        pos.y = pos.y + speed.y * dt;
    } else {
        // Ver qual é o tamanho da janela.
        // Queremos calcular posição da camera de modo que o objeto foco
        // fique no meio.
        SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
        int width, height;
        SDL_GetRendererOutputSize(renderer, &width, &height);
        Vec2 focusPos = focus->box.GetCenter();
        pos = focusPos - Vec2((float) width/2.0, (float) height/2.0);
    }
}