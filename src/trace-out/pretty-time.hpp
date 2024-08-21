#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/pretty-lines.hpp"
#include "trace-out/statistics.hpp"
#include "trace-out/styles.hpp"
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

inline void print_measuring_title(std::ostream &stream, const file_line_t &file_line, const char *title, const char *label);
inline void print_execution_time_in_milliseconds(std::ostream &stream, const file_line_t &file_line, const char *label, standard::uint64_t milliseconds);
inline void print_execution_time_in_clocks(std::ostream &stream, const file_line_t &file_line, const char *label, std::clock_t clocks, double milliseconds);
inline void print_execution_statistics(std::ostream &stream, const file_line_t &file_line, const char *label, std::vector<standard::uint64_t> &results, const char *units);

}

//
// Implementation

namespace trace_out
{

void print_measuring_title(std::ostream &stream, const file_line_t &file_line, const char *title, const char *label)
{
	stream << START_HEADER << THREAD_INFO << NEW_PARAGRAPH(file_line) << title << ' ' << styles::SUBJECT << '"' << label << '"' << styles::NORMAL << "..." << std::endl;
}

void print_execution_time_in_milliseconds(std::ostream &stream, const file_line_t &file_line, const char *label, standard::uint64_t milliseconds)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << START_HEADER << THREAD_INFO << NEW_PARAGRAPH(file_line) << styles::SUBJECT << '"' << label << '"' << styles::NORMAL << " timed in " << std::setbase(10) << styles::NUMBER << milliseconds << styles::NORMAL << " ms" << std::endl;
}

void print_execution_time_in_clocks(std::ostream &stream, const file_line_t &file_line, const char *label, std::clock_t clocks, double milliseconds)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << START_HEADER << THREAD_INFO << NEW_PARAGRAPH(file_line) << styles::SUBJECT << '"' << label << '"' << styles::NORMAL << " clocked in " << styles::NUMBER << clocks << styles::NORMAL << " clocks (" << styles::NUMBER << milliseconds << styles::NORMAL << " ms)" << std::endl;
}

void print_execution_statistics(std::ostream &stream, const file_line_t &file_line, const char *label, std::vector<standard::uint64_t> &results, const char *units)
{
	if (results.empty())
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		stream << START_HEADER << THREAD_INFO << NEW_PARAGRAPH(file_line) << styles::COMMENT << "// Execution time statistics for \"" << label << "\" is not available" << styles::NORMAL << std::endl;
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
		stream << START_HEADER << THREAD_INFO << NEW_PARAGRAPH(file_line) << styles::COMMENT << "// Execution time statistics (" << units << ") for " << styles::SUBJECT << '"' << label << '"' << styles::COMMENT << ':' << styles::NORMAL << "\n";
		stream << CONTINUE_PARAGRAPH << styles::COMMENT << "//   avg/med: " << styles::NUMBER << average << styles::COMMENT << " / " << styles::NUMBER << median << styles::NORMAL << '\n';
		if (modes.size() == 1)
		{
			stream << CONTINUE_PARAGRAPH << styles::COMMENT << "//      mode: " << styles::NUMBER << modes.front() << styles::COMMENT << " (" << styles::NUMBER << percentage << '%' << styles::COMMENT << " of all values)";
		}
		else if (modes.size() > 1)
		{
			stream << CONTINUE_PARAGRAPH << styles::COMMENT << "//     modes: ";
			std::vector<standard::uint64_t>::iterator itr = modes.begin();
			stream << *itr;
			for (++itr; itr != modes.end(); ++itr)
			{
				stream << ", " << styles::NUMBER << *itr << styles::COMMENT;
			}

			stream << " (each = " << styles::NUMBER << percentage << '%' << styles::COMMENT << ", all = " << styles::NUMBER << (percentage * static_cast<float>(modes.size())) << '%' << styles::COMMENT << " of all values)";
		}

		stream << styles::NORMAL << '\n';

		// range
		stream << CONTINUE_PARAGRAPH << styles::COMMENT << "//     range: " << styles::NUMBER << (results.back() - results.front()) << styles::COMMENT << " [" << styles::NUMBER << (results.front()) << styles::COMMENT << "..." << styles::NUMBER << (results.back()) << styles::COMMENT << ']' << styles::NORMAL << '\n' << BREAK_PARAGRAPH;
	}
}

}

