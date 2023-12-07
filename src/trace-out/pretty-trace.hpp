#pragma once

#include "trace-out/mutex.hpp"
#include "trace-out/pretty-lines.hpp"
#include "trace-out/pretty-print.hpp"
#include <string>

#if TRACE_OUT_CPP_VERSION >= 201103L
	#include <utility> // [amalgamate:leave]
#endif

//
// Public

namespace trace_out
{

#if TRACE_OUT_CPP_VERSION >= 201103L

template <typename Type_t>
inline Type_t &&trace(std::ostream &stream, const file_line_t &file_line, const char *name, Type_t &&value);

template <typename ...Types_t>
inline void trace(std::ostream &stream, const file_line_t &file_line, const char *names, const Types_t &...values);

template <typename ...Types_t>
inline void trace_binary(std::ostream &stream, const file_line_t &file_line, const char *names, Types_t ...values);

template <typename ...Types_t>
inline void trace_octal(std::ostream &stream, const file_line_t &file_line, const char *names, Types_t ...values);

template <typename ...Types_t>
inline void trace_hexadecimal(std::ostream &stream, const file_line_t &file_line, const char *names, Types_t ...values);

#else

template <typename Type_t>
inline const Type_t &trace(std::ostream &stream, const file_line_t &file_line, const char *name, const Type_t &value);

template <typename Type_t>
inline Type_t &trace(std::ostream &stream, const file_line_t &file_line, const char *name, Type_t &value);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

template <standard::size_t Size>
inline void trace(std::ostream &stream, const file_line_t &file_line, const char *should_comment, const char (&comment)[Size]);

template <typename Type_t>
inline const Type_t &trace_binary(std::ostream &stream, const file_line_t &file_line, const char *name, const Type_t &value);

template <typename Type_t>
inline Type_t &trace_binary(std::ostream &stream, const file_line_t &file_line, const char *name, Type_t &value);

template <typename Type_t>
inline const Type_t &trace_octal(std::ostream &stream, const file_line_t &file_line, const char *name, const Type_t &value);

template <typename Type_t>
inline Type_t &trace_octal(std::ostream &stream, const file_line_t &file_line, const char *name, Type_t &value);

template <typename Type_t>
inline const Type_t &trace_hexadecimal(std::ostream &stream, const file_line_t &file_line, const char *name, const Type_t &value);

template <typename Type_t>
inline Type_t &trace_hexadecimal(std::ostream &stream, const file_line_t &file_line, const char *name, Type_t &value);

template <typename Begin_t, typename End_t>
inline void trace_range(std::ostream &stream, const file_line_t &file_line, const char *begin_name, const char *end_name, Begin_t begin, End_t end);

template <typename Begin_t>
inline void trace_range(std::ostream &stream, const file_line_t &file_line, const char *begin_name, const char *how_much_name, Begin_t begin, standard::size_t how_much);

}

//
// Private

namespace trace_out
{

inline std::string first_token(const std::string &tokens);
inline std::string rest_tokens(const std::string &tokens);

#if TRACE_OUT_CPP_VERSION >= 201103L

inline void print_next_value(std::ostream &stream, const std::string &);

template <typename First_t, typename ...Rest_t>
inline void print_next_value(std::ostream &stream, const std::string &names, const First_t &first, const Rest_t &...rest);

template <typename First_t, typename ...Rest_t>
inline void print_first_value(std::ostream &stream, const file_line_t &file_line, const std::string &names, const First_t &first, const Rest_t &...rest);

inline void print_next_binary_value(std::ostream &stream, const std::string &);

template <typename First_t, typename ...Rest_t>
inline void print_next_binary_value(std::ostream &stream, const std::string &names, const First_t &first, const Rest_t &...rest);

template <typename First_t, typename ...Rest_t>
inline void print_first_binary_value(std::ostream &stream, const file_line_t &file_line, const std::string &names, const First_t &first, const Rest_t &...rest);

inline void print_next_octal_value(std::ostream &stream, const std::string &);

template <typename First_t, typename ...Rest_t>
inline void print_next_octal_value(std::ostream &stream, const std::string &names, const First_t &first, const Rest_t &...rest);

template <typename First_t, typename ...Rest_t>
inline void print_first_octal_value(std::ostream &stream, const file_line_t &file_line, const std::string &names, const First_t &first, const Rest_t &...rest);

inline void print_next_hexadecimal_value(std::ostream &stream, const std::string &);

template <typename First_t, typename ...Rest_t>
inline void print_next_hexadecimal_value(std::ostream &stream, const std::string &names, const First_t &first, const Rest_t &...rest);

template <typename First_t, typename ...Rest_t>
inline void print_first_hexadecimal_value(std::ostream &stream, const file_line_t &file_line, const std::string &names, const First_t &first, const Rest_t &...rest);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

}

