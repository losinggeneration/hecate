#include "EntitySystem.h"

namespace hecate {

EntitySystem::EntitySystem() {
}

void EntitySystem::process() {
}

void EntitySystem::setSystemBit(long bit) {
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
}

void EntitySystem::setWorld(World *world) {
	this->world = world;
}

void EntitySystem::remove(Entity *e) {
}

}
