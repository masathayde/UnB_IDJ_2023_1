#include "State.h"
#include "RenderQueue.h"

State::State() {
}

State::~State () {
	objectArray.clear();
}

bool State::QuitRequested () {
    return quitRequested;
}

bool State::PopRequested () {
    return popRequested;
}

void State::StartArray () {
	for (auto it: objectArray) {
		it.get()->Start();
	}
}

void State::UpdateArray (float dt) {
	for (auto it: objectArray) {
		it.get()->Update(dt);
	}
}

void State::RenderArray (float alpha) {
	for (auto it: objectArray) {
		it.get()->Render();
	}
	// Not actually rendering, just scheduling rendering jobs
	RenderQueue& rq = RenderQueue::GetInstance();
	rq.RenderJobs(alpha);
}

std::weak_ptr<GameObject> State::AddObject (GameObject* goptr) {
	std::shared_ptr<GameObject> goShrdPtr(goptr);
	objectArray.push_back(goShrdPtr);
	if (this->started) {
		goptr->Start();
	}
	std::weak_ptr<GameObject> goPtr(goShrdPtr);
	return goPtr;
}

std::weak_ptr<GameObject> State::GetObjectPtr (GameObject* goptr) {
	std::weak_ptr<GameObject> returnPtr;
	for (auto it : objectArray) {
		if (goptr == it.get()) {
			returnPtr = it;	
		}
	}
	return returnPtr;
}
