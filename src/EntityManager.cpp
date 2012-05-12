#include "EntityManager.h"
#include "Component.h"
#include "ComponentType.h"
#include "ComponentTypeManager.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "SystemManager.h"
#include "World.h"

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
		refresh(e);
		removeComponentsOfEntity(e);

		count--;
		totalRemoved++;

		removedAndAvailable.insert(e);
	}
}

void EntityManager::removeComponentsOfEntity(Entity *e) {
	for(componentsTypeMap_t::iterator it = componentsByType.begin(); it != componentsByType.end(); it++) {
		componentMap_t components = (*it).second;

		componentMap_t::iterator ct = components.find(e->getId());
		if(ct != components.end()) {
			Component *c = (*ct).second;
			components.erase(ct);
			delete c;
		}
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
	ComponentType type = ComponentTypeManager::getTypeFor(*component);
	removeComponent(e, type);

}

void EntityManager::addComponent(Entity *e, Component *component) {
	ComponentType type = ComponentTypeManager::getTypeFor(*component);

	componentMap_t components = componentsByType[type.getId()];

	components[e->getId()] = component;

	e->addTypeBit(type.getBit());
}

void EntityManager::removeComponent(Entity *e, const ComponentType &type) {

}

Component *EntityManager::getComponent(Entity *e, const ComponentType &type) {

}

Entity *EntityManager::getEntity(int entityId) {
	for(entitySet_t::iterator it = activeEntities.begin(); it != activeEntities.end(); it++) {
		if((*it)->getId() == entityId) {
			return *it;
		}
	}

	return NULL;
}

const componentSet_t EntityManager::getComponents(Entity *e) {
	entityComponents_t::iterator it = entityComponents.find(e);
	if(it != entityComponents.end()) {
		// We found an entity, return the set associated with it
		return it->second;
	}

	// Return an empty set
	componentSet_t empty;
	return empty;
}

}
