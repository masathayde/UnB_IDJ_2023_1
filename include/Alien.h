#ifndef ALIEN_H_
#define ALIEN_H_
#include <queue>
#include "Component.h"
#include "Vec2.h"

class Alien : public Component {

    class Action {
      public:
        enum ActionType {MOVE, SHOOT};
        ActionType type;
        Vec2 pos;
        Action (ActionType type, float x, float y);
    };

    Vec2 speed;
    int hp;
    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    void Shoot (Vec2 target);

 public:
    Alien (GameObject& go, int nMinions);
    ~Alien ();

    void Start ();
    void Update (float dt);
    void Render ();
    bool Is (std::string type);
    void NotifyCollision (GameObject& other);
};


#endif