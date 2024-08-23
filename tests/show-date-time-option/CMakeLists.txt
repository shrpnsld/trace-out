#
# 'show-date-time-option-tests'

add_executable(show-date-time-option-tests)

target_compile_features(show-date-time-option-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-date-time-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_DATE_TIME
)

target_link_libraries(show-date-time-option-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(show-date-time-option-tests
	PRIVATE
		show-date-time-option.tests.cpp
)

catch_discover_tests(show-date-time-option-tests)

#
# 'show-date-time-option-and-start-macro-tests'

add_executable(show-date-time-option-and-start-macro-tests)

target_compile_features(show-date-time-option-and-start-macro-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-date-time-option-and-start-macro-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_DATE_TIME
)

target_link_libraries(show-date-time-option-and-start-macro-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(show-date-time-option-and-start-macro-tests
	PRIVATE
		show-date-time-option-and-start-macro.tests.cpp
)

catch_discover_tests(show-date-time-option-and-start-macro-tests)

#
# IDE

set_target_properties(show-date-time-option-tests PROPERTIES FOLDER tests)

#
# Build optimizations

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-date-time-option-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

