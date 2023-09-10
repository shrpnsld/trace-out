#pragma once

#include <ctime>
#include <string>
#include <vector>

#include "trace-out/standard/integer.hpp"


namespace trace_out { namespace detail
{

	void print_execution_time_in_milliseconds(const std::string &filename_line, const char *label, standard::uint64_t milliseconds);
	void print_execution_time_in_clocks(const std::string &filename_line, const char *label, std::clock_t clocks, double milliseconds);

	void print_execution_statistics(const std::string &filename_line, const char *label, std::vector<standard::uint64_t> &results, const char *units);
}
}
