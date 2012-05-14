#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include <map>
#include <set>
#include <string>

#include "Types.h"

namespace hecate {

class Entity;
class World;

class GroupManager {
public:
	GroupManager(World *world);

	void set(std::string group, const Entity &e);
	entitySet_t getEntities(std::string group) const;
	void remove(const Entity &e);
	std::string getGroupOf(const Entity &e) const;
	bool isGrouped(const Entity &e) const;
	bool isInGroup(std::string group, const Entity &e) const;

private:
	typedef std::map<std::string, entitySet_t> entityGroupMap_t;
	typedef std::map<int, std::string> groupMap_t;

	World *world;
	entitySet_t EMPTY_SET;
	entityGroupMap_t entitiesByGroup;
	groupMap_t groupByEntity;
};

}

#endif // GROUPMANAGER_H
