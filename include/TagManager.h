#ifndef TAGMANAGER_H
#define TAGMANAGER_H
#include <string>

namespace hecate {

class Entity;
class World;

class TagManager {
public:
	TagManager(World *world);

	void registerTag(std::string tag, Entity *e);
	void unregister(std::string tag);
	bool isRegistered(std::string tag);
	Entity *getEntity(std::string tag);

protected:
	void remove(Entity *e);

private:
	World *world;
	friend class World;
};

}

#endif // TAGMANAGER_H
