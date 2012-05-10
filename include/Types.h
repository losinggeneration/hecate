#ifndef HECATE_TYPES_H
#define HECATE_TYPES_H

#include <map>
#include <set>

namespace hecate {

class Entity;
class Component;
class EntitySystem;

typedef std::set<Entity*> entitySet_t;
typedef std::set<Component*> componentSet_t;
typedef std::map<Entity*, componentSet_t> entityComponents_t;
typedef std::set<EntitySystem*> entitySystemSet_t;

}

#endif
