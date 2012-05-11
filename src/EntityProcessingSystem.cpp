#include "EntityProcessingSystem.h"

namespace hecate {

template<class T>
EntityProcessingSystem::EntityProcessingSystem(T *requiredType, std::set<T*> otherTypes) :
EntitySystem(getMergedTypes(requiredType, otherTypes)) {
}

void EntityProcessingSystem::processEntities(entitySet_t entities) {
	for(entitySet_t::iterator it = entities.begin(); it != entities.end(); it++) {
		process((*it));
	}
}

inline bool EntityProcessingSystem::checkProcessing() {
	return true;
}

}
