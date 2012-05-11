#include "Entity.h"
#include "Component.h"
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

int Entity::getId() {
	return id;
}

long Entity::getUniqueId() {
	return uniqueId;
}

void Entity::addComponent(Component *component) {
	entityManager->addComponent(this, component);
}

void Entity::removeComponent(Component *component) {
	entityManager->removeComponent(this, component);
}

void Entity::removeComponent(std::string type) {
	entityManager->removeComponent(this, type);
}

bool Entity::isActive() {
	return entityManager->isActive(id);
}

Component *Entity::getComponent(std::string type) {
	return entityManager->getComponent(this, type);
}

template<class T> T *Entity::getComponent(std::string type) {
	return dynamic_cast<T>(getComponent(type));
}

componentSet_t Entity::getComponents() {
	return entityManager->getComponents(this);
}

void Entity::refresh() {
	world->refreshEntity(this);
}

void Entity::deleteEntity() {
	world->deleteEntity(this);
}

void Entity::setGroup(std::string group) {
	world->getGroupManager()->set(group, this);
}

void Entity::setTag(std::string tag) {
	world->getTagManager()->registerTag(tag, this);
}

std::string Entity::toString() {
	std::stringstream ss;
	std::string s;
	ss << "Entity[" << id << "]";
	ss >> s;
	return s;
}

void Entity::setUniqueId(long uniqueId) {
	this->uniqueId = uniqueId;
}

long Entity::getTypeBits() {
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

long Entity::getSystemBits() {
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
