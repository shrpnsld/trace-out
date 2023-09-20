#pragma once

#include <cstdarg>
#include <cstdio>

#include "trace-out/standard/integer.hpp"
#include "trace-out/stuff/platform-detection.hpp"


namespace trace_out { namespace detail { namespace standard
{

	inline size_t vsnprintf_string_length(const char *format, va_list arguments);
	inline int vsnprintf(char *buffer, size_t size, const char *format, va_list arguments);

}
}
}

#if defined(TRACE_OUT_CLANG) || defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)

namespace trace_out { namespace detail { namespace standard
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
}

#elif defined(TRACE_OUT_MVS)

namespace trace_out { namespace detail { namespace standard
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
}

#endif
