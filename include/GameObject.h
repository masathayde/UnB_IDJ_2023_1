#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include <vector>
#include "Component.h"
#include "Rect.h"

class GameObject {

    std::vector<Component*> components;
    bool isDead;

 public:
    Rect box;

    GameObject ();
    ~GameObject ();
    void Update (float dt);
    void Render ();
    bool IsDead ();
    void RequestDelete ();
    void AddComponent(Component* cpt);
    void RemoveComponent (Component* cpt);
    Component* GetComponent (std::string type);
};

#endif