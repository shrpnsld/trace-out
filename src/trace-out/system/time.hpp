#pragma once

#include "trace-out/standard/integer.hpp"
#include "trace-out/stuff/platform-detection.hpp"


namespace trace_out { namespace detail { namespace system
{

	inline standard::uint64_t time_in_milliseconds();

}
}
}

#if defined(TRACE_OUT_POSIX)

#include <cstddef>
#include <cassert> // [amalgamate:leave]
#include <sys/time.h> // [amalgamate:leave]

namespace trace_out { namespace detail { namespace system
{

	standard::uint64_t time_in_milliseconds()
	{
		struct timeval time_value;
		int retval = gettimeofday(&time_value, NULL);
		assert(retval == 0);

		standard::uint64_t microseconds = static_cast<standard::uint64_t>(time_value.tv_usec);
		standard::uint64_t seconds = static_cast<standard::uint64_t>(time_value.tv_sec);
		standard::uint64_t milliseconds = seconds * 1000 + microseconds / 1000;

		return milliseconds;
	}

}
}
}

#elif defined(TRACE_OUT_WINDOWS)

#include <windows.h> // [amalgamate:leave]

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

#endif

