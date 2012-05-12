#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <set>
#include <string>
#include "Types.h"

namespace hecate {

class GroupManager;
class SystemManager;
class EntityManager;
class TagManager;
class Manager;
class Entity;

class World {
public:
	World();
	virtual ~World();

	GroupManager *getGroupManager();
	SystemManager *getSystemManager();
	EntityManager *getEntityManager();
	TagManager *getTagManager();

	void setManager(Manager *manager);
	template<class T> T *getManager(T *managerType);

	int getDelta();
	void setDelta(int delta);

	void deleteEntity(Entity *e);
	void refreshEntity(Entity *e);
	Entity *createEntity();
	Entity *getEntity(int entityId);

	void loopStart();

protected:
	World(const World& other);
	virtual World& operator=(const World& other);

private:
	SystemManager *systemManager;
	EntityManager *entityManager;
	TagManager *tagManager;
	GroupManager *groupManager;

	typedef std::set<Manager*> managerSet_t;

	int delta;
	entitySet_t refreshed;
	entitySet_t deleted;
	managerSet_t managers;
};

}

#endif
