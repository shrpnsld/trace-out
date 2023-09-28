add_executable(macros-tests)

target_compile_features(macros-tests
	PUBLIC
		cxx_std_11
)

target_compile_definitions(macros-tests
	PUBLIC
		TRACE_OUT_STREAM=test
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
