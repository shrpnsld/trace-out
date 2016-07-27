#pragma once

#include <ctime>
#include <string>

#include "standard/integer.hpp"


namespace trace_out { namespace detail
{

	void print_execution_time_in_milliseconds(const std::string &filename_line, standard::uint64_t milliseconds);
	void print_execution_time_in_ticks(const std::string &filename_line, std::clock_t ticks, double milliseconds);

}
}

