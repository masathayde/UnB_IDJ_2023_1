#include "StageState.h"
#include "Vec2.h"
#include "Sound.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "RenderQueue.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"
// #define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER
// #include "SDL_include.h"
#define PI 3.141592653589793238463
#define RADDEGRATIO PI/180

StageState::StageState () {
    quitRequested = false;
	started = false;
    LoadAssets();
    music.Play();

	// Background
    GameObject* background = new GameObject(-1);
	CameraFollower* cFollow = new CameraFollower(*background);
	Sprite* eSprite = new Sprite(*background, "img/ocean.jpg");
	background->AddComponent(cFollow);
	background->AddComponent(eSprite);
	AddObject(background);

	// Tileset
	bgTileSet = new TileSet(64, 64, "img/tileset.png");

	// Ground
	GameObject* tileMapObject = new GameObject(0);
	TileMap* bgTileMap = new TileMap(*tileMapObject, "map/tileMap_half_1.txt", bgTileSet);
	tileMapObject->AddComponent(bgTileMap);
	AddObject(tileMapObject);

	// Clouds
	GameObject* tileMapObject2 = new GameObject(3);
	TileMap* bgTileMap2 = new TileMap(*tileMapObject2, "map/tileMap_half_2.txt", bgTileSet);
	tileMapObject2->AddComponent(bgTileMap2);
	AddObject(tileMapObject2);

	// Alien
	GameObject* alienGo = new GameObject(1);
	new Alien(*alienGo, 0);
	alienGo->box.x = 512;
	alienGo->box.y = 300;
	AddObject(alienGo);

	// Player penguin
	GameObject* penguinGo = new GameObject(1);
	new PenguinBody(*penguinGo);
	penguinGo->box.x = 704;
	penguinGo->box.y = 640;
    player = AddObject(penguinGo);

	// Make camera follow penguin
	Camera::Follow(player);
	AddCameraFocus(player);
}

StageState::~StageState () {
	delete bgTileSet;
}

void StageState::LoadAssets () {
    music.Open("audio/stageState.ogg");
}

void StageState::Start () {
	LoadAssets();
	StartArray();
	started = true;
}

void StageState::UpdateArray (float dt) {
	for (auto it : objectArray) {
		if (cameraFocus.expired() || it.get() != cameraFocus.lock().get()) {
			it->Update(dt);
		}
	}
}

void StageState::EraseObjects () {
	for (std::list<std::shared_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
		if (it->get()->IsDead()) {
			objectArray.erase(it);
			it--;
		}
	}
}

void StageState::CheckCollision () {
	for (std::list<std::shared_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
		Collider* colliderA = (Collider*) it->get()->GetComponent("Collider");
		if (colliderA != nullptr) {
			std::list<std::shared_ptr<GameObject>>::iterator jt = it;
			++jt;
			for (; jt != objectArray.end(); ++jt) {
				Collider* colliderB = (Collider*) jt->get()->GetComponent("Collider");
				if (colliderB != nullptr) {
					float angleA = it->get()->angleDeg * RADDEGRATIO;
					float angleB = jt->get()->angleDeg * RADDEGRATIO;
					Rect boxA = colliderA->box;
					Rect boxB = colliderB->box;
					bool haveCollided = Collision::IsColliding (boxA, boxB, angleA, angleB);
					if (haveCollided) {
						GameObject& objA = *(it->get());
						GameObject& objB = *(jt->get());
						it->get()->NotifyCollision(objB);
						jt->get()->NotifyCollision(objA);
					}
				}
			}
		}
	}
}

void StageState::Update (float dt) {
	InputManager& inputM = InputManager::GetInstance();
	if (inputM.QuitRequested()) {
		quitRequested = true;
	}

	if (inputM.KeyPress(SDLK_ESCAPE)) {
		popRequested = true;
	}

	Input();
	Camera camera;
	// Atualiza foco da câmera primeiro.
	if (cameraFocus.expired() == false) {
		cameraFocus.lock()->Update(dt);
	}
	camera.Update(dt);
    UpdateArray(dt);
	CheckCollision();
	EraseObjects();

	// PrintDebugInfo();
}

void StageState::Render () {
	RenderArray();
}

void StageState::Input() {
	InputManager& inputM = InputManager::GetInstance();
	Camera camera;

	if (inputM.KeyPress(SDLK_c)) {
		if (cameraFocus.expired()) {
			printf("lol\n");
			camera.Follow(player);
			AddCameraFocus(player);
		} else {
			RemoveCameraFocus();
			camera.Unfollow();
		}
	}
}

void StageState::AddCameraFocus (std::weak_ptr<GameObject> object) {
	cameraFocus = object;
}

void StageState::RemoveCameraFocus () {
	cameraFocus.reset();
}

void StageState::PrintDebugInfo () {
	if (!player.expired()) {
		Rect box = player.lock()->box;
		Collider* collider = (Collider*) player.lock()->GetComponent("Collider");
		Rect boxColl = collider->box;
		Camera camera;
		system("cls");
		printf("penguin (go): %f, %f\n",  (box.x - camera.pos.x), (box.y - camera.pos.y));
		printf("penguin (collision): %f, %f\n",  (boxColl.x - camera.pos.x), (boxColl.y - camera.pos.y));
		fflush(stdout);
	}
}

void StageState::Pause () {
}

void StageState::Resume () {	
}