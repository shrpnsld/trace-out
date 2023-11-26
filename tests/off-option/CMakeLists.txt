#
# off-option-tests

add_executable(off-option-tests)

target_compile_features(off-option-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(off-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_OFF
)

target_link_libraries(off-option-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(off-option-tests
	PRIVATE
		off-option.tests.cpp
)

catch_discover_tests(off-option-tests)

#
# IDE

set_target_properties(off-option-tests PROPERTIES FOLDER tests)

#
# Build optimizations

if (TRACE_OUT_USE_PCH)
	target_link_libraries(off-option-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

