project(artemis)
cmake_minimum_required(VERSION 2.8)
set(HECATE_VERSION "0.1.0")

option(BUILD_UNIT_TESTS "Build unit tests for the framework" off)
option(BUILD_SHARED_LIBRARY "Build a shared library" off)

add_subdirectory(include)
add_subdirectory(src)

if(${BUILD_UNIT_TESTS})
	add_subdirectory(test)
endif()
