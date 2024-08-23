#
# 'marker-and-show-date-time-and-show-file-line-options-and-start-macro-tests'

add_executable(marker-and-show-date-time-and-show-file-line-options-and-start-macro-tests)

target_compile_features(marker-and-show-date-time-and-show-file-line-options-and-start-macro-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(marker-and-show-date-time-and-show-file-line-options-and-start-macro-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=100
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_DATE_TIME
		TRACE_OUT_SHOW_FILE_LINE
)

target_link_libraries(marker-and-show-date-time-and-show-file-line-options-and-start-macro-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(marker-and-show-date-time-and-show-file-line-options-and-start-macro-tests
	PRIVATE
		marker-and-show-date-time-and-show-file-line-options-and-start-macro.tests.cpp
)

catch_discover_tests(marker-and-show-date-time-and-show-file-line-options-and-start-macro-tests)

#
# IDE

set_target_properties(marker-and-show-date-time-and-show-file-line-options-and-start-macro-tests PROPERTIES FOLDER tests)

#
# Build optimizations

if (TRACE_OUT_USE_PCH)
	target_link_libraries(marker-and-show-date-time-and-show-file-line-options-and-start-macro-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

