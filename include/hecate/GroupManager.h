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
