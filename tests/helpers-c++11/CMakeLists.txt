add_library(helpers-c++11)

target_include_directories(helpers-c++11
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(helpers-c++11 PRIVATE cxx_std_11)

target_sources(helpers-c++11
	INTERFACE
		lifecycle-tracker.hpp

	PRIVATE
		lifecycle-tracker.cpp
)

