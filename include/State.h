#ifndef STATE_H_
#define STATE_H_
#include "GameObject.h"
#include <memory>
#include <list>

class State {
 protected:

   bool quitRequested {false};
   bool popRequested {false};
   bool started {false};
   std::list<std::shared_ptr<GameObject>> objectArray;

   virtual void StartArray ();
   virtual void UpdateArray (float dt);
   virtual void RenderArray (float alpha);

 public:
   State();
   virtual ~State();
   bool QuitRequested ();
   bool PopRequested ();
   virtual void LoadAssets()=0;
   virtual void Update(float dt)=0;
   virtual void Render(float alpha = 1.0)=0;
   virtual void Start ()=0;
   virtual void Pause ()=0;
   virtual void Resume ()=0;

   virtual std::weak_ptr<GameObject> AddObject (GameObject* go);
   virtual std::weak_ptr<GameObject> GetObjectPtr (GameObject* go);

};

#endif