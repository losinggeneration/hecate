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

#include "World.h"
#include "Entity.h"
#include "EntityManager.h"
#include "GroupManager.h"
#include "TagManager.h"
#include "SystemManager.h"

namespace hecate {

World::World() {
	entityManager = new EntityManager(this);
	groupManager = new GroupManager(this);
	systemManager = new SystemManager(this);
	tagManager = new TagManager(this);
}

World::World(const World& other) {
}

World::~World() {
	delete entityManager;
	delete groupManager;
	delete systemManager;
	delete tagManager;
}

GroupManager *World::getGroupManager() const {
	return groupManager;
}

SystemManager *World::getSystemManager() const {
	return systemManager;
}

EntityManager *World::getEntityManager() const {
	return entityManager;
}

TagManager *World::getTagManager() const {
	return tagManager;
}

void World::setManager(Manager *manager) {
	managers.insert(manager);
}

template<class T> T *World::getManager(const T &managerType) const {
	managerSet_t::iterator it = managers.find(managerType);
	if(it != managers.end()) {
		return dynamic_cast<T>(*it);
	}

	return NULL;
}

int World::getDelta() const {
	return delta;
}

void World::setDelta(int delta) {
	this->delta = delta;
}

void World::deleteEntity(Entity *e) {
	deleted.insert(e);
}

void World::refreshEntity(Entity *e) {
	refreshed.insert(e);
}

Entity *World::createEntity() {
	return entityManager->create();
}

Entity *World::getEntity(int entityId) const {
	return entityManager->getEntity(entityId);
}

void World::loopStart() {
	if(!refreshed.empty()) {
		for(std::set<Entity*>::iterator it = refreshed.begin(); it != refreshed.end(); it++) {
			entityManager->refresh(*it);
		}
		refreshed.clear();
	}
	if(!deleted.empty()) {
		for(std::set<Entity*>::iterator it = deleted.begin(); it != deleted.end(); it++) {
			groupManager->remove(**it);
			entityManager->remove(*it);
			tagManager->remove(**it);
		}
		deleted.clear();
	}
}

World& World::operator=(const World& other) {
	return *this;
}

}
