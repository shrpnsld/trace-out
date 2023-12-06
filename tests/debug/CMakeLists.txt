#
# 'debug'

include(compile-options-if-supported)

add_executable(debug EXCLUDE_FROM_ALL)

target_compile_features(debug
	PRIVATE
		cxx_std_11
)

target_compile_options_if_supported(debug PRIVATE "-g" "/ZI")

target_link_libraries(debug
	PRIVATE
		trace-out
)

target_sources(debug
	PRIVATE
		main.cpp
)

#
# IDE

set_target_properties(debug PROPERTIES FOLDER tests)

