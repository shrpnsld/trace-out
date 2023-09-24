#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/out-stream.hpp"
#include "trace-out/statistics.hpp"
#include <algorithm>
#include <ctime>
#include <string>
#include <utility>
#include <vector>

//
// Public

namespace trace_out
{

inline void print_execution_time_in_milliseconds(const std::string &filename_line, const char *label, standard::uint64_t milliseconds);
inline void print_execution_time_in_clocks(const std::string &filename_line, const char *label, std::clock_t clocks, double milliseconds);
inline void print_execution_statistics(const std::string &filename_line, const char *label, std::vector<standard::uint64_t> &results, const char *units);

}

//
// Implementation

namespace trace_out
{

void print_execution_time_in_milliseconds(const std::string &filename_line, const char *label, standard::uint64_t milliseconds)
{
	out_stream stream(filename_line);
	stream << "// execution time \"" << label << "\": " << to_string(milliseconds) << " ms" << ENDLINE;
}

void print_execution_time_in_clocks(const std::string &filename_line, const char *label, std::clock_t clocks, double milliseconds)
{
	out_stream stream(filename_line);
	stream << "// execution time \"" << label << "\": " << to_string(clocks) << " clocks (" << to_string(milliseconds) << " ms)" << ENDLINE;
}

void print_execution_statistics(const std::string &filename_line, const char *label, std::vector<standard::uint64_t> &results, const char *units)
{
	out_stream stream(filename_line);

	if (results.empty())
	{
		stream << "// execution time statistics for \"" << label << "\" is not available" << ENDLINE;
		return;
	}

	std::sort(results.begin(), results.end());

	// average & median
	float average = average_value<float>(results.begin(), results.end());
	float median = median_value<float>(results.begin(), results.end());
	stream << "// execution time statistics (" << units << ") for \"" << label << "\":" << NEWLINE;
	stream << "//   avg/med: " << to_string(average) << " / " << to_string(median) << NEWLINE;

	// modes
	std::pair<std::vector<standard::uint64_t>, unsigned int> result = mode_values<standard::uint64_t>(results.begin(), results.end());
	std::vector<standard::uint64_t> modes = result.first;
	unsigned int occurances = result.second;
	float percentage = static_cast<float>(occurances) / static_cast<float>(results.size()) * 100.0f;
	if (modes.size() == 1)
	{
		stream << "//      mode: " << to_string(modes.front()) << " (" << to_string(percentage) << "% of all values)";
	}
	else if (modes.size() > 1)
	{
		stream << "//     modes: ";
		std::vector<standard::uint64_t>::iterator itr = modes.begin();
		stream << to_string(*itr);
		for (++itr; itr != modes.end(); ++itr)
		{
			stream << ", " << to_string(*itr);
		}

		stream << " (each = " << to_string(percentage) << "%, all = " << to_string(percentage * static_cast<float>(modes.size())) << "% of all values)";
	}

	stream << NEWLINE;

	// range
	stream << "//     range: " << to_string(results.back() - results.front()) << " [" << to_string(results.front()) << "..." << to_string(results.back()) << "]" << NEWLINE;
	stream << ENDLINE;
}

}

