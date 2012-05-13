#include "GroupManager.h"
#include "Entity.h"

namespace hecate {

GroupManager::GroupManager(World *world) : world(world) {
}

void GroupManager::set(std::string group, const Entity &e) {
	remove(e); // An entity can only belong to one group
	entitiesByGroup[group].insert(const_cast<Entity*>(&e));
	groupByEntity[e.getId()] = group;
}

entitySet_t GroupManager::getEntities(std::string group) const {
	// this keeps it from needlessly adding groups if no entities exist in it
	entityGroupMap_t::const_iterator it = entitiesByGroup.find(group);

	if(it != entitiesByGroup.end()) {
		return it->second;
	}

	return EMPTY_SET;
}

void GroupManager::remove(const Entity &e) {
	groupMap_t::iterator it = groupByEntity.find(e.getId());

	if(it != groupByEntity.end()) {
		std::string group = it->second;
		groupByEntity.erase(it);
		entityGroupMap_t::iterator egt = entitiesByGroup.find(group);
		if(egt != entitiesByGroup.end()) {
			egt->second.erase(const_cast<Entity*>(&e));
		}
	}
}

std::string GroupManager::getGroupOf(const Entity &e) const {
	groupMap_t::const_iterator it = groupByEntity.find(e.getId());

	if(it != groupByEntity.end()) {
		return it->second;
	}

	return "";
}

bool GroupManager::isGrouped(const Entity &e) const {
	return getGroupOf(e) != "";
}

bool GroupManager::isInGroup(std::string group, const Entity &e) const {
	return group != "" && group != getGroupOf(e);
}

}
