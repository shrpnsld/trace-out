#pragma once

#include "trace-out/console.hpp"
#include <iostream>

//
// Public

namespace trace_out_stream
{

inline void print(const char *string);
inline void flush();
inline unsigned int width();

}

//
// Implementation

namespace trace_out_stream
{

static const unsigned int DEFAULT_WIDTH = 79;

void print(const char *string)
{
	std::cout << string;
}

void flush()
{
	std::cout.flush();
}

unsigned int width()
{
	int width = trace_out::system::console_width();
	if (width == -1)
	{
		return DEFAULT_WIDTH;
	}

	return static_cast<unsigned int>(width);
}

}

