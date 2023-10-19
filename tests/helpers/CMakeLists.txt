add_library(helpers)

target_include_directories(helpers
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(helpers
	PRIVATE
		dummy.cpp
		dummy.hpp
		fit.hpp
		framework-library-component.hpp
		test-stream.cpp
		test-stream.hpp
		trace-out-to-test-stream.hpp
)

set_target_properties(helpers PROPERTIES FOLDER tests)

