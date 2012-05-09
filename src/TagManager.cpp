#include "TagManager.h"

namespace hecate {

TagManager::TagManager(World *world) : world(world) {
}

void TagManager::registerTag(std::string tag, Entity *e) {
}

void TagManager::unregister(std::string tag) {
}

bool TagManager::isRegistered(std::string tag) {
}

Entity *TagManager::getEntity(std::string tag) {
}

void TagManager::remove(Entity *e) {
}

}

