#pragma once

#include <string>

#include "trace-out/detail/pretty-printing/out-stream.hpp"


namespace trace_out { namespace detail
{

	class function_printer
	{
	public:
		function_printer(const std::string &filename_line, const std::string &function_signature);
		~function_printer();

	private:
		std::string _filename_line;
		std::string _function_signature;
	};


	function_printer make_function_printer(const std::string &filename_line, const std::string &function_signature);



	class return_printer
	{
	public:
		return_printer(const std::string &filename_line);

		template <typename T>
		const T &operator ,(const T &value);

	private:
		std::string _filename_line;
	};


	return_printer make_return_printer(const std::string &filename_line);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	const Type_t &return_printer::operator ,(const Type_t &value)
	{
		out_stream stream(_filename_line);
		stream << "return " << make_pretty(value) << ENDLINE;
		return value;
	}

}
}

