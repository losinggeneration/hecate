#include <boost/test/unit_test.hpp>
#include "EntityManager.h"
#include "GroupManager.h"
#include "SystemManager.h"
#include "TagManager.h"
#include "World.h"

using namespace hecate;

BOOST_AUTO_TEST_SUITE(World_Test)

BOOST_AUTO_TEST_CASE(EntityManager_test)
{
	World w;
	EntityManager *em = w.getEntityManager();
	BOOST_CHECK(em->getEntityCount() == 0);
	BOOST_CHECK(em->getTotalCreated() == 0);
	BOOST_CHECK(em->getTotalRemoved() == 0);
	Entity *ep = w.createEntity();
	BOOST_CHECK(em->getEntityCount() == 1);
	BOOST_CHECK(em->getTotalCreated() == 1);
	BOOST_CHECK(em->getTotalRemoved() == 0);
	w.deleteEntity(ep);
	w.loopStart();
	BOOST_CHECK(em->getEntityCount() == 0);
	BOOST_CHECK(em->getTotalCreated() == 1);
	BOOST_CHECK(em->getTotalRemoved() == 1);
	w.deleteEntity(ep);
	w.loopStart();
	BOOST_CHECK(em->getEntityCount() == 0);
	BOOST_CHECK(em->getTotalCreated() == 1);
	BOOST_CHECK(em->getTotalRemoved() == 1);
}

BOOST_AUTO_TEST_CASE(GroupManager_test)
{
	World w;
	GroupManager *gm = w.getGroupManager();
}

BOOST_AUTO_TEST_CASE(SystemManager_test)
{
	World w;
	SystemManager *sm = w.getSystemManager();
}

BOOST_AUTO_TEST_CASE(TagManager_test)
{
	World w;
	TagManager *tm = w.getTagManager();
}

BOOST_AUTO_TEST_SUITE_END()
