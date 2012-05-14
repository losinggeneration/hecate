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

#include "ComponentType.h"
#include "ComponentTypeManager.h"
#include "EntitySystem.h"
#include "Entity.h"

namespace hecate {

EntitySystem::EntitySystem() {
}

template<class T> EntitySystem::EntitySystem(std::set<T*> types) {
	for(typename std::set<T*>::iterator it = types.begin(); it != types.end(); it++) {
		ComponentType ct = ComponentTypeManager::getTypeFor(*it);
		typeFlags |= ct.getBit();
	}
}

void EntitySystem::process() {
	if(checkProcessing()) {
		begin();
		processEntities(actives);
		end();
	}
}

void EntitySystem::setSystemBit(long bit) {
	systemBit = bit;
}

void EntitySystem::begin() {
}

void EntitySystem::end() {
}

void EntitySystem::initialize() {
}

void EntitySystem::added(Entity *e) {
}

void EntitySystem::removed(Entity *e) {
}

void EntitySystem::change(Entity *e) {
	bool contains = (systemBit & e->getSystemBits()) == systemBit;
	bool interest = (typeFlags & e->getTypeBits()) == typeFlags;

	if (interest && !contains && typeFlags > 0) {
		actives.insert(e);
		e->addSystemBit(systemBit);
		added(e);
	} else if (!interest && contains && typeFlags > 0) {
		remove(e);
	}
}

void EntitySystem::setWorld(World *world) {
	this->world = world;
}

template<class T> std::set<T*> EntitySystem::getMergedTypes(T *requiredType, std::set<T*> otherTypes) {
	std::set<T*> types;

	types.insert(requiredType);
	types.insert(otherTypes.begin(), otherTypes.end());

	return types;
}

void EntitySystem::remove(Entity *e) {
	if(actives.find(e) != actives.end()) {
		actives.erase(e);
		e->removeSystemBit(systemBit);
		removed(e);
	}
}

}
