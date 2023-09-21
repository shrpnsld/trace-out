#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/platform-detection.hpp"
#include <cstdarg>
#include <cstdio>

//
// Public

namespace trace_out { namespace standard
{

inline size_t vsnprintf_string_length(const char *format, va_list arguments);
inline int vsnprintf(char *buffer, size_t size, const char *format, va_list arguments);

}
}

#if defined(TRACE_OUT_CLANG) || defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)

//
// Clang/GCC/MinGW Implementation

namespace trace_out { namespace standard
{

size_t vsnprintf_string_length(const char *format, va_list arguments)
{
	int retval = ::vsnprintf(NULL, 0, format, arguments);
	return static_cast<size_t>(retval);
}

int vsnprintf(char *buffer, size_t size, const char *format, va_list arguments)
{
	return ::vsnprintf(buffer, size, format, arguments);
}

}
}

#elif defined(TRACE_OUT_MVS)

//
// Visual Studio Implementation

namespace trace_out { namespace standard
{

size_t vsnprintf_string_length(const char *format, va_list arguments)
{
	int retval = _vscprintf(format, arguments);
	return static_cast<size_t>(retval);
}

int vsnprintf(char *buffer, size_t size, const char *format, va_list arguments)
{
	return _vsnprintf_s(buffer, size, _TRUNCATE, format, arguments);
}

}
}

#endif
