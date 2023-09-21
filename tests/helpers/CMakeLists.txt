add_library(helpers)

target_sources(helpers
	INTERFACE
		trace-out-to-test-stream.hpp

	PUBLIC
		test-stream.hpp

	PRIVATE
		test-stream.cpp
)

target_include_directories(helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

