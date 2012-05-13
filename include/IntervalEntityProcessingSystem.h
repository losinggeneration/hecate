#ifndef HECATE_INTERVALENTITYPROCESSINGSYSTEM_H
#define HECATE_INTERVALENTITYPROCESSINGSYSTEM_H

#include "IntervalEntitySystem.h"
#include "Types.h"

namespace hecate {

	class Entity;

	class IntervalEntityProcessingSystem : public IntervalEntitySystem {
	public:
		template<class T> IntervalEntityProcessingSystem(int interval, T *requiredType, std::set<T*> otherTypes);

	protected:
		virtual void process(Entity *e, int accumulatedDelta) = 0;
		void processEntities(entitySet_t entities, int accumulatedDelta);
	};

}

#endif
