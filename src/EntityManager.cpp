#include "EntityManager.h"
#include "Component.h"
#include "Entity.h"
#include "EntitySystem.h"
#include "SystemManager.h"
#include "World.h"

#include <typeinfo>

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
	entityComponents_t::iterator it = entityComponents.find(e);
	if(it != entityComponents.end()) {
		for(componentSet_t::iterator ct = (*it).second.begin(); ct != (*it).second.end(); ct++) {
			Component *c = (*ct);
			(*it).second.erase(ct++);
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

#ifndef NO_RTTI

template<class T> void EntityManager::removeComponent(Entity *e, T *t) {
	if(t->getType() == "") {
		t->setType(typeid(t).name());
	}

	removeComponent(e, t->getType());
}

template<class T> std::string EntityManager::addComponent(Entity *e, T *t) {
	t->setType(typeid(t).name());
	return addComponent(e, t->getType());
}
#endif

void EntityManager::removeComponent(Entity *e, Component *component) {
	entityComponents_t::iterator it = entityComponents.find(e);
	if(it != entityComponents.end()) {
		componentSet_t::iterator ct = (*it).second.find(component);
		if(ct != (*it).second.end()) {
			(*it).second.erase(component);
			delete component;
			component = NULL;
		}
	}
}

std::string EntityManager::addComponent(Entity *e, Component *component) {
	entityComponents[e].insert(component);
	return component->getType();
}

void EntityManager::removeComponent(Entity *e, std::string type) {
	entityComponents_t::iterator it = entityComponents.find(e);

	if(it != entityComponents.end()) {
		for(componentSet_t::iterator ct = (*it).second.begin(); ct != (*it).second.end();) {
			if((*ct)->getType() == type) {
				Component *t = (*ct);
				(*it).second.erase(ct++);
				delete t;
			}
			else {
				ct++;
			}
		}
	}
}

Component *EntityManager::getComponent(Entity *e, std::string type) {
	entityComponents_t::iterator it = entityComponents.find(e);
	if(it != entityComponents.end()) {
		for(componentSet_t::iterator ct = (*it).second.begin(); ct != (*it).second.end(); ct++) {
			if((*ct)->getType() == type) {
				return (*ct);
			}
		}
	}

	return NULL;
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
