#include <boost/test/unit_test.hpp>
#include "Bag.h"

using namespace hecate;

BOOST_AUTO_TEST_SUITE(Bag_Test)

BOOST_AUTO_TEST_CASE(Size_Case)
{
	Bag<int> i;
	int tmp;
	BOOST_CHECK(i.size() == 0);
	i.set(5, 1);
	BOOST_CHECK(i.size() == 6);
	tmp = i.capacity()+1;
	i.set(tmp, 2);
	tmp++;
	BOOST_CHECK(i.size() == tmp);
}

BOOST_AUTO_TEST_CASE(Index_Case)
{
	Bag<int> bag;

	for(int i = 0; i < 50; i++) {
		bag.set(i, i);
		std::cout << bag[i] << std::endl;
	}

	for(int i = 0; i < 50; i++) {
		std::cout << bag[i] << std::endl;
// 		BOOST_CHECK(bag.at(i) == i);
// 		BOOST_CHECK(bag[i] == i);
	}

	bag.clear();

	BOOST_CHECK(bag.size() == 0);

	for(int i = 0; i < 50; i++) {
		bag.add(i);
	}

	for(int i = 0; i < 50; i++) {
		std::cout << bag[i] << std::endl;
		BOOST_CHECK(bag.at(i) == i);
		BOOST_CHECK(bag[i] == i);
	}
}

BOOST_AUTO_TEST_SUITE_END()
