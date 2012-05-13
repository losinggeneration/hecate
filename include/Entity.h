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
	int getId() const;
	long getUniqueId() const;

	void addComponent(Component *component);
	void removeComponent(Component *component);
	void removeComponent(const ComponentType &type);

	bool isActive() const;

	Component *getComponent(const ComponentType &type) const;
	template<class T> T *getComponent(const T &type) const;

	componentSet_t getComponents() const;

	void refresh();
	void deleteEntity();

	void setGroup(std::string group);
	void setTag(std::string tag);

	std::string toString() const;

protected:
    Entity(World *world, int id);
	~Entity();
	void setUniqueId(long uniqueId);
	long getTypeBits()const ;
	void addTypeBit(long bit);
	void removeTypeBit(long bit);
	void setTypeBits(long typeBits);
	long getSystemBits() const;
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
