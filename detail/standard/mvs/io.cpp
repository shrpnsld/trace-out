#include "../../platform_defines.hpp"
#if defined(TRACE_OUT_MVS)

#include "../io.hpp"

#include <cstdio>


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


#endif // defined(TRACE_OUT_MVS)

