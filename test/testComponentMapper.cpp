#include <boost/test/unit_test.hpp>
#include "Component.h"
#include "ComponentMapper.h"
#include "Entity.h"
#include "World.h"

#include <vector>

using namespace hecate;
using namespace std;

class C1 : public Component {
};

class C2 : public Component {
};

BOOST_AUTO_TEST_SUITE(ComponentMapper_Test)

BOOST_AUTO_TEST_CASE(ComponentMapper_Constructor_Case) {
	World w;
	C1 c1;
	C2 c2;
	Entity *e1 = w.createEntity(), *e2 = w.createEntity();
	e1->addComponent(&c1);
	e1->addComponent(&c2);
	e2->addComponent(&c1);
	ComponentMapper<C1> cm1(C1(), &w);
	ComponentMapper<C2> cm2(C2(), &w);
	Component *c1a = e1->getComponent(c1);

	// Check that c1 is correctly returned
	BOOST_CHECK(&c1 == cm1.get(*e1));
	// Check that e1 & e2 both have c1
	BOOST_CHECK(cm1.get(*e1) == cm1.get(*e2));
	// e2 doesn't have a c2
	BOOST_CHECK(cm2.get(*e2) == NULL);
	// e2 doesn't have a c2, but e1 does
	BOOST_CHECK(cm2.get(*e1) != cm2.get(*e2));
}

BOOST_AUTO_TEST_SUITE_END()
