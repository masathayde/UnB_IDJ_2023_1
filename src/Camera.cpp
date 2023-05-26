#include "Camera.h"
#include "InputManager.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Game.h"

std::weak_ptr<GameObject> Camera::focus;
Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);

void Camera::Follow (std::weak_ptr<GameObject> newFocus) {
    focus = newFocus;
}

void Camera::Unfollow () {
    focus.reset();
    Game::GetInstance().GetState().RemoveCameraFocus();
}

void Camera::Update (float dt) {
    // Checar inputs
    if (focus.expired()) {
        Game::GetInstance().GetState().RemoveCameraFocus();
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
        Vec2 focusPos = focus.lock()->box.GetCenter();
        focusPos.y -= 0.1; // hack to fix jittering sprite
        float widthF = width/2;
        float heightF = height/2;
        pos = focusPos - Vec2(widthF, heightF);
    }
}