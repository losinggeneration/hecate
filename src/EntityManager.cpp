/*
 * Copyright 2011 GAMADU.COM. All rights reserved.
 * Copyright 2012 Harley Laue. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Harley Laue ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Harley Laue OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of Harley Laue.
 */

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
	count = totalCreated = totalRemoved = 0;
	nextAvailableId = 1;
}

EntityManager::~EntityManager() {
	entitySet_t::iterator it = removedAndAvailable.begin();
	while(it != removedAndAvailable.end()) {
		Entity *e = *it;
		e->setTypeBits(0);
		refresh(e);
		removedAndAvailable.erase(it++);
		delete e;
	}

	it = activeEntities.begin();
	while(it != activeEntities.end()) {
		Entity *e = *it;
		e->setTypeBits(0);
		refresh(e);
		activeEntities.erase(it++);
		delete e;
	}
}

bool EntityManager::isActive(int entityId) const {
	for(entitySet_t::iterator it = activeEntities.begin(); it != activeEntities.end(); it++) {
		if((*it)->getId() == entityId) {
			return true;
		}
	}
	return false;
}

int EntityManager::getEntityCount() const {
	return count;
}

long EntityManager::getTotalCreated() const {
	return totalCreated;
}

long EntityManager::getTotalRemoved() const {
	return totalRemoved;
}

Entity *EntityManager::create() {
	// Reuse an entity over creating a new one
	Entity *e = NULL;

	if(!removedAndAvailable.empty()) {
		entitySet_t::iterator it = removedAndAvailable.begin();
		e = *it;
		e->reset();
		removedAndAvailable.erase(it);
	}
	else {
		e = new Entity(world, nextAvailableId++);
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

Entity *EntityManager::getEntity(int entityId) const {
	for(entitySet_t::iterator it = activeEntities.begin(); it != activeEntities.end(); it++) {
		if((*it)->getId() == entityId) {
			return *it;
		}
	}

	return NULL;
}

void EntityManager::refresh(Entity *e) {
	SystemManager *sm = world->getSystemManager();
	entitySystemSet_t systems = sm->getSystems();
	for(entitySystemSet_t::iterator it = systems.begin(); it != systems.end(); it++) {
		(*it)->change(e);
	}
}

void EntityManager::addComponent(Entity *e, Component *component) {
	ComponentType type = ComponentTypeManager::getTypeFor(*component);

	componentsByType[type.getId()][e->getId()] = component;

	e->addTypeBit(type.getBit());
}

void EntityManager::removeComponent(Entity *e, Component *component) {
	ComponentType type = ComponentTypeManager::getTypeFor(*component);
	removeComponent(e, type);
}

void EntityManager::removeComponent(Entity *e, const ComponentType &type) {
	componentsTypeMap_t::iterator it = componentsByType.find(type.getId());

	if(it != componentsByType.end()) {
		componentMap_t &components = componentsByType[type.getId()];
		componentMap_t::iterator ct = components.find(e->getId());
		if(ct != components.end()) {
			Component *c = ct->second;
			components.erase(ct);
			e->removeTypeBit(type.getBit());
			delete c;
		}
	}
}

Component *EntityManager::getComponent(const Entity &e, const ComponentType &type) {
	componentsTypeMap_t::iterator it = componentsByType.find(type.getId());

	if(it != componentsByType.end()) {
		componentMap_t &components = componentsByType[type.getId()];
		componentMap_t::iterator ct = components.find(e.getId());

		if(ct != components.end()) {
			return ct->second;
		}
	}

	return NULL;
}

const componentSet_t EntityManager::getComponents(const Entity &e) {
	entityComponents.clear();

	for(componentsTypeMap_t::iterator it = componentsByType.begin(); it != componentsByType.end(); it++) {
		componentMap_t &components = it->second;
		componentMap_t::iterator ct = components.find(e.getId());

		if(ct != components.end()) {
			entityComponents.insert(ct->second);
		}
	}

	return entityComponents;
}

void EntityManager::removeComponentsOfEntity(Entity *e) {
	for(componentsTypeMap_t::iterator it = componentsByType.begin(); it != componentsByType.end(); it++) {
		componentMap_t &components = it->second;

		componentMap_t::iterator ct = components.find(e->getId());
		if(ct != components.end()) {
			Component *c = ct->second;
			components.erase(ct);
			delete c;
		}
	}
}

}
