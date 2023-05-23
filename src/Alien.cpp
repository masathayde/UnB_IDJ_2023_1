#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Minion.h"
#include <cmath>

Alien::Alien (GameObject& go, int i_nMinions) : Component(go) {
    Sprite* sprite = new Sprite(go, "img/alien.png");
    associated.AddComponent(sprite);
    hp = 1;
}

Alien::~Alien () {

}

void Alien::Start () {
    int minionCount = 5;
    float arcOffset = 0;
    float offsetIncrease = 2.0 * 3.1416 / 5.0;
    for (int i = 0; i < minionCount; ++i, arcOffset += offsetIncrease) {
        GameObject* minionGO = new GameObject(1);
        std::weak_ptr<GameObject> alienGoPTR;
        alienGoPTR = Game::GetInstance().GetState().GetObjectPtr(&associated);
        Minion* minionCPT = new Minion(*minionGO, alienGoPTR, arcOffset);
        minionGO->AddComponent(minionCPT);
        Game::GetInstance().GetState().AddObject(minionGO);
        std::weak_ptr<GameObject> minionPtr = Game::GetInstance().GetState().GetObjectPtr(minionGO);
        minionArray.push_back(minionPtr);
    }
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
        Vec2 currentPos = associated.box.GetCenter();
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
                Shoot(nextAction.pos);
                taskQueue.pop();
                break;

            default:
                break;
        }

    }

    float angularSpeed = 180 / 9;
    associated.angleDeg = fmod(associated.angleDeg - (angularSpeed * dt), 360);

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

void Alien::Shoot (Vec2 target) {
    if (minionArray.empty())
        return;
    // Escolher minion mais próximo. Começamos com o primeiro.
    std::weak_ptr<GameObject> chosenMinion = minionArray[0];
    Vec2 minionPos = chosenMinion.lock()->box.GetCenter();
    float shortestDistance = minionPos.DistanceTo(target);
    for (int i = 1; i < (int) minionArray.size(); ++i) {
        std::weak_ptr<GameObject> candidate = minionArray[i];
        Vec2 candidatePos = candidate.lock()->box.GetCenter();
        float candidateDistance = candidatePos.DistanceTo(target);
        if (candidateDistance < shortestDistance) {
            chosenMinion = candidate;
            shortestDistance = candidateDistance;
        }
    }
    Minion* minion = (Minion*) chosenMinion.lock()->GetComponent("Minion");
    minion->Shoot(target);
}