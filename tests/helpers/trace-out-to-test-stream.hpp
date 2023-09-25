#pragma once

#include "test-stream.hpp"

namespace trace_out_stream
{

inline void print(const char *string);
inline void flush();
inline unsigned int width();

}

namespace trace_out_stream
{

static const unsigned int DEFAULT_WIDTH = 79;

void print(const char *string)
{
	test::stream << string;
}

void flush()
{
	test::stream.flush();
}

unsigned int width()
{
	return DEFAULT_WIDTH;
}

}

