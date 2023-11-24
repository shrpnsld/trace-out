add_executable(macros-tests-c++23)

target_compile_features(macros-tests-c++23
	PRIVATE
		cxx_std_23
)

target_compile_definitions(macros-tests-c++23
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_CPP_VERSION=202302L
)

target_link_libraries(macros-tests-c++23
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(macros-tests-c++23
	PRIVATE
		t.tests.cpp
)

catch_discover_tests(macros-tests-c++23)

set_target_properties(macros-tests-c++23 PROPERTIES FOLDER tests)

if (TRACE_OUT_USE_PCH)
	target_link_libraries(macros-tests-c++23
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

