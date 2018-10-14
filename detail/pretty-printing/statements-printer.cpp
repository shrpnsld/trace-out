#include "trace-out/detail/pretty-printing/statements-printer.hpp"


namespace trace_out { namespace detail
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
		_auto_indentation(),
		_value(value)
	{
	}


	block::block(const block &another)
		:
		_auto_indentation(),
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


	block iteration_block(const std::string &filename_line, standard::size_t iteration)
	{
		{
			auto_indentation auto_indentation;

			out_stream stream(filename_line);
			stream << "// for: iteration #" << make_pretty(iteration) << ENDLINE;
		}

		return block(false);
	}



	for_block::for_block(const std::string &filename_line, const char *expression)
		:
		_iteration_number(0)
	{
		out_stream stream(filename_line);
		stream << "for (" << expression << ")" << ENDLINE;
	}


	for_block::~for_block()
	{
	}


	for_block::operator bool() const
	{
		return false;
	}


	standard::size_t for_block::iteration()
	{
		return ++_iteration_number;
	}


	for_block make_for_block(const std::string &filename_line, const char *expression)
	{
		return for_block(filename_line, expression);
	}



	void print_while_header(const std::string &filename_line, const char *condition)
	{
		out_stream stream(filename_line);
		stream << "while (" << condition << ")" << ENDLINE;
	}

}
}