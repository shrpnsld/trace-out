include(GNUInstallDirs)

get_target_property(TRACE_OUT_AMALGAMATED_DIR trace-out.hpp BINARY_DIR)

install(CODE "execute_process(COMMAND cmake --build ${PROJECT_BINARY_DIR} --target trace-out.hpp)")

install(
	FILES ${TRACE_OUT_AMALGAMATED_DIR}/trace-out-amalgamated/trace-out.hpp
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

