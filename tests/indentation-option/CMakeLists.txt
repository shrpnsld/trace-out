add_executable(indentation-option-tests)
target_compile_features(indentation-option-tests PUBLIC cxx_std_20)
target_compile_definitions(indentation-option-tests PRIVATE TRACE_OUT_STREAM="trace-out-to-test-stream.hpp")
target_compile_definitions(indentation-option-tests PRIVATE TRACE_OUT_WIDTH=70)
target_compile_definitions(indentation-option-tests PRIVATE TRACE_OUT_INDENTATION="  ")
target_include_directories(indentation-option-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_link_libraries(indentation-option-tests PRIVATE trace-out Catch2::Catch2WithMain helpers)

target_sources(indentation-option-tests
	PRIVATE
		indentation-option.tests.cpp
)

catch_discover_tests(indentation-option-tests)

