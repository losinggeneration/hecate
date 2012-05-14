/*
 * Copyright 2011 GAMADU.COM. All rights reserved.
 * Copyright 2012 Harley Laue. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Harley Laue ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Harley Laue OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of Harley Laue.
 */

#include "DelayedEntitySystem.h"
#include "World.h"

namespace hecate {

template<class T> DelayedEntitySystem::DelayedEntitySystem(std::set<T*> types) : EntitySystem(types) {
}

void DelayedEntitySystem::startDelayedRun(int delay) {
	this->delay = delay;
	this->acc = 0;
	running = true;
}

int DelayedEntitySystem::getInitialTimeDelay() const {
	return delay;
}

int DelayedEntitySystem::getRemainingTimeUntilProcessing() const {
	if(running) {
		return delay - acc;
	}

	return 0;
}

bool DelayedEntitySystem::isRunning() const {
	return running;
}

void DelayedEntitySystem::stop() {
	running = false;
	acc = 0;
}

bool DelayedEntitySystem::checkProcessing() {
	if(running) {
		acc += world->getDelta();

		if(acc >= delay) {
			return true;
		}
	}

	return false;
}

void DelayedEntitySystem::processEntities(entitySet_t entities) {
	processEntities(entities, acc);
}

}
