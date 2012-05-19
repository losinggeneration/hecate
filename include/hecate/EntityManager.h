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

#ifndef HECATE_ENTITYMANAGER_H
#define HECATE_ENTITYMANAGER_H

#include <map>
#include <set>
#include <string>
#include <stdint.h>

#include "Types.h"

namespace hecate {

class Entity;
class Component;
class ComponentType;
class World;

class EntityManager {
public:
	EntityManager(World *world);
	virtual ~EntityManager();

	bool isActive(int entityId) const;
	int getEntityCount() const;
	long getTotalCreated() const;
	long getTotalRemoved() const;

protected:
	Entity *create();
	void remove(Entity *e);
	Entity *getEntity(int entityId) const;
	void refresh(Entity *e);

	void addComponent(Entity *e, Component *component);
	void removeComponent(Entity *e, Component *component);
	void removeComponent(Entity *e, const ComponentType &type);
	Component *getComponent(const Entity &e, const ComponentType &type);
	const componentSet_t getComponents(const Entity &e);

private:
	// hide the copy constructor and assignment operator
	EntityManager(const EntityManager& other) {}
	EntityManager &operator=(const EntityManager c) { return *this; }

	void removeComponentsOfEntity(Entity *e);

	typedef std::map<int, Component*> componentMap_t;
	typedef std::map<int, componentMap_t> componentsTypeMap_t;

	World *world;
	entitySet_t activeEntities;
	entitySet_t removedAndAvailable;
	int nextAvailableId;
	int count;
	uint64_t uniqueEntityId;
	long totalCreated;
	long totalRemoved;

	componentSet_t entityComponents;
	// Maped by type.id for components, and then by entity.id for each entity
	componentsTypeMap_t componentsByType;

	friend class Entity;
	friend class World;
	template<class T>
	friend class ComponentMapper;
};

}

#endif
