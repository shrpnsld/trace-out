add_executable(to-network-tests)

target_compile_features(to-network-tests
	PUBLIC
		cxx_std_98
)

target_compile_definitions(to-network-tests
	PRIVATE
		TRACE_OUT_TO_NETWORK="127.0.0.1:45678"
		TRACE_OUT_WIDTH=70
)

target_include_directories(to-network-tests
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(to-network-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(to-network-tests
	PRIVATE
		to-network.tests.cpp
)

