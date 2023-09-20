#include <fstream>
#include <cassert>

#include "trace-out/standard/integer.hpp"


namespace trace_out_stream
{

	inline void print(const char *string);
	inline void flush();
	inline unsigned int width();

}


namespace trace_out_stream
{

	static std::ofstream stream;

	void print(const char *string)
	{
		if (!stream.is_open())
		{
			stream.open(TRACE_OUT_TO_FILE);
		}

		stream << string;
	}


	void flush()
	{
		assert(stream.is_open());

		stream.flush();
	}


	unsigned int width()
	{
		return 120;
	}

}

