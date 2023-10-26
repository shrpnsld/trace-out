cmake_minimum_required(VERSION 3.19)

project(
	trace-out
	VERSION 1.0.0
	DESCRIPTION "Printf-debugging library"
	HOMEPAGE_URL https://github.com/shrpnsld/trace-out
	LANGUAGES CXX
)

enable_testing()

set_property(GLOBAL PROPERTY USE_FOLDERS YES)

add_subdirectory(src)
add_subdirectory(cmake)
add_subdirectory(tests)

