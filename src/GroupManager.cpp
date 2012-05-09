#include "GroupManager.h"

namespace hecate {

GroupManager::GroupManager(World *world) : world(world) {
}

void GroupManager::set(std::string group, Entity *e) {
}

// 	ImmutableBag<Entity> GroupManager::getEntities(std::string group) {
// }

void GroupManager::remove(Entity *e) {
}

std::string GroupManager::getGroupOf(Entity *e) {
}

bool GroupManager::isGrouped(Entity *e) {
}

bool GroupManager::isInGroup(std::string group, Entity *e) {
}

}
