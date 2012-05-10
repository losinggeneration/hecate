#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include <set>
#include <string>

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

	bool isActive(int entityId);
	int getEntityCount();
	long getTotalCreated();
	long getTotalRemoved();

protected:
	EntityManager(const EntityManager& other);

	Entity *create();
	void remove(Entity *e);
	void removeComponentsOfEntity(Entity *e);
	void refresh(Entity *e);
	void removeComponent(Entity *e, Component *component);
#ifndef NO_RTTI
	std::string addComponent(Entity *e, Component *component);
	void removeComponent(Entity *e, std::string type);
	Component *getComponent(Entity *e, std::string type);
#endif
	Entity *getEntity(int entityId);
	const componentSet_t getComponents(Entity *e);

private:
	World *world;
	entitySet_t activeEntities;
	entitySet_t removedAndAvailable;
	int nextAvailableId;
	int count;
	long uniqueEntityId;
	long totalCreated;
	long totalRemoved;

	entityComponents_t componentsByType;
	componentSet_t entityComponents;
	friend class Entity;
	friend class World;
};

}

#endif // ENTITYMANAGER_H
