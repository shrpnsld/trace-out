cmake_minimum_required(VERSION 3.19)

project(
	trace-out
	VERSION 1.0.0
	DESCRIPTION "Printf-debugging library"
	HOMEPAGE_URL https://github.com/shrpnsld/trace-out
	LANGUAGES CXX
)

enable_testing()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS YES)

add_subdirectory(src)

include(amalgamate)
include(install)
include(package)

add_subdirectory(tests)

