#include "TitleState.h"
#include "StageState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"

TitleState::TitleState () {
    GameObject* titleGO = new GameObject ();
    Sprite* titleSprite = new Sprite (*titleGO, "img/title.jpg");
    titleGO->AddComponent(titleSprite);
    AddObject(titleGO);
}

TitleState::~TitleState () {
}

void TitleState::Update (float dt) {
    InputManager& inputM = InputManager::GetInstance();

    if (inputM.QuitRequested() || inputM.KeyPress(SDLK_ESCAPE))
		quitRequested = true;

    if (inputM.KeyPress(SDLK_SPACE)) {
        StageState* stage = new StageState();
        Game::GetInstance().Push(stage);
    } 
}

void TitleState::LoadAssets () {

}

void TitleState::Render () {
    Camera::Reset();
    RenderArray();
}

void TitleState::Start () {
}

void TitleState::Pause () {
}

void TitleState::Resume () {
}