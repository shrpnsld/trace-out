add_executable(off-option-tests)
target_compile_features(off-option-tests PUBLIC cxx_std_20)
target_compile_definitions(off-option-tests PRIVATE TRACE_OUT_STREAM="trace-out-to-test-stream.hpp")
target_compile_definitions(off-option-tests PRIVATE TRACE_OUT_WIDTH=70)
target_compile_definitions(off-option-tests PRIVATE TRACE_OUT_OFF)
target_include_directories(off-option-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_link_libraries(off-option-tests PRIVATE trace-out Catch2::Catch2WithMain helpers)

target_sources(off-option-tests
	PRIVATE
		off-option.tests.cpp
)

catch_discover_tests(off-option-tests)

