#pragma once

#include "trace-out/pretty-lines.hpp"
#include "trace-out/pretty-values.hpp"
#include <string>

//
// Public

namespace trace_out
{

template <typename Iterator_t>
void range(std::ostream &stream, const file_line_t &file_line, const char *begin_name, const char *end_name, const Iterator_t &begin, const Iterator_t &end);

template <typename Iterator_t>
void range(std::ostream &stream, const file_line_t &file_line, const char *begin_name, const char *how_much_name, const Iterator_t &begin, std::size_t how_much);

}

//
// Implementation

namespace trace_out
{

template <typename Iterator_t>
void range(std::ostream &stream, const file_line_t &file_line, const char *begin_name, const char *end_name, const Iterator_t &begin, const Iterator_t &end)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << '[' << begin_name << ", " << end_name << ") = ";
	pretty_print_begin_end(stream, begin, end);
	stream << std::endl;
}

template <typename Iterator_t>
void range(std::ostream &stream, const file_line_t &file_line, const char *begin_name, const char *how_much_name, const Iterator_t &begin, std::size_t how_much)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << '[' << begin_name << ": " << how_much_name << "] = ";
	pretty_print_begin_how_much(stream, begin, how_much);
	stream << std::endl;
}

}

