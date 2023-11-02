add_executable(marker-option-tests)

target_compile_features(marker-option-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(marker-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_WIDTH=70
		TRACE_OUT_MARKER="@@"
)

target_link_libraries(marker-option-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(marker-option-tests
	PRIVATE
		marker-option.tests.cpp
)

catch_discover_tests(marker-option-tests)

set_target_properties(marker-option-tests PROPERTIES FOLDER tests)

if (TRACE_OUT_USE_PCH)
	target_link_libraries(marker-option-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

