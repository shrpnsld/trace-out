add_executable(show-thread-option-tests)

target_compile_features(show-thread-option-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-thread-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_WIDTH=70
		TRACE_OUT_SHOW_THREAD
)

target_link_libraries(show-thread-option-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(show-thread-option-tests
	PRIVATE
		show-thread-option.tests.cpp
)

catch_discover_tests(show-thread-option-tests)

set_target_properties(show-thread-option-tests PROPERTIES FOLDER tests)

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-thread-option-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

