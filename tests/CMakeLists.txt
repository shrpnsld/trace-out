find_package(Catch2 3 REQUIRED)

add_executable(tests)
target_compile_definitions(tests PRIVATE TRACE_OUT_STREAM="helpers/trace-out-to-test-stream.hpp")
target_compile_definitions(tests PRIVATE TRACE_OUT_WIDTH=70)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_link_libraries(tests PRIVATE trace-out Catch2::Catch2WithMain)

target_compile_features(trace-out PUBLIC cxx_std_20)

add_subdirectory(src)

include(Catch)
catch_discover_tests(tests)

