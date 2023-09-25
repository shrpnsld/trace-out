add_executable(strip-scope-option-tests-0)

target_compile_features(strip-scope-option-tests-0
	PUBLIC
		cxx_std_11
)

target_compile_definitions(strip-scope-option-tests-0
	PRIVATE
		TRACE_OUT_STREAM="trace-out-to-test-stream.hpp"
		TRACE_OUT_WIDTH=70
		TRACE_OUT_STRIP_SCOPE=0
)

target_include_directories(strip-scope-option-tests-0
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(strip-scope-option-tests-0
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(strip-scope-option-tests-0
	PRIVATE
		strip-scope-option-0.tests.cpp
)

catch_discover_tests(strip-scope-option-tests-0)

