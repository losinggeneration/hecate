#include <boost/test/unit_test.hpp>
#include "Component.h"
#include "ComponentMapper.h"
#include "Entity.h"
#include "World.h"

#include <vector>

using namespace hecate;
using namespace std;

BOOST_AUTO_TEST_SUITE(ComponentMapper_Test)

BOOST_AUTO_TEST_CASE(ComponentMapper_Constructor_Case) {
	World w;
	Component c1, c2;
	Entity *e1 = w.createEntity();
	e1->addComponent(&c1);
	e1->addComponent(&c2);
// 	ComponentMapper<Component> cm1(&c1, &w), cm2(&c2, &w);
}

BOOST_AUTO_TEST_SUITE_END()
