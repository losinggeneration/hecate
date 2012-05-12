#include "SystemManager.h"
#include "EntitySystem.h"
#include "SystemBitManager.h"
#include "World.h"

namespace hecate {

SystemManager::SystemManager(World *world) : world(world) {
}

SystemManager::~SystemManager() {
}

EntitySystem *SystemManager::setSystem(EntitySystem *system) {
	system->setWorld(world);

	if(sets.find(system) != sets.end()) {
		sets.insert(system);
	}

	system->setSystemBit(SystemBitManager::getBitFor(system));

	return system;
}

template<class T> T *SystemManager::getSystem(T *type) {
	systemsMap_t::iterator it = systems.find(type);
	if(it != systems.end()) {
		return dynamic_cast<T>((*it).second);
	}

	return NULL;
}

entitySystemSet_t SystemManager::getSystems() {
	return sets;
}

void SystemManager::initializeAll() {
	for(entitySystemSet_t::iterator it = sets.begin(); it != sets.end(); it++) {
		(*it)->initialize();
	}
}

}
