#ifndef ALIEN_H_
#define ALIEN_H_
#include <queue>
#include "Component.h"
#include "Timer.h"
#include "Vec2.h"

class Alien : public Component {

    class Action {
      public:
        enum ActionType {MOVE, SHOOT};
        ActionType type;
        Vec2 pos;
        Action (ActionType type, float x, float y);
    };

    enum AlienState {MOVING, RESTING};
    AlienState state {RESTING};
    Timer restTimer;
    float restTime;
    Vec2 destination;

    Vec2 speed;
    int hp {3};
    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    void Shoot (Vec2 target);
    void AI (float dt);
    void ManualControl (float dt);

 public:
    Alien (GameObject& go, int nMinions);
    ~Alien ();

    void Start ();
    void Update (float dt);
    void Render ();
    bool Is (std::string type);
    void NotifyCollision (GameObject& other);

    static int alienCount;
};


#endif