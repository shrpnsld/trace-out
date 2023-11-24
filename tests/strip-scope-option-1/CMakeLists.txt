add_executable(strip-scope-option-tests-1)

target_compile_features(strip-scope-option-tests-1
	PRIVATE
		cxx_std_11
)

target_compile_definitions(strip-scope-option-tests-1
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_STRIP_SCOPE=1
)

target_link_libraries(strip-scope-option-tests-1
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(strip-scope-option-tests-1
	PRIVATE
		strip-scope-option-1.tests.cpp
)

catch_discover_tests(strip-scope-option-tests-1)

set_target_properties(strip-scope-option-tests-1 PROPERTIES FOLDER tests)

if (TRACE_OUT_USE_PCH)
	target_link_libraries(strip-scope-option-tests-1
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

