#include <boost/test/unit_test.hpp>
#include "Component.h"
#include "ComponentTypeManager.h"
#include "Entity.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "TagManager.h"
#include "World.h"

using namespace hecate;

class C1 : public Component {
};

class C2 : public Component {
};

BOOST_AUTO_TEST_SUITE(World_Test)

BOOST_AUTO_TEST_CASE(EntityManager_Case)
{
	World w;
	EntityManager *em = w.getEntityManager();
	// Check initial case
	BOOST_CHECK(em->getEntityCount() == 0);
	BOOST_CHECK(em->getTotalCreated() == 0);
	BOOST_CHECK(em->getTotalRemoved() == 0);

	Entity *ep1 = w.createEntity();
	// Check that we have the correct count after one creation
	BOOST_CHECK(em->getEntityCount() == 1);
	BOOST_CHECK(em->getTotalCreated() == 1);
	BOOST_CHECK(em->getTotalRemoved() == 0);

	w.deleteEntity(ep1);
	w.loopStart();
	// Check for correct count after removal of one
	BOOST_CHECK(em->getEntityCount() == 0);
	BOOST_CHECK(em->getTotalCreated() == 1);
	BOOST_CHECK(em->getTotalRemoved() == 1);

	w.deleteEntity(ep1);
	w.loopStart();
	// Makes sure it can't delete more than once
	BOOST_CHECK(em->getEntityCount() == 0);
	BOOST_CHECK(em->getTotalCreated() == 1);
	BOOST_CHECK(em->getTotalRemoved() == 1);

	ep1 = w.createEntity();
	w.deleteEntity(ep1);
	w.deleteEntity(ep1);
	w.loopStart();
	// Make sure we can't delete more than once within the same loop
	BOOST_CHECK(em->getEntityCount() == 0);
	BOOST_CHECK(em->getTotalCreated() == 2);
	BOOST_CHECK(em->getTotalRemoved() == 2);
}

/// TODO make the asserts actually mean something useful here
BOOST_AUTO_TEST_CASE(Entity_Reuse_Case)
{
	World w;
	EntityManager *em = w.getEntityManager();
	Entity *ep1, *ep2;
	ep1 = w.createEntity();
	ep2 = w.createEntity();
	w.loopStart();
	w.deleteEntity(ep1);
	w.deleteEntity(ep2);
	w.loopStart();
	BOOST_CHECK(em->getEntityCount() == 0);
	BOOST_CHECK(em->getTotalRemoved() == 2);

	ep1 = w.createEntity();
	ep2 = w.createEntity();
	w.loopStart();
	BOOST_CHECK(em->getEntityCount() == 2);
	BOOST_CHECK(em->getTotalCreated() == 4);
	BOOST_CHECK(em->getTotalRemoved() == 2);
}

BOOST_AUTO_TEST_CASE(Entity_Component_Case)
{
	World w;
	Entity *ep1 = w.createEntity(), *ep2;
	C1 c1;
	C2 c2;
	ep1 = w.createEntity();
	ep2 = w.createEntity();
	ep1->addComponent(&c1);
	ep1->addComponent(&c2);
	ep2->addComponent(&c1);
	ComponentType ct1 = ComponentTypeManager::getTypeFor(c1), ct2 = ComponentTypeManager::getTypeFor(c2);

	C1 *c1g1 = ep1->getComponent(c1);
	BOOST_CHECK(c1g1 != NULL);

	C2 *c2g1 = ep1->getComponent(c2);
	BOOST_CHECK(c2g1 != NULL);

	Component *c1g2 = ep1->getComponent(ct1), *c2g2 = ep1->getComponent(ct2);
	BOOST_CHECK(c1g1 == c1g2);
	BOOST_CHECK(c2g1 == c2g2);

	// This entity does not have this component
	C2 *c2gn1 = ep2->getComponent(c2);
	Component *c2gn2 = ep2->getComponent(ct2);
	BOOST_CHECK(c2gn1 == c2gn2);
	BOOST_CHECK(c2gn1 == NULL);
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
