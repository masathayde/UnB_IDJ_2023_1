#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Minion.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"
#include "PenguinBody.h"
#include <cmath>

int Alien::alienCount {0};

Alien::Alien (GameObject& go, int i_nMinions) : Component(go) {
    associated.AddComponent(this);
    Sprite* sprite = new Sprite(go, "img/alien.png");
    associated.AddComponent(sprite);
    Collider* collider = new Collider(go);
    associated.AddComponent(collider);
    restTime = 0.5 + ((float) (rand() % 101))/100.0;;
    alienCount++;
}

Alien::~Alien () {
    alienCount--;
}

void Alien::Start () {
    int minionCount = 5;
    float arcOffset = 0;
    float offsetIncrease = 2.0 * 3.1416 / 5.0;
    for (int i = 0; i < minionCount; ++i, arcOffset += offsetIncrease) {
        GameObject* minionGO = new GameObject(1);
        std::weak_ptr<GameObject> alienGoPTR;
        alienGoPTR = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);
        new Minion(*minionGO, alienGoPTR, arcOffset);
        Game::GetInstance().GetCurrentState().AddObject(minionGO);
        std::weak_ptr<GameObject> minionPtr = Game::GetInstance().GetCurrentState().GetObjectPtr(minionGO);
        minionArray.push_back(minionPtr);
    }
}

void Alien::Update (float dt) {
    AI(dt);

    float angularSpeed = 180 / 9;
    associated.angleDeg = fmod(associated.angleDeg - (angularSpeed * dt), 360);

    if (hp <= 0) {
        std::string file = "img/aliendeath.png";
        GameObject* deathGo = new GameObject(associated.z);
        deathGo->box = associated.box;
        Sprite* deathSprite = new Sprite(*deathGo, file, 4, 0.2, true, false, 1.0, 0.4);
        Sound* deathSound = new Sound(*deathGo, "audio/boom.wav");
        deathSound->Play();
        deathGo->AddComponent(deathSprite);
        deathGo->AddComponent(deathSound);
        Game::GetInstance().GetCurrentState().AddObject(deathGo);
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

void Alien::NotifyCollision (GameObject& other) {
    Bullet* bullet = (Bullet*) other.GetComponent("Bullet");
    if (bullet != nullptr && !bullet->targetsPlayer) {
        this->hp -= bullet->GetDamage();
    }
}

void Alien::AI (float dt) {
    if (PenguinBody::player == nullptr) {
        return;
    }

    float speed = 150;
    Vec2 currentPos = associated.box.GetCenter();
    float angle;
    Vec2 speedVec(speed, 0);

    switch (state) {

        case RESTING:
            if (restTimer.Get() >= restTime) {
                destination = PenguinBody::player->GetPos().GetCenter();
                state = MOVING;
            } else {
                restTimer.Update(dt);
            }
            break;

        case MOVING:
            angle = currentPos.AngleOfLineTo(destination);
            speedVec = speedVec.GetRotated(angle);
            speedVec *= dt;
            // Testar se Alien está suficiente próximo da posição.
            if (speedVec.Magnitude() < currentPos.DistanceTo(destination)) {
                currentPos += speedVec;
            } else {
                currentPos = destination;
                Shoot(PenguinBody::player->GetPos().GetCenter());
                restTime = 0.5 + ((float) (rand() % 101))/100.0;
                state = RESTING;
                restTimer.Restart();
            }
            associated.box = associated.box.TopLeftCornerIfCenterIs(currentPos);
            break;

        default:
            break;
    }
}

void Alien::ManualControl (float dt) {
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
}