#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <map>
#include <set>
#include <string>
#include "Types.h"

namespace hecate {

class ComponentType;
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
	typedef std::map<std::string, EntitySystem*> systemsMap_t;
	World *world;
	systemsMap_t systems;
	entitySystemSet_t sets;
};

}

#endif // SYSTEMMANAGER_H
