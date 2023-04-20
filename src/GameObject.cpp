#include "GameObject.h"

GameObject::GameObject () {
    isDead = false;
}

GameObject::~GameObject () {
    components.clear();
}

void GameObject::Update (float dt) {
    for (std::vector<std::unique_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it) {
        (*it)->Update(dt);
    }
}

void GameObject::Render () {
    for (std::vector<std::unique_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it) {
        (*it)->Render();
    }
}

bool GameObject::IsDead () {
    return isDead;
}

void GameObject::RequestDelete () {
    isDead = true;
}

void GameObject::AddComponent (Component* cpt) {
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent (std::unique_ptr<Component> cpt) {
    for (unsigned int i = 0; i < components.size(); ++i) {
        if (components[i] == cpt) {
            components.erase(components.begin()+i);
            i--;
        }
    }
}

Component* GameObject::GetComponent (std::string type) {
    for (unsigned int i = 0; i < components.size(); ++i) {
        if (components[i].get()->Is(type)) {
            return components[i].get();
        }
    }
    return nullptr;
}
