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

#if defined(TRACE_OUT_STYLE) && TRACE_OUT_STYLE > 0
	inline function_printer(std::ostream &stream, const file_line_t &file_line, const std::string &name, const std::string &signature);
#else
	inline function_printer(std::ostream &stream, const file_line_t &file_line, const std::string &signature);
#endif

	inline ~function_printer();

private:
	std::ostream &_stream;
	file_line_t _file_line;
	std::string _signature;

#if defined(TRACE_OUT_STYLE) && TRACE_OUT_STYLE > 0
	std::string::iterator _name_start;
	std::string::iterator _name_end;
#endif
};

}

//
// Implementation

namespace trace_out
{

#if defined(TRACE_OUT_STYLE) && TRACE_OUT_STYLE > 0
function_printer::function_printer(std::ostream &stream, const file_line_t &file_line, const std::string &name, const std::string &signature)
#else
function_printer::function_printer(std::ostream &stream, const file_line_t &file_line, const std::string &signature)
#endif
	:
	_stream(stream),
	_file_line(file_line),
	_signature(signature)
#if defined(TRACE_OUT_STYLE) && TRACE_OUT_STYLE > 0
	,
	_name_start(_signature.begin() + _signature.find(name + '(')),
	_name_end(_name_start + name.size())
#endif
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

#if defined(TRACE_OUT_STYLE) && TRACE_OUT_STYLE > 0
		std::ostream_iterator<char> stream_itr(_stream);

		_stream << THREAD_INFO << NEW_PARAGRAPH(_file_line);
		std::copy(_signature.begin(), _name_start, stream_itr);
		_stream << styles::FUNCTION;
		std::copy(_name_start, _name_end, stream_itr);
		_stream << styles::NORMAL;
		std::copy(_name_end, _signature.end(), stream_itr);
		_stream << '\n' << CONTINUE_PARAGRAPH << '{' << std::endl;
#else
		_stream << THREAD_INFO << NEW_PARAGRAPH(_file_line) << styles::FUNCTION << _signature << styles::NORMAL << '\n' << CONTINUE_PARAGRAPH << '{' << std::endl;
#endif
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

#if defined(TRACE_OUT_STYLE) && TRACE_OUT_STYLE > 0
		std::ostream_iterator<char> stream_itr(_stream);

		_stream << THREAD_INFO << NEW_PARAGRAPH(_file_line) << '}' << ' ' << styles::COMMENT << "// ";
		std::copy(_signature.begin(), _name_start, stream_itr);
		_stream << styles::COMMENT_BOLD;
		std::copy(_name_start, _name_end, stream_itr);
		_stream << styles::COMMENT;
		std::copy(_name_end, _signature.end(), stream_itr);
		_stream << styles::NORMAL << '\n' << BREAK_PARAGRAPH;
#else
		_stream << THREAD_INFO << NEW_PARAGRAPH(_file_line) << '}' << ' ' << styles::COMMENT << "// " << _signature << styles::NORMAL << '\n' << BREAK_PARAGRAPH;
#endif
	}
}

}
