#ifndef TIMER_H_
#define TIMER_H_

class Timer {

    float time {0};

 public:
    void Update (float dt);
    void Restart ();
    float Get();
};

#endif