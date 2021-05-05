//#include "trace-out/detail/stuff/platform-detection.hpp" // [amalgamate:uncomment]
//#if defined(TRACE_OUT_POSIX) // [amalgamate:uncomment]

#include <cstddef>
#include <cassert> // [amalgamate:leave]
#include <sys/time.h> // [amalgamate:leave]

#include "trace-out/detail/system/time.hpp"


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


//#endif // defined(TRACE_OUT_POSIX) // [amalgamate:uncomment]

