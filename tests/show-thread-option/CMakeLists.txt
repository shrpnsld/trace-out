add_executable(show-thread-option-tests)

target_compile_features(show-thread-option-tests
	PUBLIC
		cxx_std_20
)

target_compile_definitions(show-thread-option-tests
	PRIVATE
		TRACE_OUT_STREAM="trace-out-to-test-stream.hpp"
		TRACE_OUT_WIDTH=70
		TRACE_OUT_SHOW_THREAD
)

target_include_directories(show-thread-option-tests
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(show-thread-option-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(show-thread-option-tests
	PRIVATE
		show-thread-option.tests.cpp
)

catch_discover_tests(show-thread-option-tests)

