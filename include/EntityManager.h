#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <set>

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
	void addComponent(Entity *e, Component component);
	void refresh(Entity *e);
	void removeComponent(Entity *e, Component component);
	void removeComponent(Entity *e, ComponentType type);
	Component *getComponent(Entity *e, ComponentType type);
	Entity *getEntity(int entityId);
	const std::set<Component*> getComponents(Entity *e);

private:
	World *world;
	std::set<Entity*> activeEntities;
	std::set<Entity*> removedAndAvailable;
	int nextAvailableId;
	int count;
	long uniqueEntityId;
	long totalCreated;
	long totalRemoved;

	std::set<std::set<Component*> > componentsByType;
	std::set<Component*> entityComponents;
	friend class Entity;
	friend class World;
};

}

#endif // ENTITYMANAGER_H
