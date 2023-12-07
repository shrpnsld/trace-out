find_package(Catch2 3 REQUIRED)
include(Catch)

include(compile-options-if-supported)
include(build-optimizations)

set(TRACE_OUT_TEST_AMALGAMATED YES CACHE BOOL "Test amalgamated 'trace-out.hpp'")

if(TRACE_OUT_TEST_AMALGAMATED)
	add_library(trace-out ALIAS trace-out-amalgamated)
else()
	add_library(trace-out ALIAS trace-out-dev)
endif()

add_compile_options_if_supported("-Wall" "-Wextra" "/W4")

add_subdirectory(compatibility-with-c++98)
add_subdirectory(debug)
add_subdirectory(helpers)
add_subdirectory(indentation-option)
add_subdirectory(macros)
add_subdirectory(marker-option)
add_subdirectory(off-option)
add_subdirectory(show-file-line-option)
add_subdirectory(show-thread-option)
add_subdirectory(stream-to-endpoint-option)
add_subdirectory(stream-to-file-option)
add_subdirectory(stream-to-wdo-option)
add_subdirectory(strip-scope-option)
add_subdirectory(sync-stream-option)

