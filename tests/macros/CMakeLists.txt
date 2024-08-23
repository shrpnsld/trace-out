#
# 'macros-tests'

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
		tr.tests.cpp
		return.tests.cpp
		s.tests.cpp
		t-base.tests.cpp
		t-expression-nested.tests.cpp
		t.tests.cpp
		time-stats.tests.cpp
		time.tests.cpp
		while.tests.cpp
)

catch_discover_tests(macros-tests)

#
# 'start-no-message-tests'

add_executable(start-no-message-tests)

target_compile_features(start-no-message-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(start-no-message-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
)

target_link_libraries(start-no-message-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(start-no-message-tests
	PRIVATE
		start-no-message.tests.cpp
)

catch_discover_tests(start-no-message-tests)

#
# 'start-with-message-argument-1-tests'

add_executable(start-with-message-argument-1-tests)

target_compile_features(start-with-message-argument-1-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(start-with-message-argument-1-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
)

target_link_libraries(start-with-message-argument-1-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(start-with-message-argument-1-tests
	PRIVATE
		start-with-message-argument-1.tests.cpp
)

catch_discover_tests(start-with-message-argument-1-tests)

#
# 'start-with-message-argument-2-tests'

add_executable(start-with-message-argument-2-tests)

target_compile_features(start-with-message-argument-2-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(start-with-message-argument-2-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
)

target_link_libraries(start-with-message-argument-2-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(start-with-message-argument-2-tests
	PRIVATE
		start-with-message-argument-2.tests.cpp
)

catch_discover_tests(start-with-message-argument-2-tests)

#
# 'start-with-message-definition-1-tests'

add_executable(start-with-message-definition-1-tests)

target_compile_features(start-with-message-definition-1-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(start-with-message-definition-1-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_START_MESSAGE="one"
)

target_link_libraries(start-with-message-definition-1-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(start-with-message-definition-1-tests
	PRIVATE
		start-with-message-definition-1.tests.cpp
)

catch_discover_tests(start-with-message-definition-1-tests)

#
# 'start-with-message-definition-2-tests'

add_executable(start-with-message-definition-2-tests)

target_compile_features(start-with-message-definition-2-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(start-with-message-definition-2-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_START_MESSAGE="two"
)

target_link_libraries(start-with-message-definition-2-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(start-with-message-definition-2-tests
	PRIVATE
		start-with-message-definition-2.tests.cpp
)

catch_discover_tests(start-with-message-definition-2-tests)

#
# 'start-with-message-argument-and-definition-tests'

add_executable(start-with-message-argument-and-definition-tests)

target_compile_features(start-with-message-argument-and-definition-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(start-with-message-argument-and-definition-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_START_MESSAGE="one"
)

target_link_libraries(start-with-message-argument-and-definition-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(start-with-message-argument-and-definition-tests
	PRIVATE
		start-with-message-argument-and-definition.tests.cpp
)

catch_discover_tests(start-with-message-argument-and-definition-tests)

#
# 'macros-tests-c++17'

add_executable(macros-tests-c++17)

target_compile_features(macros-tests-c++17
	PRIVATE
		cxx_std_17
)

target_compile_definitions(macros-tests-c++17
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
)

target_link_libraries(macros-tests-c++17
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(macros-tests-c++17
	PRIVATE
		t-c++17.tests.cpp
)

catch_discover_tests(macros-tests-c++17)

#
# 'macros-tests-c++23'

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
		t-c++23.tests.cpp
)

catch_discover_tests(macros-tests-c++23)

#
# 'unique-variable-names'

add_executable(unique-variable-names EXCLUDE_FROM_ALL)

target_compile_features(unique-variable-names
	PRIVATE
		cxx_std_11
)

target_link_libraries(unique-variable-names
	PRIVATE
		helpers
		trace-out
)

target_sources(unique-variable-names
	PRIVATE
		unique-variable-names.tests.cpp
)

add_test("unique variable names"
	COMMAND
		${CMAKE_COMMAND}
		--build "${PROJECT_BINARY_DIR}"
		--target "unique-variable-names"
)

#
# IDE

set_target_properties(macros-tests PROPERTIES FOLDER tests)
set_target_properties(start-no-message-tests PROPERTIES FOLDER tests)
set_target_properties(start-with-message-argument-1-tests PROPERTIES FOLDER tests)
set_target_properties(start-with-message-argument-2-tests PROPERTIES FOLDER tests)
set_target_properties(start-with-message-definition-1-tests PROPERTIES FOLDER tests)
set_target_properties(start-with-message-definition-2-tests PROPERTIES FOLDER tests)
set_target_properties(start-with-message-argument-and-definition-tests PROPERTIES FOLDER tests)
set_target_properties(macros-tests-c++17 PROPERTIES FOLDER tests)
set_target_properties(macros-tests-c++23 PROPERTIES FOLDER tests)
set_target_properties(unique-variable-names PROPERTIES FOLDER tests)

#
# Build optimizations

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

if (TRACE_OUT_USE_PCH)
	target_link_libraries(start-no-message-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(start-with-message-argument-1-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(start-with-message-argument-2-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(start-with-message-definition-1-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(start-with-message-definition-2-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(start-with-message-argument-and-definition-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(macros-tests-c++17
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(macros-tests-c++23
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

