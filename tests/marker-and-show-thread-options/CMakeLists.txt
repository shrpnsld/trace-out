#
# 'marker-and-show-thread-options-tests'

add_executable(marker-and-show-thread-options-tests)

target_compile_features(marker-and-show-thread-options-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(marker-and-show-thread-options-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_THREAD
)

target_link_libraries(marker-and-show-thread-options-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(marker-and-show-thread-options-tests
	PRIVATE
		marker-and-show-thread-options.tests.cpp
)

catch_discover_tests(marker-and-show-thread-options-tests)
#
# IDE

set_target_properties(
	marker-and-show-thread-options-tests

	PROPERTIES
		FOLDER tests
)

#
# Build optimizations

if (TRACE_OUT_USE_PCH)
	target_link_libraries(marker-and-show-thread-options-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

