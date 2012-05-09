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

GroupManager *World::getGroupManager() {
	return groupManager;
}

SystemManager *World::getSystemManager() {
	return systemManager;
}

EntityManager *World::getEntityManager() {
	return entityManager;
}

TagManager *World::getTagManager() {
	return tagManager;
}

// void World::setmanager(Manager manager) {
// }

// 	template<class T> T World::getManager(T managerType) {
// }

int World::getDelta() {
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

Entity *World::getEntity(int entityId) {
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
			groupManager->remove(*it);
			entityManager->remove(*it);
			tagManager->remove(*it);
		}
		deleted.clear();
	}
}

World& World::operator=(const World& other) {
	return *this;
}

}
