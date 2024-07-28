#pragma once

#include "trace-out/mutex.hpp"
#include "trace-out/pretty-lines.hpp"
#include "trace-out/styles.hpp"
#include <string>

//
// Public

namespace trace_out
{

class function_printer
{
public:
	inline function_printer(std::ostream &stream, const file_line_t &file_line, const std::string &signature);
	inline ~function_printer();

private:
	std::ostream &_stream;
	file_line_t _file_line;
	std::string _signature;
};

}

//
// Implementation

namespace trace_out
{

function_printer::function_printer(std::ostream &stream, const file_line_t &file_line, const std::string &signature)
	:
	_stream(stream),
	_file_line(file_line),
	_signature(signature)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << THREAD_INFO << NEW_PARAGRAPH(_file_line) << styles::FUNCTION << _signature << styles::NORMAL << '\n' << CONTINUE_PARAGRAPH << styles::PUNCTUATION << '{' << styles::NORMAL << std::endl;
	}

	indentation_add();
}

function_printer::~function_printer()
{
	indentation_remove();

	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << THREAD_INFO << NEW_PARAGRAPH(_file_line) << styles::PUNCTUATION << '}' << styles::NORMAL << ' ' << styles::COMMENT << "// " << _signature << styles::NORMAL << '\n' << SEPARATE_PARAGRAPH << std::endl;
	}
}

}
