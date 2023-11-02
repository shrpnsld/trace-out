add_executable(strip-scope-option-tests-0)

target_compile_features(strip-scope-option-tests-0
	PRIVATE
		cxx_std_11
)

target_compile_definitions(strip-scope-option-tests-0
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_WIDTH=70
		TRACE_OUT_STRIP_SCOPE=0
)

target_link_libraries(strip-scope-option-tests-0
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(strip-scope-option-tests-0
	PRIVATE
		strip-scope-option-0.tests.cpp
)

catch_discover_tests(strip-scope-option-tests-0)

set_target_properties(strip-scope-option-tests-0 PROPERTIES FOLDER tests)

if (TRACE_OUT_USE_PCH)
	target_link_libraries(strip-scope-option-tests-0
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

