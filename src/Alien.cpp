#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include <math.h>

Alien::Alien (GameObject& go, int i_nMinions) : Component(go) {
    Sprite* sprite = new Sprite(go, "img/alien.png");
    associated.AddComponent(sprite);
    hp = 1;
}

Alien::~Alien () {

}

void Alien::Start () {

}

void Alien::Update (float dt) {
    InputManager& inputM = InputManager::GetInstance();
    Camera camera;
    float posX, posY;
    if (inputM.MousePress(LEFT_MOUSE_BUTTON)) {
        posX = inputM.GetMouseX() + camera.pos.x;
        posY = inputM.GetMouseY() + camera.pos.y;
        Action newAction (Action::SHOOT, posX, posY);
        taskQueue.emplace(newAction);
    }
    if (inputM.MousePress(RIGHT_MOUSE_BUTTON)) {
        posX = inputM.GetMouseX() + camera.pos.x;
        posY = inputM.GetMouseY() + camera.pos.y;
        Action newAction (Action::MOVE, posX, posY);
        taskQueue.emplace(newAction);
    }

    if (taskQueue.empty() == false) {
        Action nextAction = taskQueue.front();

        float speed = 150;
        Vec2 currentPos = associated.box.Center();
        float angle;
        Vec2 speedVec(speed, 0);

        switch (nextAction.type) {
            case Action::MOVE:
                angle = currentPos.AngleOfLineTo(nextAction.pos);
                speedVec = speedVec.GetRotated(angle);
                speedVec *= dt;
                // Testar se Alien está suficiente próximo da posição.
                if (speedVec.Magnitude() < currentPos.DistanceTo(nextAction.pos)) {
                    currentPos += speedVec;
                } else {
                    currentPos = nextAction.pos;
                    taskQueue.pop();
                }
                associated.box = associated.box.TopLeftCornerIfCenterIs(currentPos);
                break;

            case Action::SHOOT:
                break;

            default:
                break;
        }

    }

    if (hp <= 0) {
        associated.RequestDelete();
    }
}

void Alien::Render () {

}

bool Alien::Is (std::string type) {
    return type == "Alien";
}

Alien::Action::Action (Action::ActionType type, float x, float y) {
    this->type = type;
    this->pos = Vec2(x,y);
}