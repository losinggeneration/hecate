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
	Entity *getEntity(int entityId);
	void refresh(Entity *e);

	void addComponent(Entity *e, Component *component);
	void removeComponent(Entity *e, Component *component);
	void removeComponent(Entity *e, const ComponentType &type);
	Component *getComponent(Entity *e, const ComponentType &type);
	const componentSet_t getComponents(Entity *e);

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
	long uniqueEntityId;
	long totalCreated;
	long totalRemoved;

	componentSet_t entityComponents;
	// Maped by type.id for components, and then by entity.id for each entity
	componentsTypeMap_t componentsByType;
	friend class Entity;
	friend class World;
};

}

#endif // ENTITYMANAGER_H
