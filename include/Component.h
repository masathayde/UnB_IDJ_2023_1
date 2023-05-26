#ifndef COMPONENT_H_
#define COMPONENT_H_
#include "GameObject.h"
#include <string>

class GameObject;

class Component {

 protected:
   GameObject& associated;
    
 public:
   Component (GameObject& gObject);
   virtual ~Component() {};
   virtual void Update(float dt)=0;
   virtual void Render()=0;
   virtual bool Is(std::string type)=0;
   virtual void Start ();
   virtual void NotifyCollision (GameObject& other);
};

#endif