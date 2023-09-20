#pragma once

#include "trace-out/pretty-printing/out-stream.hpp"
#include <string>


namespace trace_out { namespace detail
{

	class function_printer
	{
	public:
		inline function_printer(const std::string &filename_line, const std::string &function_signature);
		inline ~function_printer();

	private:
		std::string _filename_line;
		std::string _function_signature;
	};


	inline function_printer make_function_printer(const std::string &filename_line, const std::string &function_signature);

}
}


namespace trace_out { namespace detail
{

	function_printer::function_printer(const std::string &filename_line, const std::string &function_signature)
		:
		_filename_line(filename_line),
		_function_signature(function_signature)
	{
		out_stream stream(_filename_line);
		stream << _function_signature << NEWLINE << "{" << ENDLINE;
		indentation_add();
	}


	function_printer::~function_printer()
	{
		indentation_remove();
		out_stream stream(_filename_line);
		stream << "} // " << _function_signature << NEWLINE << ENDLINE;
	}


	function_printer make_function_printer(const std::string &filename_line, const std::string &function_signature)
	{
		return function_printer(filename_line, function_signature);
	}

}
}
