#pragma once

#include "trace-out/mutex.hpp"
#include "trace-out/pretty-lines.hpp"
#include "trace-out/pretty-print.hpp"
#include "trace-out/styles.hpp"
#include <ostream>

//
// Public

namespace trace_out
{

class return_printer
{
public:
	inline return_printer(std::ostream &stream, const file_line_t &file_line);

	template <typename T>
	const T &operator ,(const T &value);

private:
	std::ostream &_stream;
	file_line_t _file_line;
};

}

//
// Implementation

namespace trace_out
{

return_printer::return_printer(std::ostream &stream, const file_line_t &file_line)
	:
	_stream(stream),
	_file_line(file_line)
{
}

template <typename Type_t>
const Type_t &return_printer::operator ,(const Type_t &value)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << THREAD_INFO << NEW_PARAGRAPH(_file_line) << styles::KEYWORD << "return" << styles::NORMAL << ' ';
		pretty_print(_stream, value);
		_stream << std::endl;
	}

	return value;
}

}

