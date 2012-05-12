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

	for(typename std::set<T*>::iterator it = otherTypes.begin(); it != otherTypes.end(); it++) {
		types.insert((*it));
	}

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
