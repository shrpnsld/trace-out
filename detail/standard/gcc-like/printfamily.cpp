#include "trace-out/detail/stuff/platform-detection.hpp"
#if defined(TRACE_OUT_CLANG) || defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)

#include "trace-out/detail/standard/printfamily.hpp"

#include <cstdio>


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


#endif // defined(TRACE_OUT_CLANG) || defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)
