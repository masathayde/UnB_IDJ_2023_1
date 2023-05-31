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
    bool started;
    Rect box {0, 0, 0, 0};
    Rect previousBox {0, 0, 0, 0};
    double angleDeg {0.0};
    double previousAngleDeg {0.0};
    float previousZ;
    float z;
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
    void NotifyCollision (GameObject& other);
    // Rect GetBox ();
    // Rect GetPreviousBox ();
    // void ChangeBox (Rect box);
    // void ChangeBoxPosition (float x, float y);
    // void ChangeBoxDimensions (float w, float h);
    // double GetAngle ();
    // void ChangeAngle (double angle);
};

#endif