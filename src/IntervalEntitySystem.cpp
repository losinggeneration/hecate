#include "IntervalEntitySystem.h"
#include "World.h"

namespace hecate {

template<class T> IntervalEntitySystem::IntervalEntitySystem(int interval, std::set<T*> types) : EntitySystem(types), interval(interval) {
}

bool IntervalEntitySystem::checkProcessing() {
	acc += world->getDelta();

	if(acc >= interval) {
		acc -= interval;
		return true;
	}

	return false;
}

}
