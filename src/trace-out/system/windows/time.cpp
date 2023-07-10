//#include "trace-out/stuff/platform-detection.hpp" // [amalgamate:uncomment]
//#if defined(TRACE_OUT_WINDOWS) // [amalgamate:uncomment]

#include <windows.h> // [amalgamate:leave]

#include "trace-out/system/time.hpp"


namespace trace_out { namespace detail { namespace system
{

	standard::uint64_t time_in_milliseconds()
	{
		FILETIME file_time;
		ULARGE_INTEGER large_integer;

		GetSystemTimeAsFileTime(&file_time);
		large_integer.LowPart = file_time.dwLowDateTime;
		large_integer.HighPart = file_time.dwHighDateTime;

		standard::uint64_t milliseconds = (large_integer.QuadPart - 116444736000000000LL) / 10000;

		return milliseconds;
	}

}
}
}


//#endif // defined(TRACE_OUT_WINDOWS) // [amalgamate:uncomment]

