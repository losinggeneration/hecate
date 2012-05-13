#include "DelayedEntitySystem.h"
#include "World.h"

namespace hecate {

template<class T> DelayedEntitySystem::DelayedEntitySystem(std::set<T*> types) : EntitySystem(types) {
}

void DelayedEntitySystem::startDelayedRun(int delay) {
	this->delay = delay;
	this->acc = 0;
	running = true;
}

int DelayedEntitySystem::getInitialTimeDelay() const {
	return delay;
}

int DelayedEntitySystem::getRemainingTimeUntilProcessing() const {
	if(running) {
		return delay - acc;
	}

	return 0;
}

bool DelayedEntitySystem::isRunning() const {
	return running;
}

void DelayedEntitySystem::stop() {
	running = false;
	acc = 0;
}

bool DelayedEntitySystem::checkProcessing() {
	if(running) {
		acc += world->getDelta();

		if(acc >= delay) {
			return true;
		}
	}

	return false;
}

void DelayedEntitySystem::processEntities(entitySet_t entities) {
	processEntities(entities, acc);
}

}
