#ifndef HECATE_DELAYEDENTITYPROCESSINGSYSTEM_H
#define HECATE_DELAYEDENTITYPROCESSINGSYSTEM_H

#include "DelayedEntitySystem.h"
#include "Types.h"

namespace hecate {

class Entity;

class DelayedEntityProcessingSystem : public DelayedEntitySystem {
public:
	template<class T> DelayedEntityProcessingSystem(T *requiredType, std::set<T*> otherTypes);

protected:
	virtual void process(Entity *e, int accumulatedDelta) = 0;
	// Do not override
	void processEntities(entitySet_t entities, int accumulatedDelta);
};

}

#endif
