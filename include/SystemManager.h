#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

namespace hecate {

class EntitySystem;
class World;

class SystemManager {
public:
	SystemManager(World *world);
	~SystemManager();

	EntitySystem setSystem(EntitySystem system);
// 	EntitySystem getSystem(type);
// 	systems getSystems();

	void initializeAll();

private:
	World *world;
// 	Map<Class<?>, EntitySystem> systems;
// 	Bag<EntitySystem> bagged;
};

}

#endif // SYSTEMMANAGER_H
