#
# 'show-header-and-show-thread-options-tests'

add_executable(show-header-and-show-thread-options-tests)

target_compile_features(show-header-and-show-thread-options-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-and-show-thread-options-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_THREAD
)

target_link_libraries(show-header-and-show-thread-options-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-and-show-thread-options-tests
	PRIVATE
		show-header-and-show-thread-options.tests.cpp
)

catch_discover_tests(show-header-and-show-thread-options-tests)

#
# IDE

set_target_properties(show-header-and-show-thread-options-tests PROPERTIES FOLDER tests)

#
# Build optimizations

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-and-show-thread-options-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

