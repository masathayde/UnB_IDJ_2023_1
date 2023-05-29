#include "TitleState.h"
#include "StageState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"
#include "Text.h"

TitleState::TitleState () {

    // Title image
    GameObject* titleImageGO = new GameObject ();
    Sprite* titleImageSprite = new Sprite (*titleImageGO, "img/title.jpg");
    titleImageGO->AddComponent(titleImageSprite);
    AddObject(titleImageGO);
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

    // Title text
    textTimer += dt;
    if (textTimer >= textDisplayTime) {
        if (textShowing) {
            if (!titleTextGO.expired()) {
                titleTextGO.lock()->RequestDelete();
            }
            textShowing = false;
            titleTextGO.reset();
        } else {
            std::string msg = "Pressione ESPACO para jogar";
            GameObject* textGO = new GameObject(1);
            textGO->box.x = 50;
            textGO->box.y = 300;
            Text* titleText = new Text (*textGO, "font/Call me maybe.ttf", 30, Text::SOLID, msg, Text::ChooseColor(Text::WHITE_TEXT));
            textGO->AddComponent(titleText);
            titleTextGO = AddObject(textGO);
            textShowing = true;
        }
        textTimer = 0.0;
    }
    EraseObjects();
}

void TitleState::LoadAssets () {

}

void TitleState::Render () {
    RenderArray();
}

void TitleState::Start () {
    Mix_HaltMusic();
    Camera::Reset();
}

void TitleState::Pause () {
}

void TitleState::Resume () {
    Mix_HaltMusic();
    Camera::Reset();
}

void TitleState::EraseObjects () {
	for (std::list<std::shared_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
		if (it->get()->IsDead()) {
            // Get segfault in GDB if I don't do this
			it = objectArray.erase(it);
		}
	}
}