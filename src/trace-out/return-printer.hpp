#pragma once

#include "trace-out/out-stream.hpp"
#include <string>

//
// Public

namespace trace_out
{

class return_printer
{
public:
	inline return_printer(const std::string &filename_line);

	template <typename T>
	const T &operator ,(const T &value);

private:
	std::string _filename_line;
};

inline return_printer make_return_printer(const std::string &filename_line);

}

//
// Implementation

namespace trace_out
{

return_printer::return_printer(const std::string &filename_line)
	:
	_filename_line(filename_line)
{
}

return_printer make_return_printer(const std::string &filename_line)
{
	return return_printer(filename_line);
}

template <typename Type_t>
const Type_t &return_printer::operator ,(const Type_t &value)
{
	out_stream stream(_filename_line);
	stream << "return " << make_pretty(value) << ENDLINE;
	return value;
}

}

