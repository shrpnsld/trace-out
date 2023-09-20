#pragma once

#include "trace-out/standard/integer.hpp"
#include "trace-out/stuff/platform-detection.hpp"


namespace trace_out { namespace detail { namespace system
{

	inline standard::uint64_t current_thread_id();

}
}
}

#if defined(TRACE_OUT_POSIX)

#include <pthread.h> // [amalgamate:leave]


namespace trace_out { namespace detail { namespace system
{

	standard::uint64_t current_thread_id()
	{
		return reinterpret_cast<standard::uint64_t>(pthread_self());
	}

}
}
}

#elif defined(TRACE_OUT_WINDOWS)

#include <windows.h> // [amalgamate:leave]


namespace trace_out { namespace detail { namespace system
{

	standard::uint64_t current_thread_id()
	{
		return static_cast<standard::uint64_t>(GetCurrentThreadId());
	}

}
}
}

#endif

