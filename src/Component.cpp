#include "Component.h"

Component::Component (GameObject& gObject) : associated(gObject) {
}

void Component::Start () {
}

void Component::NotifyCollision (GameObject& other) {
    
}