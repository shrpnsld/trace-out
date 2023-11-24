add_executable(debug EXCLUDE_FROM_ALL)

target_compile_features(debug
	PRIVATE
		cxx_std_11
)

target_link_libraries(debug
	PRIVATE
		trace-out
)

target_sources(debug
	PRIVATE
		main.cpp
)

set_target_properties(debug PROPERTIES FOLDER tests)

