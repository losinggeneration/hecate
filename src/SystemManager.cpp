#include "SystemManager.h"
#include "EntitySystem.h"
// #include "SystemBitManager.h"
#include "World.h"

#ifndef NO_RTTI
#include <typeinfo>
#endif

namespace hecate {

SystemManager::SystemManager(World *world) : world(world) {
}

SystemManager::~SystemManager() {
}

EntitySystem *SystemManager::setSystem(EntitySystem *system) {
	system->setWorld(world);
#ifndef NO_RTTI
	systems[typeid(system).name()] = system;
#endif
	if(sets.find(system) != sets.end()) {
		sets.insert(system);
	}

// 	system->setSystemBit(SystemBitManager.getBitFor(typeid(system).name()));

	return system;
}

EntitySystem *SystemManager::getSystem(std::string type) {
	std::map<std::string, EntitySystem*>::iterator it = systems.find(type);
	if(it != systems.end()) {
		return (*it).second;
	}

	return NULL;
}

std::set<EntitySystem*> SystemManager::getSystems() {
	return sets;
}

void SystemManager::initializeAll() {
	for(std::set<EntitySystem*>::iterator it = sets.begin(); it != sets.end(); it++) {
		(*it)->initialize();
	}
}

}
