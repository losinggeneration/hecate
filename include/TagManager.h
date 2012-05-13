#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <map>
#include <string>

namespace hecate {

class Entity;
class World;

class TagManager {
public:
	TagManager(World *world);

	void registerTag(std::string tag, const Entity &e);
	void unregister(std::string tag);
	bool isRegistered(std::string tag) const;
	Entity *getEntity(std::string tag) const;

protected:
	void remove(const Entity &e);

private:
	typedef std::map<std::string, Entity*> stringEntityMap_t;
	World *world;
	stringEntityMap_t entityByTag;

	friend class World;
};

}

#endif // TAGMANAGER_H
