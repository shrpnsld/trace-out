add_library(trace-out INTERFACE)
target_include_directories(trace-out INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(trace-out)

