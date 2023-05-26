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
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"
#define PI 3.1416
#define RADDEGRATIO 3.141592653589793238463/180

State::State() {
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

State::~State () {
    objectArray.clear();
	delete bgTileSet;
}

void State::LoadAssets () {
    music.Open("audio/stageState.ogg");
}

void State::Start () {
	LoadAssets();
	for (auto it: objectArray) {
		it->Start();
	}
	started = true;
}

void State::UpdateObjects (float dt) {
	// for (std::vector<std::unique_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
    //     (*it).get()->Update(dt);
    // }
	for (auto it : objectArray) {
		if (cameraFocus.expired() || it.get() != cameraFocus.lock().get()) {
			it->Update(dt);
		}
	}
}

void State::EraseObjects () {
	// Old code, delete later

	// std::vector<GameObject*> toErase;
	// for (auto it: objectArray) {
	// 	if (it.second->IsDead()) {
	// 		toErase.push_back(it.first);
	// 	}
	// }
	// for (auto obj : toErase) {
	// 	objectArray.erase(obj);
	// }

	// for (int i = 0; i < (int) objectArray.size(); ++i) {
    //     if (objectArray[i]->IsDead()) {
    //         objectArray.erase(objectArray.begin()+i);
    //         i--;
    //     }
    // }

	for (std::list<std::shared_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
		if (it->get()->IsDead()) {
			objectArray.erase(it);
		}
	}

}

void State::CheckCollision () {
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

void State::Update (float dt) {
	InputManager& inputM = InputManager::GetInstance();
	if (inputM.QuitRequested() || inputM.KeyPress(SDLK_ESCAPE))
		quitRequested = true;

	Input();
	Camera camera;
	// Atualiza foco da câmera primeiro.
	if (cameraFocus.expired() == false) {
		cameraFocus.lock()->Update(dt);
	}
	camera.Update(dt);
    UpdateObjects(dt);
	CheckCollision();
	EraseObjects();

	// PrintDebugInfo();
}

void State::Render () {
	// Not actually rendering, just scheduling rendering jobs
    // for (std::vector<std::unique_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
    //     (*it).get()->Render();
    // }
	for (auto it = objectArray.begin(); it != objectArray.end(); ++it) {
		it->get()->Render();
	}
	RenderQueue& rq = RenderQueue::GetInstance();
	rq.RenderJobs();
}

bool State::QuitRequested () {
    return quitRequested;
}

void State::Input() {
	InputManager& inputM = InputManager::GetInstance();
	Camera camera;

	if (inputM.KeyPress(SDLK_c)) {
		if (cameraFocus.expired()) {
			camera.Follow(player);
			AddCameraFocus(player);
		} else {
			camera.Unfollow();
		}
	}

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
	objectArray.push_back(goShrdPtr);
	if (this->started) {
		goptr->Start();
	}
	std::weak_ptr<GameObject> goPtr(goShrdPtr);
	return goPtr;
}

std::weak_ptr<GameObject> State::GetObjectPtr (GameObject* goptr) {
	std::weak_ptr<GameObject> returnPtr;
	for (auto it : objectArray) {
		if (goptr == it.get()) {
			returnPtr = it;	
		}
	}
	return returnPtr;
}

void State::AddCameraFocus (std::weak_ptr<GameObject> object) {
	cameraFocus = object;
}

void State::RemoveCameraFocus () {
	cameraFocus.reset();
}

void State::PrintDebugInfo () {
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