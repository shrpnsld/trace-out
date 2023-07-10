target_sources(trace-out
	PUBLIC
		trace-out.hpp
)

add_subdirectory(pretty-printing)
add_subdirectory(redirections)
add_subdirectory(standard)
add_subdirectory(stuff)
add_subdirectory(system)

