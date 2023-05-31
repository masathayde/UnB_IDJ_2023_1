#include "EndState.h"
#include "GameData.h"
#include "Sprite.h"
#include "Text.h"
#include "InputManager.h"
#include "TitleState.h"
#include "Game.h"
#include "Camera.h"
#include "Music.h"

EndState::EndState () {
    std::string imageFile;
    std::string musicFile;
    GameObject* imageGO = new GameObject ();
    if (GameData::playerVictory) {
        imageFile = "img/win.jpg";
        musicFile = "audio/endStateWin.ogg";
    } else {
        imageFile = "img/lose.jpg";
        musicFile = "audio/endStateLose.ogg";
    }
    backgroundMusic.Open(musicFile);

    Sprite* imageSprite = new Sprite (*imageGO, imageFile);
    imageGO->AddComponent(imageSprite);
    AddObject(imageGO);
}

EndState::~EndState () {
}

void EndState::LoadAssets () {
}

void EndState::Update (float dt) {
    InputManager& inputM = InputManager::GetInstance();
    if (inputM.QuitRequested() || inputM.KeyPress(SDLK_ESCAPE))
		quitRequested = true;

    if (inputM.KeyPress(SDLK_SPACE)) {
        popRequested = true;
    }

    // Title text
    textTimer += dt;
    if (textTimer >= textDisplayTime) {
        if (textShowing) {
            if (titleTextGO != nullptr) {
                titleTextGO->RequestDelete();
            }
            textShowing = false;
            titleTextGO = nullptr;
        } else {
            std::string msg = "Pressione ESPACO para jogar de novo\nPressione ESC para sair";
            titleTextGO = new GameObject(1);
            titleTextGO->box.x = 50;
            titleTextGO->box.y = 300;
            Text* titleText = new Text (*titleTextGO, "font/Call me maybe.ttf", 30, Text::SOLID, msg, Text::ChooseColor(Text::BLACK_TEXT));
            titleTextGO->AddComponent(titleText);
            AddObject(titleTextGO);
            textShowing = true;
        }
        textTimer = 0.0;
    }
    EraseObjects ();
}

void EndState::Render (float alpha) {
    RenderArray(alpha);
}

void EndState::Start () {
    backgroundMusic.Play();
    Camera::Reset();
}

void EndState::Pause () {
}

void EndState::Resume () {
    Mix_HaltMusic();
    Camera::Reset();
}

void EndState::EraseObjects () {
	for (std::list<std::shared_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
		if (it->get()->IsDead()) {
			it = objectArray.erase(it);
		}
	}
}