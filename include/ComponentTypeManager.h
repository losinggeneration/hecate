#ifndef HECATE_COMPONENTTYPEMANAGER_H
#define HECATE_COMPONENTTYPEMANAGER_H

#include "ComponentType.h"

#include <map>

namespace hecate {

class Component;

class ComponentTypeManager {
public:
	static ComponentType getTypeFor(Component *c) {
		std::map<Component*, ComponentType>::iterator it = componentTypes.find(c);

		if(it == componentTypes.end()) {
			ComponentType type;
			return type;
		}

		return it->second;
	}

	static long getBit(Component *c) {
		return getTypeFor(c).getBit();
	}

	static int getId(Component *c) {
		return getTypeFor(c).getId();
	}

private:
	static std::map<Component*, ComponentType> componentTypes;
};

}

#endif
