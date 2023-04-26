#include "Face.h"
#include "Sound.h"
#include "Sprite.h"

Face::Face (GameObject& associated) : Component (associated) {
    hitpoints = 30;
}

void Face::Damage (int damage) {
    hitpoints -= damage;
}

void Face::Update (float dt) {
    if (dead == false && hitpoints <= 0) {
        dead = true;
        Sound* sound = (Sound*) associated.GetComponent("Sound");
        if (sound != nullptr) {
            // Remover Imagem do GameObject?
            Sprite* spritePtr = (Sprite*) associated.GetComponent("Sprite");
            associated.RemoveComponent(spritePtr);
            soundChannel = sound->Play(0);
        }
    }
    if (dead) {
        // Checar se o som já terminou de tocar
        if(Mix_Playing(soundChannel) == 0) {
            associated.RequestDelete();
        }
    }
}

void Face::Render () {

}

bool Face::Is (std::string type) {
    return type == "Face";
}
