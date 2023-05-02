#include "InputManager.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

InputManager& InputManager::GetInstance () {
    static InputManager im;
    return im;
}

InputManager::InputManager () {
    for (int i = 0; i < 6; ++i) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}

InputManager::~InputManager () {

}

void InputManager::Update () {
	SDL_Event event;
	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);
    // Reseta quitRequested
    quitRequested = false;
    // Incrementa o contador de update
    updateCounter++;
    int key;
	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // Se o evento for quit, setar a flag para terminação
            case SDL_QUIT:
                quitRequested = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            case SDL_KEYDOWN:
                if (event.key.repeat == 1)
                    break;
                key = event.key.keysym.sym;
                keyState[key] = true;
                keyUpdate[key] = updateCounter;
                break;

            case SDL_KEYUP:
                key = event.key.keysym.sym;
                keyState[key] = false;
                keyUpdate[key] = updateCounter;
                break;

            default:
                break;
        }
	}
}

bool InputManager::KeyPress (int key) {
    return keyState[key] == true && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease (int key) {
    return keyState[key] == false && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown (int key) {
    return keyState[key];
}

bool InputManager::MousePress (int button) {
    return mouseState[button] == true && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease (int button) {
    return mouseState[button] == false && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown (int button) {
    return mouseState[button];
}

int InputManager::GetMouseX () {
    return mouseX;
}

int InputManager::GetMouseY () {
    return mouseY;
}

bool InputManager::QuitRequested () {
    return quitRequested;
}