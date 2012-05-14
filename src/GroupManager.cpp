/*
 * Copyright 2011 GAMADU.COM. All rights reserved.
 * Copyright 2012 Harley Laue. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Harley Laue ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Harley Laue OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of Harley Laue.
 */

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
	return group != "" && group == getGroupOf(e);
}

}
