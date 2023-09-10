#pragma once

#include <string>

#include "trace-out/stuff/platform-detection.hpp"
#include "trace-out/stuff/stuff.hpp"
#include "trace-out/pretty-printing/pretty.hpp"
#include "trace-out/pretty-printing/out-stream.hpp"


namespace trace_out { namespace detail
{

#if TRACE_OUT_CPP_VERSION < 201103L

	template <typename Type_t>
	const Type_t &expression(const std::string &filename_line, const char *name, const Type_t &value);

	template <typename Type_t>
	Type_t &expression(const std::string &filename_line, const char *name, Type_t &value);

	template <typename Type_t>
	void watch(const std::string &filename_line, const char *name, const Type_t &value);

#else

	template <typename Type_t>
	Type_t &&expression(const std::string &filename_line, const char *name, Type_t &&value);

	template <typename ...Types_t>
	void watch(const std::string &filename_line, const char *names, const Types_t &...values);

#endif // TRACE_OUT_CPP_VERSION < 201103L

}
}


namespace trace_out { namespace detail
{

#if TRACE_OUT_CPP_VERSION < 201103L

	template <typename Type_t>
	const Type_t &expression(const std::string &filename_line, const char *name, const Type_t &value)
	{
		out_stream stream(filename_line);
		stream << name << " = " << make_pretty(value) << ENDLINE;
		return value;
	}


	template <typename Type_t>
	Type_t &expression(const std::string &filename_line, const char *name, Type_t &value)
	{
		out_stream stream(filename_line);
		stream << name << " = " << make_pretty(value) << ENDLINE;
		return value;
	}


	template <typename Type_t>
	void watch(const std::string &filename_line, const char *name, const Type_t &value)
	{
		out_stream stream(filename_line);
		stream << name << " = " << make_pretty(value) << ENDLINE;
	}

#else

	template <typename Type_t>
	Type_t &&expression(const std::string &filename_line, const char *name, Type_t &&value)
	{
		out_stream stream(filename_line);
		stream << name << " = " << make_pretty(value) << ENDLINE;
		return std::forward<Type_t>(value);
	}


	template <typename Type_t>
	void print_values(out_stream &stream, const std::string &name, const Type_t &value)
	{
		stream << name << " = " << make_pretty(value) << ENDLINE;
	}


	template <typename FirstType_t, typename ...RestTypes_t>
	void print_values(out_stream &stream, const std::string &names, const FirstType_t &first_value, const RestTypes_t &...rest_values)
	{
		stream << first_token(names) << " = " << make_pretty(first_value) << NEWLINE;
		print_values(stream, rest_tokens(names), rest_values...);
	}

	template <typename ...Types_t>
	void watch(const std::string &filename_line, const char *names, const Types_t &...values)
	{
		out_stream stream(filename_line);
		print_values(stream, names, values...);
		if (sizeof...(values) > 1)
		{
			out_stream() << ENDLINE;
		}
	}

#endif // TRACE_OUT_CPP_VERSION < 201103L

}
}