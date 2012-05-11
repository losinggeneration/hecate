#ifndef HECATE_SYSTEMBITMANAGER_H
#define HECATE_SYSTEMBITMANAGER_H

#include <map>

namespace hecate {

class EntitySystem;

class SystemBitManager {
public:
	static long getBitFor(EntitySystem *es) {
		static std::map<EntitySystem *, long> systemBits;
		static int POS = 0;
		long bit;

		if(systemBits.find(es) == systemBits.end()) {
			bit = 1 << POS++;
			systemBits[es] = bit;
		}
		else {
			bit = systemBits[es];
		}

		return bit;
	}

private:
	SystemBitManager() {}
	SystemBitManager &operator=(const SystemBitManager &s) { return *this; }
};

}

#endif
