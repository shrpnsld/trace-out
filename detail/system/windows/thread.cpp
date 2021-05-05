//#include "trace-out/detail/stuff/platform-detection.hpp" // [amalgamate:uncomment]
//#if defined(TRACE_OUT_WINDOWS) // [amalgamate:uncomment]

#include <windows.h> // [amalgamate:leave]

#include "trace-out/detail/system/thread.hpp"


namespace trace_out { namespace detail { namespace system
{

	standard::uint64_t current_thread_id()
	{
		return static_cast<standard::uint64_t>(GetCurrentThreadId());
	}

}
}
}


//#endif // defined(TRACE_OUT_WINDOWS) // [amalgamate:uncomment]

