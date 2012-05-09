project(artemis)
cmake_minimum_required(VERSION 2.8)

option(BUILD_UNIT_TESTS "Build unit tests for the framework" off)

add_subdirectory(src)

if(${BUILD_UNIT_TESTS})
	add_subdirectory(test)
endif()
