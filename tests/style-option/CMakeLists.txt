#
# 'style-1-option-tests'

add_executable(style-1-option-tests)

target_compile_features(style-1-option-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(style-1-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_STYLE=1
)

target_link_libraries(style-1-option-tests
	PRIVATE
		trace-out
		helpers
		Catch2::Catch2WithMain
)

target_sources(style-1-option-tests
	PRIVATE
		style-1-option.tests.cpp
)

catch_discover_tests(style-1-option-tests)

#
# 'style-2-option-tests'

add_executable(style-2-option-tests)

target_compile_features(style-2-option-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(style-2-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_STYLE=2
)

target_link_libraries(style-2-option-tests
	PRIVATE
		trace-out
		helpers
		Catch2::Catch2WithMain
)

target_sources(style-2-option-tests
	PRIVATE
		style-2-option.tests.cpp
)

catch_discover_tests(style-2-option-tests)

#
# 'style-1-and-show-thread-options'

add_executable(style-1-and-show-thread-options-tests)

target_compile_features(style-1-and-show-thread-options-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(style-1-and-show-thread-options-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_STYLE=1
		TRACE_OUT_SHOW_THREAD
)

target_link_libraries(style-1-and-show-thread-options-tests
	PRIVATE
		trace-out
		helpers
		Catch2::Catch2WithMain
)

target_sources(style-1-and-show-thread-options-tests
	PRIVATE
		style-1-and-show-thread-options.tests.cpp
)

catch_discover_tests(style-1-and-show-thread-options-tests)

#
# 'style-2-and-show-thread-options'

add_executable(style-2-and-show-thread-options-tests)

target_compile_features(style-2-and-show-thread-options-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(style-2-and-show-thread-options-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_STYLE=2
		TRACE_OUT_SHOW_THREAD
)

target_link_libraries(style-2-and-show-thread-options-tests
	PRIVATE
		trace-out
		helpers
		Catch2::Catch2WithMain
)

target_sources(style-2-and-show-thread-options-tests
	PRIVATE
		style-2-and-show-thread-options.tests.cpp
)

catch_discover_tests(style-2-and-show-thread-options-tests)

#
# IDE

set_target_properties(style-1-option-tests PROPERTIES FOLDER tests)
set_target_properties(style-2-option-tests PROPERTIES FOLDER tests)
set_target_properties(style-1-and-show-thread-options-tests PROPERTIES FOLDER tests)
set_target_properties(style-2-and-show-thread-options-tests PROPERTIES FOLDER tests)

#
# Build optimizations

if (TRACE_OUT_USE_PCH)
	target_link_libraries(style-1-option-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(style-2-option-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(style-1-1and-show-thread-options-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(style-2-1and-show-thread-options-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

