#include <boost/test/unit_test.hpp>
#include "EntityManager.h"
#include "SystemManager.h"
#include "TagManager.h"
#include "World.h"

using namespace hecate;

BOOST_AUTO_TEST_SUITE(World_Test)

BOOST_AUTO_TEST_CASE(EntityManager_Case)
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

BOOST_AUTO_TEST_CASE(SystemManager_Case)
{
	World w;
	SystemManager *sm = w.getSystemManager();
}

BOOST_AUTO_TEST_CASE(TagManager_Case)
{
	World w;
	TagManager *tm = w.getTagManager();
	Entity *e1 = w.createEntity(), *e2 = w.createEntity(), *e3 = w.createEntity();
	tm->registerTag("Entity 1", *e1);
	BOOST_CHECK(tm->isRegistered("Entity 1"));
	BOOST_CHECK(tm->getEntity("Entity 1") == e1);
	tm->registerTag("Entity 2", *e2);
	BOOST_CHECK(tm->isRegistered("Entity 2"));
	BOOST_CHECK(tm->getEntity("Entity 2") == e2);
	tm->registerTag("Entity 1", *e3);
	BOOST_CHECK(tm->getEntity("Entity 1") != e1);
	BOOST_CHECK(tm->getEntity("Entity 1") == e3);
	tm->unregister("Entity 1");
	BOOST_CHECK(!tm->isRegistered("Entity 1"));
	BOOST_CHECK(tm->getEntity("Entity 1") != e1);
	// Make sure "Entity 2" is still valid
	BOOST_CHECK(tm->isRegistered("Entity 2"));
	BOOST_CHECK(tm->getEntity("Entity 2") == e2);
	tm->unregister("Entity 2");


}

BOOST_AUTO_TEST_SUITE_END()
