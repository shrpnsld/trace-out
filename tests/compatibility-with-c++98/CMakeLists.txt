#
# 'compatibility-with-c++98'

add_executable(compatibility-with-c++98)

target_compile_features(compatibility-with-c++98
	PRIVATE
		cxx_std_98
)

target_compile_definitions(compatibility-with-c++98
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
)

target_link_libraries(compatibility-with-c++98
	PRIVATE
		dollar-store-catch2
		helpers
		trace-out
)

target_sources(compatibility-with-c++98
	PRIVATE
		t.tests.cpp
		t-base.tests.cpp
)

add_test("compatibility with C++98"
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/compatibility-with-c++98
)

#
# IDE

set_target_properties(compatibility-with-c++98 PROPERTIES FOLDER tests)

