#include "GameObject.h"

GameObject::GameObject () {
    isDead = false;
}

GameObject::~GameObject () {
    for (auto it: components) {
        delete it;
    }
}