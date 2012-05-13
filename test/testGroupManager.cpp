#include <boost/test/unit_test.hpp>
#include "GroupManager.h"
#include "World.h"

#include <vector>

using namespace hecate;
using namespace std;

BOOST_AUTO_TEST_SUITE(GroupManager_Test)

BOOST_AUTO_TEST_CASE(GroupManager_getGroupOf_Case)
{
	World w;
	GroupManager *gm = w.getGroupManager();
	vector<Entity*> entities;

	for(int x =0; x < 100; x++) {
		entities.push_back(w.createEntity());
		if(x % 2) {
			gm->set("Group1", *entities.back());
		}
		else {
			gm->set("Group2", *entities.back());
		}
	}

	for(int x=0; x < 100; x++) {
		BOOST_CHECK(gm->isGrouped(*entities.at(x)));
		if(x % 2) {
			BOOST_CHECK(gm->getGroupOf(*entities.at(x)) == "Group1");
			BOOST_CHECK(gm->getGroupOf(*entities.at(x)) != "Group2");
		}
		else {
			BOOST_CHECK(gm->getGroupOf(*entities.at(x)) != "Group1");
			BOOST_CHECK(gm->getGroupOf(*entities.at(x)) == "Group2");
		}
	}
}

BOOST_AUTO_TEST_CASE(GroupManager_isInGroup_Case)
{
	World w;
	GroupManager *gm = w.getGroupManager();
	vector<Entity*> entities;

	for(int x =0; x < 100; x++) {
		entities.push_back(w.createEntity());
		if(x % 2) {
			gm->set("Group1", *entities.back());
		}
		else {
			gm->set("Group2", *entities.back());
		}
	}

	for(int x=0; x < 100; x++) {
		BOOST_CHECK(gm->isGrouped(*entities.at(x)));
		if(x % 2) {
			BOOST_CHECK(gm->isInGroup("Group1", *entities.at(x)));
			BOOST_CHECK(!gm->isInGroup("Group2", *entities.at(x)));
		}
		else {
			BOOST_CHECK(!gm->isInGroup("Group1", *entities.at(x)));
			BOOST_CHECK(gm->isInGroup("Group2", *entities.at(x)));
		}
	}
}

BOOST_AUTO_TEST_CASE(GroupManager_remove_Case)
{
	World w;
	GroupManager *gm = w.getGroupManager();
	vector<Entity*> entities;

	for(int x =0; x < 100; x++) {
		entities.push_back(w.createEntity());
		if(x % 2) {
			gm->set("Group1", *entities.back());
		}
		else {
			gm->set("Group2", *entities.back());
		}
	}

	for(int x=0; x < 100; x++) {
		BOOST_CHECK(gm->isGrouped(*entities.at(x)));
		if(x % 2) {
			gm->remove(*entities.at(x));
			BOOST_CHECK(!gm->isGrouped(*entities.at(x)));
			BOOST_CHECK(!gm->isInGroup("Group1", *entities.at(x)));
			BOOST_CHECK(!gm->isInGroup("Group2", *entities.at(x)));
		}
		else {
			BOOST_CHECK(!gm->isInGroup("Group1", *entities.at(x)));
			BOOST_CHECK(gm->isInGroup("Group2", *entities.at(x)));
		}
	}
}

BOOST_AUTO_TEST_CASE(GroupManager_getEntities_Case)
{
	World w;
	GroupManager *gm = w.getGroupManager();
	vector<Entity*> entities;

	for(int x =0; x < 100; x++) {
		entities.push_back(w.createEntity());
		if(x % 2) {
			gm->set("Group1", *entities.back());
		}
		else {
			gm->set("Group2", *entities.back());
		}
	}

	entitySet_t s1 = gm->getEntities("Group1"), s2 = gm->getEntities("Group2"), s3 = gm->getEntities("Group3");

	BOOST_CHECK(!s1.empty());
	BOOST_CHECK(!s2.empty());
	BOOST_CHECK(s3.empty());

	for(int x=0; x < 100; x++) {
		if(x % 2) {
			BOOST_CHECK(s1.find(entities.at(x)) != s1.end());
		}
		else {
			BOOST_CHECK(s2.find(entities.at(x)) != s2.end());
		}
	}
}

BOOST_AUTO_TEST_SUITE_END()
