include(get-property-default)

set(TRACE_OUT_BUILD_AMALGAMATED YES CACHE BOOL "Build amalgamated 'trace-out.hpp'")

#
# 'trace-out'

if (TRACE_OUT_BUILD_AMALGAMATED)
	add_library(trace-out INTERFACE EXCLUDE_FROM_ALL)
	target_include_directories(trace-out INTERFACE ${PROJECT_BINARY_DIR}/trace-out-amalgamated/include)

	add_subdirectory(trace-out)

	set(AMALGAMATE_PATH ${PROJECT_SOURCE_DIR}/external/amalgamate/amalgamate)
	set(INTERLUDE_PATH ${PROJECT_SOURCE_DIR}/data/options-for-amalgamated-sources.hpp)
	set(FIRST_FILE trace-out/trace-out.hpp)
	get_target_property(AMALGAMATED_INCLUDE_DIR_PATH trace-out INTERFACE_INCLUDE_DIRECTORIES)
	set(TRACE_OUT_HPP_PATH ${AMALGAMATED_INCLUDE_DIR_PATH}/trace-out/trace-out.hpp)
	get_target_property_default(TRACE_OUT_INTERFACE_SOURCES trace-out INTERFACE_SOURCES "")
	get_target_property_default(TRACE_OUT_SOURCES trace-out SOURCES "")

	add_custom_target(trace-out.hpp
		DEPENDS ${TRACE_OUT_HPP_PATH}
	)

	add_custom_command(
		OUTPUT  ${TRACE_OUT_HPP_PATH}
		COMMAND ${AMALGAMATE_PATH} -i ${CMAKE_CURRENT_SOURCE_DIR} -n trace-out -L ${INTERLUDE_PATH} -g -1 ${FIRST_FILE} -b 1 -t -v
		COMMAND ${CMAKE_COMMAND} -E make_directory ${AMALGAMATED_INCLUDE_DIR_PATH}/trace-out
		COMMAND ${CMAKE_COMMAND} -E rename trace-out-amalgamated/trace-out.hpp ${TRACE_OUT_HPP_PATH}
		WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		DEPENDS ${TRACE_OUT_INTERFACE_SOURCES} ${TRACE_OUT_SOURCES} ${INTERLUDE_PATH}
		COMMENT "Amalgamating sources..."
	)

	add_dependencies(trace-out trace-out.hpp)

	#
	# IDE

	set_target_properties(trace-out.hpp PROPERTIES FOLDER amalgamation)
else()
	add_library(trace-out INTERFACE)
	target_include_directories(trace-out INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

	add_subdirectory(trace-out)
endif()

