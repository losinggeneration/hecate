#include "SystemBitManager.h"

namespace hecate {

long SystemBitManager::getBitFor(EntitySystem *es) {
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

}
