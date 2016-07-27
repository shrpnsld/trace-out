#include "../platform_defines.hpp"
#if defined(TRACE_OUT_WINDOWS)

#include <windows.h>

#include "../system_thread.hpp"


namespace trace_out { namespace detail
{

	standard::uint64_t current_thread_id()
	{
		return static_cast<standard::uint64_t>(GetCurrentThreadId());
	}

}
}


#endif // defined(TRACE_OUT_WINDOWS)

