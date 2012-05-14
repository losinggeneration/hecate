#include "ComponentType.h"

namespace hecate {

ComponentType::ComponentType() {
	init();
}

void ComponentType::init() {
	static int nextId = 1;
	static long nextBit = 1;
	id = nextId++;
	bit = nextBit;
	nextBit <<= 1;
}

int ComponentType::getId() const {
	return id;
}

long ComponentType::getBit() const {
	return bit;
}

}
