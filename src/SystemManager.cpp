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
	sets.insert(system);
	system->setSystemBit(SystemBitManager::getBitFor(system));

	return system;
}

template<class T> T *SystemManager::getSystem(T *type) {
	entitySystemSet_t::iterator it = sets.find(type);
	if(it != sets.end()) {
		return dynamic_cast<T>(*it);
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
