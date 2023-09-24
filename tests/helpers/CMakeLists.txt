add_library(helpers)

target_sources(helpers
	INTERFACE
		dummy.hpp
		framework-library-component.hpp
		trace-out-to-test-stream.hpp

	PUBLIC
		test-stream.hpp

	PRIVATE
		dummy.cpp
		test-stream.cpp
)

target_compile_features(helpers
	PUBLIC
		cxx_std_20
)

target_include_directories(helpers
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