//
// Implementation

namespace trace_out
{

#if TRACE_OUT_CPP_VERSION >= 201103L

template <typename Type_t>
Type_t &&trace(std::ostream &stream, const file_line_t &file_line, const char *name, Type_t &&value)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << name << " = ";
		pretty_print(stream, value);
		stream << std::endl;
	}

	return std::forward<Type_t>(value);
}

template <typename ...Types_t>
void trace(std::ostream &stream, const file_line_t &file_line, const char *names, const Types_t &...values)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO;
	print_first_value(stream, file_line, names, values...);
}

template <typename ...Types_t>
void trace_binary(std::ostream &stream, const file_line_t &file_line, const char *names, Types_t ...values)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO;
	print_first_binary_value(stream, file_line, names, values...);
}

template <typename ...Types_t>
void trace_octal(std::ostream &stream, const file_line_t &file_line, const char *names, Types_t ...values)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO;
	print_first_octal_value(stream, file_line, names, values...);
}

template <typename ...Types_t>
void trace_hexadecimal(std::ostream &stream, const file_line_t &file_line, const char *names, Types_t ...values)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO;
	print_first_hexadecimal_value(stream, file_line, names, values...);
}

void print_next_value(std::ostream &stream, const std::string &)
{
	stream << SEPARATE_PARAGRAPH << std::endl;
}

template <typename First_t, typename ...Rest_t>
void print_next_value(std::ostream &stream, const std::string &names, const First_t &first, const Rest_t &...rest)
{
	stream << CONTINUE_PARAGRAPH << first_token(names) << " = ";
	pretty_print(stream, first);
	stream << std::endl;
	print_next_value(stream, rest_tokens(names), rest...);
}

template <typename First_t, typename ...Rest_t>
void print_first_value(std::ostream &stream, const file_line_t &file_line, const std::string &names, const First_t &first, const Rest_t &...rest)
{
	stream << NEW_PARAGRAPH(file_line) << first_token(names) << " = ";
	pretty_print(stream, first);
	stream << std::endl;
	print_next_value(stream, rest_tokens(names), rest...);
}

void print_next_binary_value(std::ostream &stream, const std::string &)
{
	stream << SEPARATE_PARAGRAPH << std::endl;
}

template <typename First_t, typename ...Rest_t>
void print_next_binary_value(std::ostream &stream, const std::string &names, const First_t &first, const Rest_t &...rest)
{
	stream << CONTINUE_PARAGRAPH << first_token(names) << " = ";
	pretty_print_binary(stream, first);
	stream << std::endl;
	print_next_binary_value(stream, rest_tokens(names), rest...);
}

template <typename First_t, typename ...Rest_t>
void print_first_binary_value(std::ostream &stream, const file_line_t &file_line, const std::string &names, const First_t &first, const Rest_t &...rest)
{
	stream << NEW_PARAGRAPH(file_line) << first_token(names) << " = ";
	pretty_print_binary(stream, first);
	stream << std::endl;
	print_next_binary_value(stream, rest_tokens(names), rest...);
}

void print_next_octal_value(std::ostream &stream, const std::string &)
{
	stream << SEPARATE_PARAGRAPH << std::endl;
}

template <typename First_t, typename ...Rest_t>
void print_next_octal_value(std::ostream &stream, const std::string &names, const First_t &first, const Rest_t &...rest)
{
	stream << CONTINUE_PARAGRAPH << first_token(names) << " = ";
	pretty_print_octal(stream, first);
	stream << std::endl;
	print_next_octal_value(stream, rest_tokens(names), rest...);
}

template <typename First_t, typename ...Rest_t>
void print_first_octal_value(std::ostream &stream, const file_line_t &file_line, const std::string &names, const First_t &first, const Rest_t &...rest)
{
	stream << NEW_PARAGRAPH(file_line) << first_token(names) << " = ";
	pretty_print_octal(stream, first);
	stream << std::endl;
	print_next_octal_value(stream, rest_tokens(names), rest...);
}

