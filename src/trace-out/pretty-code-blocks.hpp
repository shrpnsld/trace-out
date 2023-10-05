#pragma once

#include "trace-out/indentation.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/mutex.hpp"
#include "trace-out/platform-detection.hpp"
#include "trace-out/pretty-lines.hpp"
#include "trace-out/pretty-print.hpp"
#include <iomanip>
#include <ostream>

//
// Public

namespace trace_out
{

class iteration_block
{
public:
	inline iteration_block(std::ostream &stream, const file_line_t &file_line, const char *loop, standard::size_t iteration);
	inline ~iteration_block();

	inline operator bool() const;

private:
	std::ostream &_stream;
};

class if_block
{
public:
	template <typename Type_t>
	inline if_block(std::ostream &stream, const file_line_t &file_line, const char *condition, const Type_t &value);

	inline if_block(std::ostream &stream, const file_line_t &file_line, const char *condition, bool value);
	inline ~if_block();

	inline operator bool() const;

private:
	std::ostream &_stream;
	bool _value;
};

class loop_block
{
public:
	inline loop_block(std::ostream &stream, const file_line_t &file_line, const char *statement);
	inline ~loop_block();

	inline operator bool() const;
	inline standard::size_t iteration();

private:
	std::ostream &_stream;
	const char *_statement;
	standard::size_t _iteration_number;
};

}

//
// Implementation

namespace trace_out
{

iteration_block::iteration_block(std::ostream &stream, const file_line_t &file_line, const char *loop, standard::size_t iteration)
	:
	_stream(stream)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	_stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << "// " << loop << ": iteration #" << iteration << std::endl;
}

iteration_block::~iteration_block()
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	_stream << THREAD_INFO << SEPARATE_PARAGRAPH << std::endl;
}

iteration_block::operator bool() const
{
	return false;
}

template <typename Type_t>
if_block::if_block(std::ostream &stream, const file_line_t &file_line, const char *condition, const Type_t &value)
	:
	_stream(stream),
	_value(value)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << "if (" << condition << ") => " << std::boolalpha << !!(value) << " (";
		pretty_print(stream, value);
		_stream << ")\n" << CONTINUE_PARAGRAPH << '{' << std::endl;
	}

	indentation_add();
}

if_block::if_block(std::ostream &stream, const file_line_t &file_line, const char *condition, bool value)
	:
	_stream(stream),
	_value(value)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << "if (" << condition << ") => " << std::boolalpha << value << '\n' << CONTINUE_PARAGRAPH << '{' << std::endl;
	}

	indentation_add();
}

if_block::~if_block()
{
	indentation_remove();

	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << CONTINUE_PARAGRAPH << "}\n" << SEPARATE_PARAGRAPH << std::endl;
	}
}

if_block::operator bool() const
{
	return _value;
}

loop_block::loop_block(std::ostream &stream, const file_line_t &file_line, const char *statement)
	:
	_stream(stream),
	_statement(statement),
	_iteration_number(0)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << statement << '\n' << CONTINUE_PARAGRAPH << '{' << std::endl;
	}

	indentation_add();
}

loop_block::~loop_block()
{
	indentation_remove();

	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << THREAD_INFO << CONTINUE_PARAGRAPH << "} // " << _statement << '\n' << SEPARATE_PARAGRAPH << std::endl;
	}
}

loop_block::operator bool() const
{
	return false;
}

standard::size_t loop_block::iteration()
{
	return ++_iteration_number;
}

}

