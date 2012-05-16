file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/hecate/*.h")
install(FILES ${files}
	DESTINATION include/hecate
)