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

#ifndef HECATE_ENTITY_H
#define HECATE_ENTITY_H

#include <set>
#include <string>

#include "ComponentTypeManager.h"
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
	template<class T> T *getComponent(const T &type) const {
		return dynamic_cast<T*>(getComponent(ComponentTypeManager::getTypeFor(type)));
	}

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
	uint64_t getTypeBits()const ;
	void addTypeBit(uint64_t bit);
	void removeTypeBit(uint64_t bit);
	void setTypeBits(uint64_t typeBits);
	uint64_t getSystemBits() const;
	void addSystemBit(uint64_t bit);
	void removeSystemBit(uint64_t bit);
	void setSystemBits(uint64_t systemBits);
	void reset();
	friend class World;
	friend class EntityManager;
	friend class EntitySystem;

private:
	int id;
	long uniqueId;
	uint64_t typeBits;
	uint64_t systemBits;

	World *world;
	EntityManager *entityManager;
};

}

#endif
