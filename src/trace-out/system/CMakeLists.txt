target_sources(trace-out
	PRIVATE
		console.hpp
		constants.hpp
		mutex.cpp
		mutex.hpp
		thread-local-storage.hpp
		thread.hpp
		time.hpp
)

if (UNIX)
	add_subdirectory(posix)
elseif(WIN32)
	add_subdirectory(windows)
else()
	message(FATAL_ERROR "Platform ${CMAKE_SYSTEM} is not supported")
endif()

