add_executable(indentation-option-tests)

target_compile_features(indentation-option-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(indentation-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_WIDTH=70
		TRACE_OUT_INDENTATION="  "
)

target_link_libraries(indentation-option-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(indentation-option-tests
	PRIVATE
		indentation-option.tests.cpp
)

catch_discover_tests(indentation-option-tests)

set_target_properties(indentation-option-tests PROPERTIES FOLDER tests)

