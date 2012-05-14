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

#ifndef ENTITYSYSTEM_H
#define ENTITYSYSTEM_H

#include <set>

namespace hecate {

class Entity;
class World;

class EntitySystem {
public:
	EntitySystem();
	template<class T> EntitySystem(std::set<T*> types);
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
	template<class T> static std::set<T*> getMergedTypes(T* requiredType, std::set<T*> otherTypes);

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
