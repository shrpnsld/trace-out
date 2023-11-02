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

if (${TRACE_OUT_USE_UNITY_BUILDS})
	set_target_properties(helpers
		PROPERTIES
			UNITY_BUILD YES
			UNITY_BUILD_BATCH_SIZE ${TRACE_OUT_USE_UNITY_BUILDS}
	)
endif()

if (${TRACE_OUT_USE_PCH})
	add_library(pch-helpers INTERFACE)
	target_precompile_headers(pch-helpers
		INTERFACE
			"dummy.hpp"
			"test-stream.hpp"
	)
endif()

