add_executable(sync-stream-option-tests)
target_compile_features(sync-stream-option-tests PUBLIC cxx_std_20)
target_compile_definitions(sync-stream-option-tests PRIVATE TRACE_OUT_STREAM="trace-out-to-test-stream.hpp")
target_compile_definitions(sync-stream-option-tests PRIVATE TRACE_OUT_WIDTH=70)
target_compile_definitions(sync-stream-option-tests PRIVATE TRACE_OUT_SYNC_STREAM)
target_include_directories(sync-stream-option-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_link_libraries(sync-stream-option-tests PRIVATE trace-out Catch2::Catch2WithMain helpers)

target_sources(sync-stream-option-tests
	PRIVATE
		sync-stream-option.tests.cpp
)

# TODO: add tests manually with timeout
catch_discover_tests(sync-stream-option-tests)

