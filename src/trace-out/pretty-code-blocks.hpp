#pragma once

#include "trace-out/indentation.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/mutex.hpp"
#include "trace-out/platform-detection.hpp"
#include "trace-out/pretty-lines.hpp"
#include "trace-out/pretty-print.hpp"
#include "trace-out/styles.hpp"
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
	if_block(std::ostream &stream, const file_line_t &file_line, const char *condition, const Type_t &value);

	inline if_block(std::ostream &stream, const file_line_t &file_line, const char *condition, bool value);
	inline ~if_block();

	inline operator bool() const;

private:
	std::ostream &_stream;
	const char *_condition;
	bool _value;
};

class loop_block
{
public:
	inline loop_block(std::ostream &stream, const file_line_t &file_line, const char *loop, const char *statement);
	inline ~loop_block();

	inline operator bool() const;
	inline standard::size_t iteration();

private:
	std::ostream &_stream;
	const char *_loop;
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

	_stream << START_HEADER << THREAD_INFO << NEW_PARAGRAPH(file_line) << styles::COMMENT << "// " << styles::COMMENT_BOLD << loop << styles::COMMENT << ": iteration #" << iteration << styles::NORMAL << std::endl;
}

iteration_block::~iteration_block()
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	_stream << START_HEADER << THREAD_INFO << BREAK_PARAGRAPH;
}

iteration_block::operator bool() const
{
	return false;
}

template <typename Type_t>
if_block::if_block(std::ostream &stream, const file_line_t &file_line, const char *condition, const Type_t &value)
	:
	_stream(stream),
	_condition(condition),
	_value(value)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << START_HEADER << THREAD_INFO << NEW_PARAGRAPH(file_line) << styles::KEYWORD << "if" << styles::NORMAL << " (" << styles::SUBJECT << condition << styles::NORMAL << ") => " << styles::BOOLEAN << std::boolalpha << !!(_value) << styles::NORMAL << " (";
		pretty_print(stream, value);
		_stream << ")\n" << CONTINUE_PARAGRAPH << '{' << std::endl;
	}

	indentation_add();
}

if_block::if_block(std::ostream &stream, const file_line_t &file_line, const char *condition, bool value)
	:
	_stream(stream),
	_condition(condition),
	_value(value)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << START_HEADER << THREAD_INFO << NEW_PARAGRAPH(file_line) << styles::KEYWORD << "if" << styles::NORMAL << " (" << styles::SUBJECT << condition << styles::NORMAL << ") => " << styles::BOOLEAN << std::boolalpha << _value << styles::NORMAL << '\n' << CONTINUE_PARAGRAPH << '{' << std::endl;
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

		_stream << CONTINUE_PARAGRAPH << "} " << styles::COMMENT << "// " << styles::COMMENT_BOLD << "if" << styles::COMMENT << " (" << _condition << ") => " << std::boolalpha << _value << styles::NORMAL << '\n' << BREAK_PARAGRAPH;
	}
}

if_block::operator bool() const
{
	return _value;
}

loop_block::loop_block(std::ostream &stream, const file_line_t &file_line, const char *loop, const char *statement)
	:
	_stream(stream),
	_loop(loop),
	_statement(statement),
	_iteration_number(0)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		_stream << START_HEADER << THREAD_INFO << NEW_PARAGRAPH(file_line) << styles::KEYWORD << _loop << styles::NORMAL << " (" << styles::SUBJECT << _statement << styles::NORMAL << ")\n" << CONTINUE_PARAGRAPH << '{' << std::endl;
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

		_stream << START_HEADER << THREAD_INFO << CONTINUE_PARAGRAPH << "} " << styles::COMMENT << "// " << styles::COMMENT_BOLD << _loop << styles::COMMENT << " (" << _statement << ')' << styles::NORMAL << '\n' << BREAK_PARAGRAPH;
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

