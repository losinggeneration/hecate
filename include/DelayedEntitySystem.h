#ifndef HECATE_DELAYEDENTITYSYSTEM_H
#define HECATE_DELAYEDENTITYSYSTEM_H

#include "EntitySystem.h"
#include "Types.h"

namespace hecate {

class Entity;

class DelayedEntitySystem : public EntitySystem {
public:
	template<class T> DelayedEntitySystem(std::set<T*> types);

	void startDelayedRun(int delay);
	int getInitialTimeDelay() const;
	int getRemainingTimeUntilProcessing() const;
	bool isRunning() const;
	void stop();

protected:
	// Do not override
	bool checkProcessing();
	// Do not override
	void processEntities(entitySet_t entities);
	virtual void processEntities(entitySet_t entities, int accumulatedDelta) = 0;

private:
	int delay;
	bool running;
	int acc;
};

}

#endif
