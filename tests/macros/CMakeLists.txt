add_executable(macros-tests)

target_compile_features(macros-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(macros-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
)

target_link_libraries(macros-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
		helpers-c++11
)

target_sources(macros-tests
	PRIVATE
		clock-stats.tests.cpp
		clocks.tests.cpp
		f.tests.cpp
		for.tests.cpp
		if.tests.cpp
		indentation.tests.cpp
		m.tests.cpp
		r.tests.cpp
		return.tests.cpp
		s.tests.cpp
		t.tests.cpp
		time-stats.tests.cpp
		time.tests.cpp
		while.tests.cpp
)

catch_discover_tests(macros-tests)

set_target_properties(macros-tests PROPERTIES FOLDER tests)

if (TRACE_OUT_USE_UNITY_BUILDS)
	set_target_properties(macros-tests
		PROPERTIES
			UNITY_BUILD YES
			UNITY_BUILD_BATCH_SIZE ${TRACE_OUT_USE_UNITY_BUILDS}
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(macros-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

