#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <map>
#include <set>
#include <string>

namespace hecate {

class EntitySystem;
class World;

class SystemManager {
public:
	SystemManager(World *world);
	~SystemManager();

	EntitySystem *setSystem(EntitySystem *system);
	EntitySystem *getSystem(std::string type);
	std::set<EntitySystem*> getSystems();

	void initializeAll();

private:
	World *world;
	std::map<std::string, EntitySystem*> systems;
	std::set<EntitySystem*> sets;
};

}

#endif // SYSTEMMANAGER_H
