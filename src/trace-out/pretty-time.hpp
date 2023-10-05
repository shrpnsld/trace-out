#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/statistics.hpp"
#include "trace-out/pretty-lines.hpp"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <ostream>
#include <utility>
#include <vector>

//
// Public

namespace trace_out
{

inline void print_execution_time_in_milliseconds(std::ostream &stream, const file_line_t &file_line, const char *label, standard::uint64_t milliseconds);
inline void print_execution_time_in_clocks(std::ostream &stream, const file_line_t &file_line, const char *label, std::clock_t clocks, double milliseconds);
inline void print_execution_statistics(std::ostream &stream, const file_line_t &file_line, const char *label, std::vector<standard::uint64_t> &results, const char *units);

}

//
// Implementation

namespace trace_out
{

void print_execution_time_in_milliseconds(std::ostream &stream, const file_line_t &file_line, const char *label, standard::uint64_t milliseconds)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << '"' << label << "\" timed in " << std::setbase(10) << milliseconds << " ms" << std::endl;
}

void print_execution_time_in_clocks(std::ostream &stream, const file_line_t &file_line, const char *label, std::clock_t clocks, double milliseconds)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << '"' << label << "\" clocked in " << clocks << " clocks (" << milliseconds << " ms)" << std::endl;
}

void print_execution_statistics(std::ostream &stream, const file_line_t &file_line, const char *label, std::vector<standard::uint64_t> &results, const char *units)
{
	if (results.empty())
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << "// execution time statistics for \"" << label << "\" is not available" << std::endl;
		return;
	}

	std::sort(results.begin(), results.end());

	// average & median
	float average = average_value<float>(results.begin(), results.end());
	float median = median_value<float>(results.begin(), results.end());

	// modes
	std::pair<std::vector<standard::uint64_t>, unsigned int> result = mode_values<standard::uint64_t>(results.begin(), results.end());
	std::vector<standard::uint64_t> modes = result.first;
	unsigned int occurances = result.second;
	float percentage = static_cast<float>(occurances) / static_cast<float>(results.size()) * 100.0f;

	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif
		stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << "// execution time statistics (" << units << ") for \"" << label << "\":\n";
		stream << CONTINUE_PARAGRAPH << "//   avg/med: " << average << " / " << median << '\n';
		if (modes.size() == 1)
		{
			stream << CONTINUE_PARAGRAPH << "//      mode: " << modes.front() << " (" << percentage << "% of all values)";
		}
		else if (modes.size() > 1)
		{
			stream << CONTINUE_PARAGRAPH << "//     modes: ";
			std::vector<standard::uint64_t>::iterator itr = modes.begin();
			stream << *itr;
			for (++itr; itr != modes.end(); ++itr)
			{
				stream << ", " << *itr;
			}

			stream << " (each = " << percentage << "%, all = " << (percentage * static_cast<float>(modes.size())) << "% of all values)";
		}

		stream << '\n';

		// range
		stream << CONTINUE_PARAGRAPH << "//     range: " << (results.back() - results.front()) << " [" << (results.front()) << "..." << (results.back()) << "]\n" << SEPARATE_PARAGRAPH << std::endl;
	}
}

}

