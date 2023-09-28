add_executable(off-option-tests)

target_compile_features(off-option-tests
	PUBLIC
		cxx_std_11
)

target_compile_definitions(off-option-tests
	PRIVATE
		TRACE_OUT_STREAM=test
		TRACE_OUT_WIDTH=70
		TRACE_OUT_OFF
)

target_link_libraries(off-option-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(off-option-tests
	PRIVATE
		off-option.tests.cpp
)

catch_discover_tests(off-option-tests)

