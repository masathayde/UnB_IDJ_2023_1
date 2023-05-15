#include "GameObject.h"

GameObject::GameObject (int iZ) {
    z = iZ;
    isDead = false;
    started = false;
}

GameObject::~GameObject () {
    components.clear();
}

void GameObject::Update (float dt) {
    for (unsigned int i = 0; i < components.size(); ++i) {
        components[i]->Update(dt);
    }
}

void GameObject::Render () {
    for (unsigned int i = 0; i < components.size(); ++i) {
        components[i]->Render();
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
    if (this->started)
        cpt->Start();
}

void GameObject::RemoveComponent (Component* cpt) {
    for (int i = 0; i < (int) components.size(); ++i) {
        if (components[i].get() == cpt) {
            components.erase(components.begin()+i);
            break;
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

void GameObject::Start () {
    for (auto it = components.begin(); it != components.end(); ++it) {
        (*it)->Start();
    }
    started = true;
}