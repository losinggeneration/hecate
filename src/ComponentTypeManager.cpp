#include "ComponentTypeManager.h"
#include "Component.h"

#include <map>

namespace hecate {

ComponentType ComponentTypeManager::getTypeFor(const Component &c) {
	static std::map<Component*, ComponentType> componentTypes;

	Component *com = const_cast<Component*>(&c);
	std::map<Component*, ComponentType>::iterator it = componentTypes.find(com);

	if(it == componentTypes.end()) {
			ComponentType type;
			componentTypes[com] = type;
			return type;
	}

	return it->second;
}

int ComponentTypeManager::getId(const Component &c) {
	return getTypeFor(c).getId();
}

long ComponentTypeManager::getSystemBit(const Component &c) {
	return getTypeFor(c).getBit();
}

}
