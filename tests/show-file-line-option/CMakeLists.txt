add_executable(show-file-line-option-test)

target_compile_features(show-file-line-option-test
	PUBLIC
		cxx_std_11
)

target_compile_definitions(show-file-line-option-test
	PRIVATE
		TRACE_OUT_STREAM="trace-out-to-test-stream.hpp"
		TRACE_OUT_WIDTH=70
		TRACE_OUT_SHOW_FILE_LINE
)

target_include_directories(show-file-line-option-test
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(show-file-line-option-test
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(show-file-line-option-test
	PRIVATE
		show-file-line-option.tests.cpp
)

catch_discover_tests(show-file-line-option-test)

