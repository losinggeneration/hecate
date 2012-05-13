find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(HECATE_TEST_SRCS
	testRunner.cpp
	testGroupManager.cpp
	testWorld.cpp
)

add_executable(test_hecate ${HECATE_TEST_SRCS})
target_link_libraries(test_hecate hecate ${Boost_LIBRARIES})

