include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(hecate
	Component.cpp
	ComponentType.cpp
	ComponentTypeManager.cpp
	Entity.cpp
	EntityManager.cpp
	EntityProcessingSystem.cpp
	EntitySystem.cpp
	GroupManager.cpp
	SystemBitManager.cpp
	SystemManager.cpp
	TagManager.cpp
	World.cpp
)
