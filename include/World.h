#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <set>
#include <string>

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

#ifndef NO_RTTI
	template<class T> std::string setmanager(T *manager);
#else
	std::string setManager(Manager *manager, std::string name);
#endif
	template<class T> T *getManager(std::string managerType);

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

	int delta;
	std::set<Entity*> refreshed;
	std::set<Entity*> deleted;
	std::map<std::string, Manager*> managers;
};

}

#endif
