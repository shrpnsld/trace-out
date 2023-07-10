target_sources(trace-out
	PRIVATE
		integer.hpp
		printfamily.hpp
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
	add_subdirectory(gcc-like)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	add_subdirectory(mvs)
else()
	message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER_ID} is not supported")
endif()

