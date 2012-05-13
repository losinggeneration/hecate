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
	if(managers.find(manager) == managers.end()) {
		managers.insert(manager);
	}
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
	if(deleted.find(e) == deleted.end()) {
		deleted.insert(e);
	}
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
