#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include <string>

namespace hecate {

class Entity;
class World;

class GroupManager {
public:
	GroupManager(World *world);

	void set(std::string group, Entity *e);
// 	ImmutableBag<Entity> getEntities(std::string group);
	void remove(Entity *e);
	std::string getGroupOf(Entity *e);
	bool isGrouped(Entity *e);
	bool isInGroup(std::string group, Entity *e);

private:
	World *world;
};

}

#endif // GROUPMANAGER_H
