add_library(helpers-c++11)

target_compile_features(helpers-c++11
	PUBLIC
		cxx_std_11
)

target_include_directories(helpers-c++11
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(helpers-c++11
	PRIVATE
		lifecycle-tracker.cpp
		lifecycle-tracker.hpp
)

set_target_properties(helpers-c++11 PROPERTIES FOLDER tests)

