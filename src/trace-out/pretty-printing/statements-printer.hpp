#pragma once

#include <string>

#include "trace-out/standard/integer.hpp"
#include "trace-out/stuff/platform-detection.hpp"
#include "trace-out/pretty-printing/pretty.hpp"
#include "trace-out/pretty-printing/out-stream.hpp"


namespace trace_out { namespace detail
{

	class auto_indentation
	{
	public:
		auto_indentation();
		~auto_indentation();
	};


	class block
	{
	public:
		block(bool value);
		block(const block &another);
		~block();

		operator bool() const;

	private:
		block &operator =(const block &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L

		block &operator =(block &&another); // = delete

#endif // TRACE_OUT_CPP_VERSION >= 201103L

		bool _value;
	};


	class if_block
	{
	public:
		if_block(bool value);
		if_block(const if_block &another);
		~if_block();

		operator bool() const;

	private:
		if_block &operator =(const if_block &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L

		if_block &operator =(if_block &&another); // = delete

#endif

	private:
		bool _value;
	};


	template <typename Type_t>
	if_block make_if_block(const std::string &filename_line, const char *condition, const Type_t &value);

	block iteration_block(const std::string &filename_line, const char *loop, standard::size_t iteration);



	class loop_block
	{
	public:
		loop_block(const std::string &filename_line, const char *expression);
		~loop_block();

		operator bool() const;
		standard::size_t iteration();

	private:
		const char *_expression;
		standard::size_t _iteration_number;
	};


	loop_block make_loop_block(const std::string &filename_line, const char *expression);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	if_block make_if_block(const std::string &filename_line, const char *condition, const Type_t &value)
	{
		out_stream stream(filename_line);
		stream << "if (" << condition << ") => " << FLUSH;
		stream << make_pretty_condition(value) << ENDLINE;

		return if_block(!!value);
	}

}
}
