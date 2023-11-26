set(TRACE_OUT_TEST_AMALGAMATED YES CACHE BOOL "Turn on test for amalgamated header")

#
# amalgamated-header-verification-c++98

add_executable(amalgamated-header-verification-c++98 EXCLUDE_FROM_ALL)

target_compile_features(amalgamated-header-verification-c++98
	PRIVATE
		cxx_std_11
)

target_compile_definitions(amalgamated-header-verification-c++98
	PRIVATE
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_FILE_LINE
		TRACE_OUT_INDENTATION="  "
		TRACE_OUT_STRIP_SCOPE=1
		TRACE_OUT_SYNC_STREAM
		TRACE_OUT_SHOW_THREAD
		TRACE_OUT_STREAM_WIDTH=70
)

target_link_libraries(amalgamated-header-verification-c++98
	PRIVATE
		helpers
		trace-out-amalgamated
)

target_sources(amalgamated-header-verification-c++98
	PRIVATE
		amalgamated-header-verification-c++98.tests.cpp
)

if (TRACE_OUT_TEST_AMALGAMATED)
	add_test("amalgamated header verification C++98"
		COMMAND
			${CMAKE_COMMAND}
			--build "${PROJECT_BINARY_DIR}"
			--target "amalgamated-header-verification-c++98"
	)
endif()

#
# amalgamated-header-verification-c++11

add_executable(amalgamated-header-verification-c++11 EXCLUDE_FROM_ALL)

target_compile_features(amalgamated-header-verification-c++11
	PRIVATE
		cxx_std_11
)

target_compile_definitions(amalgamated-header-verification-c++11
	PRIVATE
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_FILE_LINE
		TRACE_OUT_INDENTATION="  "
		TRACE_OUT_STRIP_SCOPE=1
		TRACE_OUT_SYNC_STREAM
		TRACE_OUT_SHOW_THREAD
		TRACE_OUT_STREAM_WIDTH=70
)

target_link_libraries(amalgamated-header-verification-c++11
	PRIVATE
		helpers
		trace-out-amalgamated
)

target_sources(amalgamated-header-verification-c++11
	PRIVATE
		amalgamated-header-verification-c++11.tests.cpp
)

if (TRACE_OUT_TEST_AMALGAMATED)
	add_test("amalgamated header verification C++11"
		COMMAND
			${CMAKE_COMMAND}
			--build "${PROJECT_BINARY_DIR}"
			--target "amalgamated-header-verification-c++11"
	)
endif()

#
# amalgamated-header-verification-c++17

add_executable(amalgamated-header-verification-c++17 EXCLUDE_FROM_ALL)

target_compile_features(amalgamated-header-verification-c++17
	PRIVATE
		cxx_std_17
)

target_compile_definitions(amalgamated-header-verification-c++17
	PRIVATE
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_FILE_LINE
		TRACE_OUT_INDENTATION="  "
		TRACE_OUT_STRIP_SCOPE=1
		TRACE_OUT_SYNC_STREAM
		TRACE_OUT_SHOW_THREAD
		TRACE_OUT_STREAM_WIDTH=70
)

target_link_libraries(amalgamated-header-verification-c++17
	PRIVATE
		helpers
		trace-out-amalgamated
)

target_sources(amalgamated-header-verification-c++17
	PRIVATE
		amalgamated-header-verification-c++17.tests.cpp
)

if (TRACE_OUT_TEST_AMALGAMATED)
	add_test("amalgamated header verification C++17"
		COMMAND
			${CMAKE_COMMAND}
			--build "${PROJECT_BINARY_DIR}"
			--target "amalgamated-header-verification-c++17"
	)
endif()

#
# amalgamated-header-verification-c++23

add_executable(amalgamated-header-verification-c++23 EXCLUDE_FROM_ALL)

target_compile_features(amalgamated-header-verification-c++23
	PRIVATE
		cxx_std_23
)

target_compile_definitions(amalgamated-header-verification-c++23
	PRIVATE
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_FILE_LINE
		TRACE_OUT_INDENTATION="  "
		TRACE_OUT_STRIP_SCOPE=1
		TRACE_OUT_SYNC_STREAM
		TRACE_OUT_SHOW_THREAD
		TRACE_OUT_STREAM_WIDTH=70
)

target_link_libraries(amalgamated-header-verification-c++23
	PRIVATE
		helpers
		trace-out-amalgamated
)

target_sources(amalgamated-header-verification-c++23
	PRIVATE
		amalgamated-header-verification-c++23.tests.cpp
)

if (TRACE_OUT_TEST_AMALGAMATED)
	add_test("amalgamated header verification C++23"
		COMMAND
			${CMAKE_COMMAND}
			--build "${PROJECT_BINARY_DIR}"
			--target "amalgamated-header-verification-c++23"
	)
endif()

#
# IDE

set_target_properties(amalgamated-header-verification-c++98 PROPERTIES FOLDER tests)
set_target_properties(amalgamated-header-verification-c++11 PROPERTIES FOLDER tests)
set_target_properties(amalgamated-header-verification-c++17 PROPERTIES FOLDER tests)
set_target_properties(amalgamated-header-verification-c++23 PROPERTIES FOLDER tests)

