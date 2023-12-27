include(GNUInstallDirs)

install(CODE "execute_process(COMMAND cmake --build ${PROJECT_BINARY_DIR} --target trace-out.hpp)")
get_target_property(AMALGAMATED_INCLUDE_DIR_PATH trace-out INTERFACE_INCLUDE_DIRECTORIES)
set(TRACE_OUT_HPP_PATH "${AMALGAMATED_INCLUDE_DIR_PATH}/trace-out/trace-out.hpp")

install(
	FILES ${TRACE_OUT_HPP_PATH}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

