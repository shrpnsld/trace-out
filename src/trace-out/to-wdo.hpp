#pragma once

#include "trace-out/platform-detection.hpp"
#if defined(TRACE_OUT_WINDOWS)

#include <windows.h> // [amalgamate:leave]

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

void print(const char *string)
{
	OutputDebugStringA(string);
}

void flush()
{
}

unsigned int width()
{
	return 120;
}

}

#endif // defined(TRACE_OUT_WINDOWS)
