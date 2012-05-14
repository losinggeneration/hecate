#ifndef HECATE_INTERVALENTITYSYSTEM_H
#define HECATE_INTERVALENTITYSYSTEM_H

#include "EntitySystem.h"
#include "Types.h"

namespace hecate {

class Entity;

class IntervalEntitySystem : public EntitySystem {
public:
	template<class T> IntervalEntitySystem(int interval, std::set<T*> types);

protected:
	bool checkProcessing();

private:
	int acc;
	int interval;
};

}

#endif
