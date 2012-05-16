include_directories(${CMAKE_SOURCE_DIR}/include/hecate)

set(HECATE_FILES
	ComponentType.cpp
	ComponentTypeManager.cpp
	DelayedEntityProcessingSystem.cpp
	DelayedEntitySystem.cpp
	Entity.cpp
	EntityManager.cpp
	EntityProcessingSystem.cpp
	EntitySystem.cpp
	GroupManager.cpp
	IntervalEntityProcessingSystem.cpp
	IntervalEntitySystem.cpp
	SystemBitManager.cpp
	SystemManager.cpp
	TagManager.cpp
	World.cpp
)

add_library(hecate_static STATIC
	${HECATE_FILES}
)

set_target_properties(hecate_static PROPERTIES VERSION ${HECATE_VERSION})

install(
	TARGETS hecate_static
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

# Rename the hecate_static output
set_target_properties(hecate_static PROPERTIES OUTPUT_NAME "hecate")
# Tell it where the default prefix should be
set_target_properties(hecate_static PROPERTIES PREFIX "lib")
# And make sure for <=2.6 it doesn't clober the shared library files
set_target_properties(hecate_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# Shared library
if(BUILD_SHARED_LIBRARY)

	add_library(hecate SHARED
		${HECATE_FILES}
	)

	set_target_properties(hecate PROPERTIES VERSION ${HECATE_VERSION})

	# And make sure for <=2.6 it doesn't clober the static library files
	set_target_properties(hecate PROPERTIES CLEAN_DIRECT_OUTPUT 1)

	install(
		TARGETS hecate
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
	)
endif(BUILD_SHARED_LIBRARY)
