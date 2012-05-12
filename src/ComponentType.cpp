#include "ComponentType.h"

namespace hecate {

ComponentType::ComponentType() {
	init();
}

void ComponentType::init() {
	static int nextId;
	static long nextBit;
	id = nextId++;
	bit = nextBit;
	nextBit <<= 1;
}

int ComponentType::getId() {
	return id;
}

long ComponentType::getBit() {
	return bit;
}

}