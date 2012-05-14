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

#ifndef WORLD_H
#define WORLD_H

#include <set>
#include "Types.h"

namespace hecate {

class GroupManager;
class SystemManager;
class EntityManager;
class TagManager;
class Manager;
class Entity;

class World {
public:
	World();
	virtual ~World();

	GroupManager *getGroupManager() const;
	SystemManager *getSystemManager() const;
	EntityManager *getEntityManager() const;
	TagManager *getTagManager() const;

	void setManager(Manager *manager);
	template<class T> T *getManager(const T &managerType) const;

	int getDelta() const;
	void setDelta(int delta);

	void deleteEntity(Entity *e);
	void refreshEntity(Entity *e);
	Entity *createEntity();
	Entity *getEntity(int entityId) const;

	void loopStart();

protected:
	World(const World& other);
	virtual World& operator=(const World& other);

private:
	SystemManager *systemManager;
	EntityManager *entityManager;
	TagManager *tagManager;
	GroupManager *groupManager;

	typedef std::set<Manager*> managerSet_t;

	int delta;
	entitySet_t refreshed;
	entitySet_t deleted;
	managerSet_t managers;
};

}

#endif
