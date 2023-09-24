add_executable(macros-tests)

target_compile_features(macros-tests
	PUBLIC
		cxx_std_20
)

target_compile_definitions(macros-tests
	PRIVATE
		TRACE_OUT_STREAM="trace-out-to-test-stream.hpp"
		TRACE_OUT_WIDTH=70
)

target_include_directories(macros-tests
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(macros-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(macros-tests
	PRIVATE
		clock-stats.tests.cpp
		clocks.tests.cpp
		e.tests.cpp
		f.tests.cpp
		for.tests.cpp
		if.tests.cpp
		indentation.tests.cpp
		m.tests.cpp
		p.tests.cpp
		r.tests.cpp
		return.tests.cpp
		t.tests.cpp
		time-stats.tests.cpp
		time.tests.cpp
		w.tests.cpp
		while.tests.cpp
)

catch_discover_tests(macros-tests)