void print_next_hexadecimal_value(std::ostream &stream, const std::string &)
{
	stream << SEPARATE_PARAGRAPH << std::endl;
}

template <typename First_t, typename ...Rest_t>
void print_next_hexadecimal_value(std::ostream &stream, const std::string &names, const First_t &first, const Rest_t &...rest)
{
	stream << CONTINUE_PARAGRAPH << first_token(names) << " = ";
	pretty_print_hexadecimal(stream, first);
	stream << std::endl;
	print_next_hexadecimal_value(stream, rest_tokens(names), rest...);
}

template <typename First_t, typename ...Rest_t>
void print_first_hexadecimal_value(std::ostream &stream, const file_line_t &file_line, const std::string &names, const First_t &first, const Rest_t &...rest)
{
	stream << NEW_PARAGRAPH(file_line) << first_token(names) << " = ";
	pretty_print_hexadecimal(stream, first);
	stream << std::endl;
	print_next_hexadecimal_value(stream, rest_tokens(names), rest...);
}

#else // TRACE_OUT_CPP_VERSION >= 201103L

template <typename Type_t>
const Type_t &trace(std::ostream &stream, const file_line_t &file_line, const char *name, const Type_t &value)
{
	return trace(stream, file_line, name, const_cast<Type_t &>(value));
}

template <typename Type_t>
Type_t &trace(std::ostream &stream, const file_line_t &file_line, const char *name, Type_t &value)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << name << " = ";
		pretty_print(stream, value);
		stream << std::endl;
	}

	return value;
}

#endif

template <standard::size_t Size>
void trace(std::ostream &stream, const file_line_t &file_line, const char *should_comment, const char (&comment)[Size])
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << (should_comment != NULL ? "// " : "") << comment << std::endl;
}

template <typename Type_t>
const Type_t &trace_binary(std::ostream &stream, const file_line_t &file_line, const char *name, const Type_t &value)
{
	return trace_binary(stream, file_line, name, const_cast<Type_t &>(value));
}

template <typename Type_t>
Type_t &trace_binary(std::ostream &stream, const file_line_t &file_line, const char *name, Type_t &value)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << name << " = ";
		pretty_print_binary(stream, value);
		stream << std::endl;
	}

	return value;
}

template <typename Type_t>
const Type_t &trace_octal(std::ostream &stream, const file_line_t &file_line, const char *name, const Type_t &value)
{
	return trace_octal(stream, file_line, name, const_cast<Type_t &>(value));
}

template <typename Type_t>
Type_t &trace_octal(std::ostream &stream, const file_line_t &file_line, const char *name, Type_t &value)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << name << " = ";
		pretty_print_octal(stream, value);
		stream << std::endl;
	}

	return value;
}

template <typename Type_t>
const Type_t &trace_hexadecimal(std::ostream &stream, const file_line_t &file_line, const char *name, const Type_t &value)
{
	return trace_hexadecimal(stream, file_line, name, const_cast<Type_t &>(value));
}

template <typename Type_t>
Type_t &trace_hexadecimal(std::ostream &stream, const file_line_t &file_line, const char *name, Type_t &value)
{
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << name << " = ";
		pretty_print_hexadecimal(stream, value);
		stream << std::endl;
	}

	return value;
}

template <typename Begin_t, typename End_t>
void trace_range(std::ostream &stream, const file_line_t &file_line, const char *begin_name, const char *end_name, Begin_t begin, End_t end)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << '[' << begin_name << ", " << end_name << ") = ";
	pretty_print_begin_end(stream, begin, end);
	stream << std::endl;
}

template <typename Begin_t>
void trace_range(std::ostream &stream, const file_line_t &file_line, const char *begin_name, const char *how_much_name, Begin_t begin, standard::size_t how_much)
{
#if defined(TRACE_OUT_SYNC_STREAM)
	autolock<system::mutex> lock(stream_mutex());
#endif

	stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << '[' << begin_name << ": " << how_much_name << "] = ";
	pretty_print_begin_how_much(stream, begin, how_much);
	stream << std::endl;
}

std::string first_token(const std::string &tokens)
{
	return tokens.substr(0, tokens.find(','));
}

std::string rest_tokens(const std::string &tokens)
{
	standard::size_t from = tokens.find(',') + 1;
	while (tokens[from] == ' ')
	{
		++from;
	}

	return tokens.substr(from, tokens.size());
}

}

