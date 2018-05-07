#include "trace-out/detail/stuff/platform-detection.hpp"
#if defined(TRACE_OUT_POSIX)

#include <pthread.h>

#include "trace-out/detail/system/thread.hpp"


namespace trace_out { namespace detail { namespace system
{

	standard::uint64_t current_thread_id()
	{
		return reinterpret_cast<standard::uint64_t>(pthread_self());
	}

}
}
}


#endif // defined(TRACE_OUT_POSIX)

