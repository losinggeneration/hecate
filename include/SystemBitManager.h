#ifndef HECATE_SYSTEMBITMANAGER_H
#define HECATE_SYSTEMBITMANAGER_H

#include <map>

namespace hecate {

class EntitySystem;

class SystemBitManager {
public:
	static long getBitFor(EntitySystem *es);

private:
	SystemBitManager() {}
	SystemBitManager &operator=(const SystemBitManager &s) { return *this; }
};

}

#endif
