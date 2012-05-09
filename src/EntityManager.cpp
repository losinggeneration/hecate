#include "EntityManager.h"
#include "Component.h"
#include "Entity.h"
#include "World.h"
#include <SystemManager.h>

namespace hecate {

EntityManager::EntityManager(World *world) : world(world) {
	count = totalCreated = totalRemoved = nextAvailableId = 0;
}

EntityManager::~EntityManager() {
	std::set<Entity*>::iterator it = removedAndAvailable.begin();
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
	for(std::set<Entity*>::iterator it = activeEntities.begin(); it != activeEntities.end(); it++) {
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
	std::set<Entity*>::iterator it = activeEntities.find(e);
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

void EntityManager::addComponent(Entity *e, Component component) {
}

void EntityManager::refresh(Entity *e) {
	SystemManager *sm = world->getSystemManager();
	std::set<EntitySystem*> systems = sm->getSystems();
}

void EntityManager::removeComponent(Entity *e, Component component) {
}

// void EntityManager::removeComponent(Entity *e, ComponentType type) {
// }

// Component *EntityManager::getComponent(Entity *e, ComponentType type) {
// }

Entity *EntityManager::getEntity(int entityId) {

}

const std::set<Component*> EntityManager::getComponents(Entity *e) {
	return entityComponents;
}

}
