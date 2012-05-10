#include "EntityManager.h"
#include "Component.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "World.h"
#include <SystemManager.h>

namespace hecate {

EntityManager::EntityManager(World *world) : world(world) {
	count = totalCreated = totalRemoved = nextAvailableId = 0;
}

EntityManager::~EntityManager() {
	entitySet_t::iterator it = removedAndAvailable.begin();
	while(it != removedAndAvailable.end()) {
		Entity *e = *it;
		removedAndAvailable.erase(it++);
		delete e;
	}

	it = activeEntities.begin();
	while(it != activeEntities.end()) {
		Entity *e = *it;
		activeEntities.erase(it++);
		delete e;
	}
}

bool EntityManager::isActive(int entityId) {
	for(entitySet_t::iterator it = activeEntities.begin(); it != activeEntities.end(); it++) {
		if((*it)->getId() == entityId) {
			return true;
		}
	}
	return false;
}

int EntityManager::getEntityCount() {
	return count;
}

long EntityManager::getTotalCreated() {
	return totalCreated;
}

long EntityManager::getTotalRemoved() {
	return totalRemoved;
}

// Really shouldn't be using the copy constructor...
EntityManager::EntityManager(const EntityManager &other) : world(other.world) {
	count = totalCreated = totalRemoved = nextAvailableId = 0;
}

Entity *EntityManager::create() {
	// Reuse an entity over creating a new one
	Entity *e = *removedAndAvailable.end();

	if(e == NULL) {
		e = new Entity(world, nextAvailableId++);
	}
	else {
		e->reset();
	}

	activeEntities.insert(e);
	e->setUniqueId(uniqueEntityId++);

	count++;
	totalCreated++;

	return e;
}

void EntityManager::remove(Entity *e) {
	entitySet_t::iterator it = activeEntities.find(e);
	if(it != activeEntities.end()) {
		activeEntities.erase(it);

		e->setTypeBits(0);
		e->refresh();
		removeComponentsOfEntity(e);

		count--;
		totalRemoved++;

		removedAndAvailable.insert(e);
	}
}

void EntityManager::removeComponentsOfEntity(Entity *e) {
	for(int x = 0; x < componentsByType.size(); ++x) {
	}
}

void EntityManager::refresh(Entity *e) {
	SystemManager *sm = world->getSystemManager();
	entitySystemSet_t systems = sm->getSystems();
	for(entitySystemSet_t::iterator it = systems.begin(); it != systems.end(); it++) {
		(*it)->change(e);
	}
}

void EntityManager::removeComponent(Entity *e, Component *component) {
}

#ifndef NO_RTTI

std::string EntityManager::addComponent(Entity *e, Component *component) {
}

void EntityManager::removeComponent(Entity *e, std::string type) {
}

Component *EntityManager::getComponent(Entity *e, std::string type) {
}

#endif

Entity *EntityManager::getEntity(int entityId) {

}

const componentSet_t EntityManager::getComponents(Entity *e) {
	return entityComponents;
}

}
