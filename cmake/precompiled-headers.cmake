if (NOT TRACE_OUT_USE_PCH)
	return()
endif()

add_library(pch-standard INTERFACE)
target_precompile_headers(pch-standard
	INTERFACE
		<algorithm>
		<chrono>
		<cstdint>
		<iomanip>
		<iostream>
		<iterator>
		<limits>
		<list>
		<map>
		<memory>
		<ostream>
		<sstream>
		<string>
		<unordered_map>
		<utility>
		<vector>
		<catch2/catch_test_macros.hpp>
		<catch2/matchers/catch_matchers_string.hpp>
)

