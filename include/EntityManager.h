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
	Entity *create();
	void remove(Entity *e);
	void removeComponentsOfEntity(Entity *e);
	void refresh(Entity *e);

	void removeComponent(Entity *e, Component *component);
	void addComponent(Entity *e, Component *component);
	void removeComponent(Entity *e, const ComponentType &type);
	Component *getComponent(Entity *e, const ComponentType &type);
	Entity *getEntity(int entityId);
	const componentSet_t getComponents(Entity *e);

private:
	// hide the copy constructor and assignment operator
	EntityManager(const EntityManager& other) {}
	EntityManager &operator=(const EntityManager c) { return *this; }

	typedef std::map<int, Component*> componentMap_t;
	typedef std::map<int, componentMap_t> componentsTypeMap_t;

	World *world;
	entitySet_t activeEntities;
	entitySet_t removedAndAvailable;
	int nextAvailableId;
	int count;
	long uniqueEntityId;
	long totalCreated;
	long totalRemoved;

	entityComponents_t entityComponents;
	componentsTypeMap_t componentsByType;
	friend class Entity;
	friend class World;
};

}

#endif // ENTITYMANAGER_H
