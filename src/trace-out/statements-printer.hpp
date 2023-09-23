#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/out-stream.hpp"
#include "trace-out/platform-detection.hpp"
#include "trace-out/pretty.hpp"
#include <string>

//
// Public

namespace trace_out
{

class auto_indentation
{
public:
	inline auto_indentation();
	inline ~auto_indentation();
};

class block
{
public:
	inline block(bool value);
	inline block(const block &another);
	inline ~block();

	inline operator bool() const;

private:
	inline block &operator =(const block &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L

	inline block &operator =(block &&another); // = delete

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	bool _value;
};

class if_block
{
public:
	inline if_block(bool value);
	inline if_block(const if_block &another);
	inline ~if_block();

	inline operator bool() const;

private:
	inline if_block &operator =(const if_block &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L

	inline if_block &operator =(if_block &&another); // = delete

#endif

private:
	bool _value;
};

template <typename Type_t>
if_block make_if_block(const std::string &filename_line, const char *condition, const Type_t &value);

inline block iteration_block(const std::string &filename_line, const char *loop, standard::size_t iteration);

class loop_block
{
public:
	inline loop_block(const std::string &filename_line, const char *expression);
	inline ~loop_block();

	inline operator bool() const;
	inline standard::size_t iteration();

private:
	const char *_expression;
	standard::size_t _iteration_number;
};

inline loop_block make_loop_block(const std::string &filename_line, const char *expression);

}

//
// Implementation

namespace trace_out
{

auto_indentation::auto_indentation()
{
	indentation_add();
}

auto_indentation::~auto_indentation()
{
	indentation_remove();
}

block::block(bool value)
	:
	_value(value)
{
}

block::block(const block &another)
	:
	_value(another._value)
{
}

block::~block()
{
	out_stream stream;
	stream << ENDLINE;
}

block::operator bool() const
{
	return _value;
}

if_block::if_block(bool value)
	:
	_value(value)
{
	out_stream() << "{" << ENDLINE;
	indentation_add();
}

if_block::if_block(const if_block &another)
	:
	_value(another._value)
{
	out_stream() << "{" << ENDLINE;
	indentation_add();
}

if_block::~if_block()
{
	indentation_remove();
	out_stream() << "}" << NEWLINE << ENDLINE;
}

if_block::operator bool() const
{
	return _value;
}

template <typename Type_t>
if_block make_if_block(const std::string &filename_line, const char *condition, const Type_t &value)
{
	{
		out_stream stream(filename_line);
		stream << "if (" << condition << ") => " << FLUSH;
		stream << make_pretty_condition(value) << ENDLINE;
	}

	return if_block(!!value);
}

block iteration_block(const std::string &filename_line, const char *loop, standard::size_t iteration)
{
	out_stream stream(filename_line);
	stream << "// " << loop << ": iteration #" << make_pretty(iteration) << ENDLINE;

	return block(false);
}

loop_block::loop_block(const std::string &filename_line, const char *expression)
	:
	_expression(expression),
	_iteration_number(0)
{
	out_stream stream(filename_line);
	stream << _expression << NEWLINE << "{" << ENDLINE;
	indentation_add();
}

loop_block::~loop_block()
{
	indentation_remove();
	out_stream() << "} // " << _expression << NEWLINE << ENDLINE;
}

loop_block::operator bool() const
{
	return false;
}

standard::size_t loop_block::iteration()
{
	return ++_iteration_number;
}

loop_block make_loop_block(const std::string &filename_line, const char *expression)
{
	return loop_block(filename_line, expression);
}

}

