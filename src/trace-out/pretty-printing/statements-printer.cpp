#include "trace-out/pretty-printing/statements-printer.hpp"


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



	block iteration_block(const std::string &filename_line, const char *loop, standard::size_t iteration)
	{
		out_stream stream(filename_line);
		stream << "//" << NEWLINE << "// " << loop << ": iteration #" << make_pretty(iteration) << ENDLINE;

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
}

