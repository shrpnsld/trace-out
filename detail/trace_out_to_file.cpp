#include <fstream>
#include <cassert>

#include "standard/integer.hpp"
#include "stuff.hpp"


#if !defined(TRACE_OUT_TO_FILE)
	#define TRACE_OUT_TO_FILE trace-out.txt
#endif


namespace trace_out_to_file
{

	std::ofstream stream;


	void print(const char *string)
	{
		if (!stream.is_open())
		{
			stream.open(trace_out_private__quotize(TRACE_OUT_TO_FILE));
		}

		stream << string;
	}


	void flush()
	{
		assert(stream.is_open());

		stream.flush();
	}


	trace_out::detail::standard::size_t width()
	{
		return 120;
	}

}

