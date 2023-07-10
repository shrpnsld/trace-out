#pragma once

#include <string>

#include "trace-out/pretty-printing/pretty.hpp"
#include "trace-out/pretty-printing/out-stream.hpp"


namespace trace_out { namespace detail
{

	template <typename Iterator_t>
	void range(const std::string &filename_line, const char *begin_name, const char *end_name, const Iterator_t &begin, const Iterator_t &end);

	template <typename Iterator_t>
	void range(const std::string &filename_line, const char *begin_name, const char *how_much_name, const Iterator_t &begin, std::size_t how_much);

}
}


namespace trace_out { namespace detail
{

	template <typename Iterator_t>
	void range(const std::string &filename_line, const char *begin_name, const char *end_name, const Iterator_t &begin, const Iterator_t &end)
	{
		out_stream stream(filename_line);
		stream << "[" << begin_name << ", " << end_name << ") = " << pretty_range_closed<Iterator_t>(begin, end) << ENDLINE;
	}


	template <typename Iterator_t>
	void range(const std::string &filename_line, const char *begin_name, const char *how_much_name, const Iterator_t &begin, std::size_t how_much)
	{
		out_stream stream(filename_line);
		stream << "[" << begin_name << ": " << how_much_name << "] = " << pretty_range_open<Iterator_t>(begin, how_much) << ENDLINE;
	}

}
}
