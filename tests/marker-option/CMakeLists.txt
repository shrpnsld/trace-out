add_executable(marker-option-tests)
target_compile_features(marker-option-tests PUBLIC cxx_std_20)
target_compile_definitions(marker-option-tests PRIVATE TRACE_OUT_STREAM="trace-out-to-test-stream.hpp")
target_compile_definitions(marker-option-tests PRIVATE TRACE_OUT_WIDTH=70)
target_compile_definitions(marker-option-tests PRIVATE TRACE_OUT_MARKER="@@")
target_include_directories(marker-option-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_link_libraries(marker-option-tests PRIVATE trace-out Catch2::Catch2WithMain helpers)

target_sources(marker-option-tests
	PRIVATE
		marker-option.tests.cpp
)

catch_discover_tests(marker-option-tests)

