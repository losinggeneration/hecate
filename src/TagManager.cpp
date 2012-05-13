#include "TagManager.h"

namespace hecate {

TagManager::TagManager(World *world) : world(world) {
}

void TagManager::registerTag(std::string tag, const Entity &e) {
	entityByTag[tag] = const_cast<Entity*>(&e);
}

void TagManager::unregister(std::string tag) {
	entityByTag.erase(tag);
}

bool TagManager::isRegistered(std::string tag) const {
	return entityByTag.find(tag) != entityByTag.end();
}

Entity *TagManager::getEntity(std::string tag) const {
	stringEntityMap_t::const_iterator it = entityByTag.find(tag);

	if(it != entityByTag.end()) {
		return it->second;
	}

	return NULL;
}

void TagManager::remove(const Entity &e) {
	for(stringEntityMap_t::iterator it = entityByTag.begin(); it != entityByTag.end();){
		if(it->second == &e) {
			entityByTag.erase(it++);
		}
		else {
			it++;
		}
	}
}

}

