#include "helpers/test-stream.hpp"
#include "trace-out/standard/integer.hpp"
#include "trace-out/system/console.hpp"


namespace trace_out_to_test_stream
{

	void print(const char *string);
	void flush();
	trace_out::detail::standard::size_t width();

}


namespace trace_out_to_test_stream
{

	const trace_out::detail::standard::size_t DEFAULT_WIDTH = 79;


	void print(const char *string)
	{
		test::stream << string;
	}


	void flush()
	{
		test::stream.flush();
	}


	trace_out::detail::standard::size_t width()
	{
		int width = trace_out::detail::system::console_width();
		if (width == -1)
		{
			return DEFAULT_WIDTH;
		}

		return static_cast<trace_out::detail::standard::size_t>(width);
	}

}

