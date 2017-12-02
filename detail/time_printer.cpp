#include "stuff.hpp"
#include "out_stream.hpp"

#include "time_printer.hpp"


namespace trace_out { namespace detail
{

	void print_execution_time_in_milliseconds(const std::string &filename_line, const char *label, standard::uint64_t milliseconds)
	{
		out_stream stream(filename_line);
		stream << "// execution time \"" << label << "\" : " << to_string(milliseconds) << " ms" << ENDLINE;
	}


	void print_execution_time_in_clocks(const std::string &filename_line, const char *label, std::clock_t clocks, double milliseconds)
	{
		out_stream stream(filename_line);
		stream << "// execution time \"" << label << "\" : " << to_string(clocks) << " clocks (" << to_string(milliseconds) << " ms)" << ENDLINE;
	}

}
}

