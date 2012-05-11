include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(hecate
	Component.cpp
	Entity.cpp
	EntityManager.cpp
	EntityProcessingSystem.cpp
	EntitySystem.cpp
	GroupManager.cpp
	SystemManager.cpp
	TagManager.cpp
	World.cpp
)
