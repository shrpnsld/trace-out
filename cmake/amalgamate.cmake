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

add_library(trace-out-amalgamated INTERFACE)

target_include_directories(trace-out-amalgamated
	INTERFACE
		${PROJECT_BINARY_DIR}/trace-out-amalgamated
)

ExternalProject_Get_Property(amalgamate SOURCE_DIR)
set(AMALGAMATE_PATH ${SOURCE_DIR}/amalgamate)
set(INTERLUDE_PATH ${PROJECT_SOURCE_DIR}/data/options-for-amalgamated-sources.hpp)
set(FIRST_FILE trace-out/trace-out.hpp)
get_target_property(TRACE_OUT_SOURCE_DIR trace-out INTERFACE_INCLUDE_DIRECTORIES)
get_target_property_default(TRACE_OUT_INTERFACE_SOURCES trace-out INTERFACE_SOURCES "")
get_target_property_default(TRACE_OUT_SOURCES trace-out SOURCES "")

add_custom_target(trace-out.hpp
	DEPENDS ${PROJECT_BINARY_DIR}/trace-out-amalgamated/trace-out.hpp
)

add_custom_command(
	OUTPUT ${PROJECT_BINARY_DIR}/trace-out-amalgamated/trace-out.hpp
	COMMAND ${AMALGAMATE_PATH} -i ${TRACE_OUT_SOURCE_DIR} -n trace-out -L ${INTERLUDE_PATH} -g -1 ${FIRST_FILE} -b 1 -t -v
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
	DEPENDS ${TRACE_OUT_INTERFACE_SOURCES} ${TRACE_OUT_SOURCES} ${INTERLUDE_PATH}
	COMMENT "Amalgamating sources..."
)

add_dependencies(trace-out-amalgamated trace-out.hpp)
add_dependencies(trace-out.hpp amalgamate-update)

set_target_properties(trace-out.hpp PROPERTIES FOLDER amalgamation)

