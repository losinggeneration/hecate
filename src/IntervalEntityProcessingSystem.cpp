#include "IntervalEntityProcessingSystem.h"

namespace hecate {

	template<class T> IntervalEntityProcessingSystem::IntervalEntityProcessingSystem(int interval, T *requiredType, std::set<T*> otherTypes) :
	IntervalEntitySystem(getMergedTypes(interval, requiredType, otherTypes)) {

	}

	void IntervalEntityProcessingSystem::processEntities(entitySet_t entities, int accumulatedDelta) {
		for(entitySet_t::iterator it = entities.begin(); it != entities.end(); it++) {
			process(*it, accumulatedDelta);
		}
	}

}
