#ifndef HECTATE_COMPONENTTYPE_H
#define HECTATE_COMPONENTTYPE_H

namespace hecate {

class ComponentType {
public:
	ComponentType() {
		init();
	}

	long getBit() {
		return bit;
	}

	int getId() {
		return id;
	}

private:
	void init() {
		bit = nextBit;
		nextBit <<= 1;
		id = nextId++;
	}

	static long nextBit;
	static int nextId;

	long bit;
	int id;
};

}

#endif
