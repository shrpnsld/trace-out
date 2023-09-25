add_library(helpers)

target_include_directories(helpers
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(helpers
	INTERFACE
		dummy.hpp
		fit.hpp
		framework-library-component.hpp
		trace-out-to-test-stream.hpp

	PUBLIC
		test-stream.hpp

	PRIVATE
		dummy.cpp
		test-stream.cpp
)

