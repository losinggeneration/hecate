#include "DelayedEntityProcessingSystem.h"

namespace hecate {

template<class T> DelayedEntityProcessingSystem::DelayedEntityProcessingSystem(T *requiredType, std::set<T*> otherTypes) :
DelayedEntitySystem(getMergedTypes(requiredType, otherTypes)) {

}

void DelayedEntityProcessingSystem::processEntities(entitySet_t entities, int accumulatedDelta) {
	for(entitySet_t::iterator it = entities.begin(); it != entities.end(); it++) {
		process(*it, accumulatedDelta);
	}
}

}
