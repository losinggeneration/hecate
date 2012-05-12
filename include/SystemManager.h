#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <map>
#include <set>
#include <string>
#include "Types.h"

namespace hecate {

class EntitySystem;
class World;

class SystemManager {
public:
	SystemManager(World *world);
	~SystemManager();

	EntitySystem *setSystem(EntitySystem *system);
	template<class T> T *getSystem(T *type);
	entitySystemSet_t getSystems();

	void initializeAll();

private:
	World *world;
	entitySystemSet_t sets;
};

}

#endif // SYSTEMMANAGER_H
