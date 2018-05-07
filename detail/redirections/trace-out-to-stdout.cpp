#include <iostream>

#include "trace-out/detail/standard/integer.hpp"
#include "trace-out/detail/system/console.hpp"


namespace trace_out_to_stdout
{

	void print(const char *string);
	void flush();
	trace_out::detail::standard::size_t width();

}


namespace trace_out_to_stdout
{

	const trace_out::detail::standard::size_t DEFAULT_WIDTH = 79;


	void print(const char *string)
	{
		std::cout << string;
	}


	void flush()
	{
		std::cout.flush();
	}


	trace_out::detail::standard::size_t width()
	{
		int width = trace_out::detail::console_width();
		if (width == -1)
		{
			return DEFAULT_WIDTH;
		}

		return static_cast<trace_out::detail::standard::size_t>(width);
	}

}

