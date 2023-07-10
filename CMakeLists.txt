cmake_minimum_required(VERSION 3.15)

project(
	trace-out
	VERSION 1.0
	DESCRIPTION "Printf-debugging library"
	HOMEPAGE_URL https://github.com/shrpnsld/trace-out
	LANGUAGES CXX
)

add_library(trace-out)
add_library(trace-out::lib ALIAS trace-out)

target_include_directories(trace-out
	PUBLIC src
)

add_subdirectory(src)
add_subdirectory(tests)

