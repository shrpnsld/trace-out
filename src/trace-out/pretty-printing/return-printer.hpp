#pragma once

#include "trace-out/pretty-printing/out-stream.hpp"
#include <string>


namespace trace_out { namespace detail
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
}


namespace trace_out { namespace detail
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
}
