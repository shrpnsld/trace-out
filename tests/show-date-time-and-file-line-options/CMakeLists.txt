#
# 'show-date-time-and-file-line-options-tests'

add_executable(show-date-time-and-file-line-options-tests)

target_compile_features(show-date-time-and-file-line-options-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-date-time-and-file-line-options-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_DATE_TIME
		TRACE_OUT_SHOW_FILE_LINE
)

target_link_libraries(show-date-time-and-file-line-options-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-date-time-and-file-line-options-tests
	PRIVATE
		show-date-time-and-file-line-options.tests.cpp
)

catch_discover_tests(show-date-time-and-file-line-options-tests)

#
# 'show-date-time-and-file-line-options-and-start-macro-tests'

add_executable(show-date-time-and-file-line-options-and-start-macro-tests)

target_compile_features(show-date-time-and-file-line-options-and-start-macro-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-date-time-and-file-line-options-and-start-macro-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=100
		TRACE_OUT_SHOW_DATE_TIME
		TRACE_OUT_SHOW_FILE_LINE
)

target_link_libraries(show-date-time-and-file-line-options-and-start-macro-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-date-time-and-file-line-options-and-start-macro-tests
	PRIVATE
		show-date-time-and-file-line-options-and-start-macro.tests.cpp
)

catch_discover_tests(show-date-time-and-file-line-options-and-start-macro-tests)

#
# IDE

set_target_properties(show-date-time-and-file-line-options-tests PROPERTIES FOLDER tests)
set_target_properties(show-date-time-and-file-line-options-and-start-macro-tests PROPERTIES FOLDER tests)

#
# Build optimizations

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-date-time-and-file-line-options-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-date-time-and-file-line-options-and-start-macro-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

