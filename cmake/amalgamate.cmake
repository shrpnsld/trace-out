include(ExternalProject)

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
		${CMAKE_CURRENT_BINARY_DIR}/trace-out-amalgamated
)

ExternalProject_Get_Property(amalgamate SOURCE_DIR)
set(AMALGAMATE_PATH ${SOURCE_DIR}/amalgamate)
set(INTERLUDE_PATH ${PROJECT_SOURCE_DIR}/data/options-for-amalgamated-sources.hpp)
set(FIRST_FILE trace-out/trace-out.hpp)
get_target_property(TRACE_OUT_SOURCE_DIR trace-out INTERFACE_INCLUDE_DIRECTORIES)

add_custom_target(trace-out.hpp
	${AMALGAMATE_PATH} -i ${TRACE_OUT_SOURCE_DIR} -n trace-out -L ${INTERLUDE_PATH} -g -1 ${FIRST_FILE} -b 1 -t -v
	COMMENT "Amalgamating sources..."
	DEPENDS trace-out
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_dependencies(trace-out-amalgamated trace-out.hpp)
add_dependencies(trace-out.hpp amalgamate-update)

set_target_properties(trace-out.hpp PROPERTIES FOLDER amalgamation)

