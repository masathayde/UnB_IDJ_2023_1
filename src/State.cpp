#include "State.h"
#include "Vec2.h"
#include "Face.h"
#include "Sound.h"
#define PI 3.1416

State::State() {
    quitRequested = false;
    LoadAssets();
    music.Play();

    GameObject* background = new GameObject;
    Sprite* eSprite = new Sprite(*background, "img/ocean.jpg");
    background->AddComponent(eSprite);
    objectArray.emplace_back(background);
}

State::~State () {
    objectArray.clear();
}

void State::LoadAssets () {
    // bg.Open("img/ocean.jpg");
    music.Open("audio/stageState.ogg");
}

void State::Update (float dt) {
    // if(SDL_QuitRequested()) {
    //     quitRequested = true;
    // }
    Input();

    for (std::vector<std::unique_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
        (*it).get()->Update(dt);
    }

    for (unsigned int i = 0; i < objectArray.size(); ++i) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
            i--;
        }
    }
}

void State::Render () {

    for (std::vector<std::unique_ptr<GameObject>>::iterator it = objectArray.begin(); it != objectArray.end(); ++it) {
        (*it).get()->Render();
    }
}

bool State::QuitRequested () {
    return quitRequested;
}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if( go->box.Contains( (float)mouseX, (float) mouseY ) ) {
					Face* face = (Face*) go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject (int mouseX, int mouseY) {
    GameObject* enemy = new GameObject;
    enemy->box.x = mouseX;
    enemy->box.y = mouseY;
    Sprite* eSprite = new Sprite(*enemy, "img/penguinface.png");
    Sound* eSound = new Sound(*enemy, "audio/boom.wav");
    Face* face = new Face(*enemy);
    enemy->AddComponent(eSprite);
    enemy->AddComponent(eSound);
    enemy->AddComponent(face);
    objectArray.emplace_back(enemy);

}