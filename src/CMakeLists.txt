#
# 'amalgamate' utility

include(ExternalProject)
include(get-property-default)

ExternalProject_Add(amalgamate
	GIT_REPOSITORY https://github.com/shrpnsld/amalgamate
	GIT_SHALLOW YES
	STEP_TARGETS update
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	EXCLUDE_FROM_ALL YES
)

#
# 'trace-out-dev'

add_library(trace-out-dev INTERFACE)
target_include_directories(trace-out-dev INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(trace-out)

#
# 'trace-out-amalgamated'

add_library(trace-out-amalgamated INTERFACE EXCLUDE_FROM_ALL)

target_include_directories(trace-out-amalgamated
	INTERFACE
		${PROJECT_BINARY_DIR}/trace-out-amalgamated/include/
)

ExternalProject_Get_Property(amalgamate SOURCE_DIR)
set(AMALGAMATE_PATH ${SOURCE_DIR}/amalgamate)
set(INTERLUDE_PATH ${PROJECT_SOURCE_DIR}/data/options-for-amalgamated-sources.hpp)
set(FIRST_FILE trace-out/trace-out.hpp)
get_target_property(AMALGAMATED_INCLUDE_DIR_PATH trace-out-amalgamated INTERFACE_INCLUDE_DIRECTORIES)
set(TRACE_OUT_HPP_PATH ${AMALGAMATED_INCLUDE_DIR_PATH}/trace-out/trace-out.hpp)
get_target_property(TRACE_OUT_SOURCE_DIR trace-out-dev INTERFACE_INCLUDE_DIRECTORIES)
get_target_property_default(TRACE_OUT_INTERFACE_SOURCES trace-out-dev INTERFACE_SOURCES "")
get_target_property_default(TRACE_OUT_SOURCES trace-out-dev SOURCES "")

add_custom_target(trace-out.hpp
	DEPENDS ${TRACE_OUT_HPP_PATH}
)

add_custom_command(
	OUTPUT  ${TRACE_OUT_HPP_PATH}
	COMMAND ${AMALGAMATE_PATH} -i ${TRACE_OUT_SOURCE_DIR} -n trace-out -L ${INTERLUDE_PATH} -g -1 ${FIRST_FILE} -b 1 -t -v
	COMMAND ${CMAKE_COMMAND} -E make_directory ${AMALGAMATED_INCLUDE_DIR_PATH}/trace-out
	COMMAND ${CMAKE_COMMAND} -E rename trace-out-amalgamated/trace-out.hpp ${TRACE_OUT_HPP_PATH}
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	DEPENDS ${TRACE_OUT_INTERFACE_SOURCES} ${TRACE_OUT_SOURCES} ${INTERLUDE_PATH}
	COMMENT "Amalgamating sources..."
)

add_dependencies(trace-out-amalgamated trace-out.hpp)
add_dependencies(trace-out.hpp amalgamate-update)

#
# IDE

set_target_properties(trace-out.hpp PROPERTIES FOLDER amalgamation)

