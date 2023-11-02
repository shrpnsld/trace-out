if (NOT TRACE_OUT_USE_CCACHE)
	return()
endif()

find_program(CCACHE_PROGRAM ccache)
if (NOT CCACHE_PROGRAM)
	message(SEND_ERROR "error: cannot find 'ccache'")
	return()
endif()

if (TRACE_OUT_USE_PCH)
	set(CCACHE_SLOPPINESS sloppiness=pch_defines,time_macros)
endif()

set(CMAKE_CXX_COMPILER_LAUNCHER
	${CCACHE_PROGRAM}
	base_dir=${PROJECT_SOURCE_DIR}
	cache_dir=${PROJECT_BINARY_DIR}/ccache
	${CCACHE_SLOPPINESS}
)

