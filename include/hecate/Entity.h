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
