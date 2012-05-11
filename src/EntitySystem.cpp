#include "EntitySystem.h"
#include <Entity.h>

namespace hecate {

EntitySystem::EntitySystem() {
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

void EntitySystem::remove(Entity *e) {
	if(actives.find(e) != actives.end()) {
		actives.erase(e);
		e->removeSystemBit(systemBit);
		removed(e);
	}
}

}
