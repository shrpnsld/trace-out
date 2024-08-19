#
# 'show-file-line-option-tests'

add_executable(show-file-line-option-tests)

target_compile_features(show-file-line-option-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-file-line-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_FILE_LINE
)

target_link_libraries(show-file-line-option-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(show-file-line-option-tests
	PRIVATE
		show-file-line-option.tests.cpp
)

catch_discover_tests(show-file-line-option-tests)

#
# IDE

set_target_properties(show-file-line-option-tests PROPERTIES FOLDER tests)

#
# Build optimizations

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-file-line-option-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

