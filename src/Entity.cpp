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

#include "Entity.h"
#include "Component.h"
#include "ComponentTypeManager.h"
#include "EntityManager.h"
#include "GroupManager.h"
#include "TagManager.h"
#include "World.h"

#include <string>
#include <sstream>

namespace hecate {

Entity::Entity(World *world, int id) : world(world), id(id), entityManager(world->getEntityManager()) {
}

Entity::~Entity() {
}

int Entity::getId() const {
	return id;
}

long Entity::getUniqueId() const {
	return uniqueId;
}

void Entity::addComponent(Component *component) {
	entityManager->addComponent(this, component);
}

void Entity::removeComponent(Component *component) {
	entityManager->removeComponent(this, component);
}

void Entity::removeComponent(const ComponentType &type) {
	entityManager->removeComponent(this, type);
}

bool Entity::isActive() const {
	return entityManager->isActive(id);
}

Component *Entity::getComponent(const ComponentType &type) const {
	return entityManager->getComponent(*this, type);
}

componentSet_t Entity::getComponents() const {
	return entityManager->getComponents(*this);
}

void Entity::refresh() {
	world->refreshEntity(this);
}

void Entity::deleteEntity() {
	world->deleteEntity(this);
}

void Entity::setGroup(std::string group) {
	world->getGroupManager()->set(group, *this);
}

void Entity::setTag(std::string tag) {
	world->getTagManager()->registerTag(tag, *this);
}

std::string Entity::toString() const {
	std::stringstream ss;
	std::string s;
	ss << "Entity[" << id << "]";
	ss >> s;
	return s;
}

void Entity::setUniqueId(long uniqueId) {
	this->uniqueId = uniqueId;
}

long Entity::getTypeBits() const {
	return typeBits;
}

void Entity::addTypeBit(long bit) {
	typeBits |= bit;
}

void Entity::removeTypeBit(long bit) {
	typeBits &= ~bit;
}

void Entity::setTypeBits(long bits) {
	typeBits = bits;
}

long Entity::getSystemBits() const {
	return systemBits;
}

void Entity::addSystemBit(long bit) {
	systemBits |= bit;
}

void Entity::removeSystemBit(long bit) {
	systemBits &= ~bit;
}

void Entity::setSystemBits(long systemBits) {
	this->systemBits = systemBits;
}

void Entity::reset() {
	systemBits = 0;
	typeBits = 0;
}

}
