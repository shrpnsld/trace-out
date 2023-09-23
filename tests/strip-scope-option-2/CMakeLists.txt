add_executable(strip-scope-option-tests-2)
target_compile_features(strip-scope-option-tests-2 PUBLIC cxx_std_20)
target_compile_definitions(strip-scope-option-tests-2 PRIVATE TRACE_OUT_STREAM="trace-out-to-test-stream.hpp")
target_compile_definitions(strip-scope-option-tests-2 PRIVATE TRACE_OUT_WIDTH=70)
target_compile_definitions(strip-scope-option-tests-2 PRIVATE TRACE_OUT_STRIP_SCOPE=2)
target_include_directories(strip-scope-option-tests-2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_link_libraries(strip-scope-option-tests-2 PRIVATE trace-out Catch2::Catch2WithMain helpers)

target_sources(strip-scope-option-tests-2
	PRIVATE
		strip-scope-option-2.tests.cpp
)

catch_discover_tests(strip-scope-option-tests-2)

