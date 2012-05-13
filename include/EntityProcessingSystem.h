#ifndef HECATE_ENTITYPROCESSINGSYSTEM_H
#define HECATE_ENTITYPROCESSINGSYSTEM_H

#include "EntitySystem.h"
#include "Types.h"

namespace hecate {

class EntityProcessingSystem : public EntitySystem {
public:
	template<class T> EntityProcessingSystem(T *requiredType, std::set<T*> otherTypes);

protected:
	virtual void process(Entity *e) = 0;
	// Do not override!
	void processEntities(entitySet_t entities);
	bool checkProcessing();
};

}

#endif
