include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(hecate
	Entity.cpp
	EntityManager.cpp
	GroupManager.cpp
	SystemManager.cpp
	TagManager.cpp
	World.cpp
)
