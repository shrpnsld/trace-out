add_executable(compatibility-with-c++98 EXCLUDE_FROM_ALL)

target_compile_features(compatibility-with-c++98
	PRIVATE
		cxx_std_98
)

target_compile_definitions(compatibility-with-c++98
	PRIVATE
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_FILE_LINE
		TRACE_OUT_INDENTATION="  "
		TRACE_OUT_STRIP_SCOPE=1
		TRACE_OUT_SYNC_STREAM
		TRACE_OUT_SHOW_THREAD
		TRACE_OUT_WIDTH=70
)

target_link_libraries(compatibility-with-c++98
	PRIVATE
		helpers
		trace-out
)

target_sources(compatibility-with-c++98
	PRIVATE
		compatibility-with-c++98.cpp
)

add_test("compatibility with C++98"
	COMMAND
		${CMAKE_COMMAND}
		--build "${PROJECT_BINARY_DIR}"
		--target "compatibility-with-c++98"
)

set_target_properties(compatibility-with-c++98 PROPERTIES FOLDER tests)

