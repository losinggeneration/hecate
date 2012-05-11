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

#ifndef NO_RTTI
	template<class T> EntitySystem *setSystem(T *system);
#endif
	EntitySystem *setSystem(EntitySystem *system, std::string type);
	EntitySystem *getSystem(std::string type);
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
