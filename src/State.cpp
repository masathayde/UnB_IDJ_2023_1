#include "State.h"
#include "Vec2.h"
#include "Face.h"
#include "Sound.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "RenderQueue.h"
#include "Alien.h"
#define PI 3.1416

State::State() {
    quitRequested = false;
	started = false;
    LoadAssets();
    music.Play();

    GameObject* background = new GameObject(-1);
	GameObject* tileMapObject = new GameObject(0);
	GameObject* tileMapObject2 = new GameObject(2);
    Sprite* eSprite = new Sprite(*background, "img/ocean.jpg");
    background->AddComponent(eSprite);
	CameraFollower* cFollow = new CameraFollower(*background);
	background->AddComponent(cFollow);
	bgTileSet = new TileSet(64, 64, "img/tileset.png");
	TileMap* bgTileMap = new TileMap(*tileMapObject, "map/tileMap_half_1.txt", bgTileSet);
	TileMap* bgTileMap2 = new TileMap(*tileMapObject2, "map/tileMap_half_2.txt", bgTileSet);
	tileMapObject->AddComponent(bgTileMap);
	tileMapObject2->AddComponent(bgTileMap2);

	// objectArray.emplace_back(background);
	// objectArray.emplace_back(tileMapObject);
	// objectArray.emplace_back(tileMapObject2);

	objectArray.emplace(background, background);
	objectArray.emplace(tileMapObject, tileMapObject);
	objectArray.emplace(tileMapObject2, tileMapObject2);

	GameObject* alienGo = new GameObject(1);
	Alien* alien = new Alien(*alienGo, 0);
	alienGo->box.x = 512;
	alienGo->box.y = 300;
	alienGo->AddComponent(alien);
	objectArray.emplace(alienGo, alienGo);
}

State::~State () {
    objectArray.clear();
	delete bgTileSet;
}

void State::LoadAssets () {
    // bg.Open("img/ocean.jpg");
    music.Open("audio/stageState.ogg");
}

void State::Start () {
	LoadAssets();
	for (auto it: objectArray) {
		it.second->Start();
	}
	started = true;
}

void State::Update (float dt) {
	// if(SDL_QuitRequested()) {
    //     quitRequested = true;
    // }
	InputManager& inputM = InputManager::GetInstance();
	if (inputM.QuitRequested() || inputM.KeyPress(SDLK_ESCAPE))
		quitRequested = true;

	Input();
	Camera camera;
	camera.Update(dt);
    // for (std::vector<std::unique_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
    //     (*it).get()->Update(dt);
    // }
	for (auto it : objectArray) {
		it.second->Update(dt);
	}

    // for (int i = 0; i < (int) objectArray.size(); ++i) {
    //     if (objectArray[i]->IsDead()) {
    //         objectArray.erase(objectArray.begin()+i);
    //         i--;
    //     }
    // }
	std::vector<GameObject*> toErase;
	for (auto it: objectArray) {
		if (it.second->IsDead()) {
			toErase.push_back(it.first);
		}
	}
	for (auto obj : toErase) {
		objectArray.erase(obj);
	}
}

void State::Render () {
	// Not actually rendering, just scheduling rendering jobs
    // for (std::vector<std::unique_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
    //     (*it).get()->Render();
    // }
	for (auto it = objectArray.begin(); it != objectArray.end(); ++it) {
		it->second->Render();
	}
	RenderQueue& rq = RenderQueue::GetInstance();
	rq.RenderJobs();
}

bool State::QuitRequested () {
    return quitRequested;
}

void State::Input() {
	// InputManager& inputM = InputManager::GetInstance();
	// Camera camera;
	// if (inputM.KeyPress(SDLK_SPACE)) {
	// 	Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2(inputM.GetMouseX() + camera.pos.x, inputM.GetMouseY() + camera.pos.y);
	// 	AddObject((int)objPos.x, (int)objPos.y);
	// }

	// if (inputM.MousePress(LEFT_MOUSE_BUTTON)) {
	// 	// for(int i = objectArray.size() - 1; i >= 0; --i) {
	// 	for (auto obj : objectArray) {
	// 		// Obtem o ponteiro e casta pra Face.
	// 		// GameObject* go = (GameObject*) objectArray[i].get();
	// 		GameObject* go = (GameObject*) obj.second.get();


	// 		// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
	// 		// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
	// 		// ao usar get(), violamos esse princípio e estamos menos seguros.
	// 		// Esse código, assim como a classe Face, é provisório. Futuramente, para
	// 		// chamar funções de GameObjects, use objectArray[i]->função() direto.
	// 		float xAdjusted = (float) inputM.GetMouseX() + camera.pos.x;
	// 		float yAdjusted = (float) inputM.GetMouseY() + camera.pos.y;
	// 		if( go->box.Contains( xAdjusted, yAdjusted ) ) {
	// 			Face* face = (Face*) go->GetComponent( "Face" );
	// 			if ( nullptr != face ) {
	// 				// Aplica dano
	// 				face->Damage(std::rand() % 10 + 10);
	// 				// Sai do loop (só queremos acertar um)
	// 				break;
	// 			}
	// 		}
	// 	}
	// }
}

// void State::AddObject (int inX, int inY) {
//     GameObject* enemy = new GameObject(1);
//     enemy->box.x = inX;
//     enemy->box.y = inY;
//     Sprite* eSprite = new Sprite(*enemy, "img/penguinface.png");
//     Sound* eSound = new Sound(*enemy, "audio/boom.wav");
//     Face* face = new Face(*enemy);
//     enemy->AddComponent(eSprite);
//     enemy->AddComponent(eSound);
//     enemy->AddComponent(face);
//     objectArray.emplace(enemy, enemy);
// }

std::weak_ptr<GameObject> State::AddObject (GameObject* goptr) {
	std::shared_ptr<GameObject> goShrdPtr(goptr);
	objectArray.emplace(goptr, goShrdPtr);
	if (this->started) {
		goptr->Start();
	}
	std::weak_ptr<GameObject> goPtr(goShrdPtr);
	return goPtr;
}

std::weak_ptr<GameObject> State::GetObjectPtr (GameObject* goptr) {
	std::weak_ptr<GameObject> returnPtr;
	std::unordered_map<GameObject*, std::shared_ptr<GameObject>>::iterator it;
	it = objectArray.find(goptr);
	if (it != objectArray.end()) {
		returnPtr = it->second;
	}
	return returnPtr;
}