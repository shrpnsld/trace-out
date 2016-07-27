#include "../platform_defines.hpp"
#if defined(TRACE_OUT_POSIX)

#include <pthread.h>

#include "../system_thread.hpp"


namespace trace_out { namespace detail
{

	standard::uint64_t current_thread_id()
	{
		return reinterpret_cast<standard::uint64_t>(pthread_self());
	}

}
}


#endif // defined(TRACE_OUT_POSIX)

