#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include <vector>
#include <memory>
#include "Component.h"
#include "Rect.h"

// TODO: perguntar sobre a possibilidade de usar uma lista
// em vez de vetor, para armazenar components.

class Component;

class GameObject {

    std::vector<std::unique_ptr<Component>> components;
    bool isDead;

 public:
    Rect box;
    double angleDeg {0.0};
    float z;
    bool started;
    GameObject (int z = 0);
    ~GameObject ();
    void Update (float dt);
    void Render ();
    bool IsDead ();
    void RequestDelete ();
    void AddComponent(Component* cpt);
    void RemoveComponent (Component* cpt);
    Component* GetComponent (std::string type);
    void Start ();
};

#endif