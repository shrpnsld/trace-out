add_executable(strip-scope-option-tests-2)

target_compile_features(strip-scope-option-tests-2
	PRIVATE
		cxx_std_11
)

target_compile_definitions(strip-scope-option-tests-2
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_WIDTH=70
		TRACE_OUT_STRIP_SCOPE=2
)

target_link_libraries(strip-scope-option-tests-2
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(strip-scope-option-tests-2
	PRIVATE
		strip-scope-option-2.tests.cpp
)

catch_discover_tests(strip-scope-option-tests-2)

set_target_properties(strip-scope-option-tests-2 PROPERTIES FOLDER tests)

