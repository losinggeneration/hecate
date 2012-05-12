#ifndef ENTITY_H
#define ENTITY_H

#include <set>
#include <string>

#include "Types.h"

namespace hecate {

class World;
class EntityManager;
class Component;
class ComponentType;

class Entity {
public:
	int getId();
	long getUniqueId();

	void addComponent(Component *component);
	void removeComponent(Component *component);
	void removeComponent(const ComponentType &type);

	bool isActive();

	Component *getComponent(const ComponentType &type);
	template<class T> T *getComponent(T *type);

	componentSet_t getComponents();

	void refresh();
	void deleteEntity();

	void setGroup(std::string group);
	void setTag(std::string tag);

	std::string toString();

protected:
    Entity(World *world, int id);
	~Entity();
	void setUniqueId(long uniqueId);
	long getTypeBits();
	void addTypeBit(long bit);
	void removeTypeBit(long bit);
	void setTypeBits(long typeBits);
	long getSystemBits();
	void addSystemBit(long bit);
	void removeSystemBit(long bit);
	void setSystemBits(long systemBits);
	void reset();
	friend class World;
	friend class EntityManager;
	friend class EntitySystem;

private:
	int id;
	long uniqueId;
	long typeBits;
	long systemBits;

	World *world;
	EntityManager *entityManager;
};

}

#endif // ENTITY_H
