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

template<class T> T *Entity::getComponent(const T &type) const {
	return dynamic_cast<T>(getComponent(ComponentTypeManager::getTypeFor(type)));
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
