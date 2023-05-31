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

void GameObject::NotifyCollision (GameObject& other) {
    for (auto& it : components) {
        it->NotifyCollision(other);
    }
}

// Rect GameObject::GetBox () {
//     return box;
// }

// Rect GameObject::GetPreviousBox () {
//     return previousBox;
// }

// void GameObject::ChangeBox (Rect newBox) {
//     previousBox = box;
//     box = newBox;
// }

// void GameObject::ChangeBoxPosition (float newX, float newY) {
//     previousBox = box;
//     box.x = newX;
//     box.y = newY;
// }

// void GameObject::ChangeBoxDimensions (float newW, float newH) {
//     previousBox = box;
//     box.w = newW;
//     box.h = newH;
// }

// double GameObject::GetAngle () {
//     return angleDeg;
// }

// void GameObject::ChangeAngle (double newAngle) {
//     previousAngleDeg = angleDeg;
//     angleDeg = newAngle;
// }