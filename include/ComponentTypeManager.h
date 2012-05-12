#ifndef HECATE_COMPONENTTYPEMANAGER_H
#define HECATE_COMPONENTTYPEMANAGER_H

#include "ComponentType.h"

namespace hecate {

class Component;

class ComponentTypeManager {
public:
	static ComponentType getTypeFor(const Component &c);
	static int getId(const Component &c);
	static long getSystemBit(const Component &c);
};

}

#endif
