#pragma once

#include "trace-out/out-stream.hpp"
#include "trace-out/strip-namespaces.hpp"
#include <string>

//
// Public

namespace trace_out
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

//
// Implementation

namespace trace_out
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
	return function_printer(filename_line, trace_out_private__strip_namespaces(function_signature));
}

}
