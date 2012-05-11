#include "SystemManager.h"
#include "EntitySystem.h"
#include "SystemBitManager.h"
#include "World.h"

#ifndef NO_RTTI
#include <typeinfo>
#endif

namespace hecate {

SystemManager::SystemManager(World *world) : world(world) {
}

SystemManager::~SystemManager() {
}

#ifndef NO_RTTI

template<class T> EntitySystem *SystemManager::setSystem(T *system) {
	return setSystem(system, typeid(system).name());
}

#endif

EntitySystem *SystemManager::setSystem(EntitySystem *system, std::string type) {
	system->setWorld(world);

	systems[type] = system;

	if(sets.find(system) != sets.end()) {
		sets.insert(system);
	}

	system->setSystemBit(SystemBitManager::getBitFor(system));

	return system;
}

EntitySystem *SystemManager::getSystem(std::string type) {
	systemsMap_t::iterator it = systems.find(type);
	if(it != systems.end()) {
		return (*it).second;
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
