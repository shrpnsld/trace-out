cmake_minimum_required(VERSION 3.19)

project(
	trace-out
	VERSION 1.0
	DESCRIPTION "Printf-debugging library"
	HOMEPAGE_URL https://github.com/shrpnsld/trace-out
	LANGUAGES CXX
)

enable_testing()

add_library(trace-out INTERFACE)
add_library(trace-out::lib ALIAS trace-out)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
	target_compile_options(trace-out INTERFACE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(trace-out INTERFACE /W4)
endif()

target_include_directories(trace-out
	INTERFACE src
)

add_subdirectory(src)
add_subdirectory(tests)

