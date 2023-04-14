#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include "GameObject.h"

class Component {

 protected:
    GameObject& associated;
    
 public:
    Component (GameObject& associated);
    virtual ~Component();
    virtual void Update(float dt);
    virtual void Render();
    virtual bool Is(std::string type);
};

#endif