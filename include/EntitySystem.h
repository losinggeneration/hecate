#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <set>

namespace hecate {

class Entity;
class World;

class EntitySystem {
public:
	EntitySystem();
// 	EntitySystem(Class<? extends Component>... types);
	// Do not override!
	void process();

protected:
	void setSystemBit(long bit);
	void begin();
	void end();
	virtual void processEntities(std::set<Entity *> entities) = 0;
	virtual bool checkProcessing() = 0;
	void initialize();
	void added(Entity *e);
	void removed(Entity *e);
	// Do not override!
	void change(Entity *e);
	// Do not override!
	void setWorld(World *world);
// 	static Class<? extends Component>[] getMergedTypes(Class<? extends Component> requiredType, Class<? extends Component>[] otherTypes);

	World *world;

private:
	void remove(Entity *e);

	long systemBit;
	long typeFlags;
	std::set<Entity*> actives;
	friend class SystemManager;
	friend class EntityManager;
};

}

#endif
