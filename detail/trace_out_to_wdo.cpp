#include "platform_defines.hpp"
#if defined(TRACE_OUT_WINDOWS)

#include <windows.h>

#include "standard/integer.hpp"


namespace trace_out_to_wdo
{

	void print(const char *string)
	{
		OutputDebugStringA(string);
	}


	void flush()
	{
	}


	trace_out::detail::standard::size_t width()
	{
		return 120;
	}

}

#endif // defined(TRACE_OUT_WINDOWS)
