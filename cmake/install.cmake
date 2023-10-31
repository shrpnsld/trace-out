include(GNUInstallDirs)

install(CODE "execute_process(COMMAND cmake --build ${PROJECT_BINARY_DIR} --target trace-out.hpp)")

install(
	FILES ${PROJECT_BINARY_DIR}/trace-out-amalgamated/trace-out.hpp
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

