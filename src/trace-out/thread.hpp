#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/platform-detection.hpp"

//
// Public

namespace trace_out { namespace system
{

inline standard::uint64_t current_thread_id();

}
}

#if defined(TRACE_OUT_POSIX)

//
// POSIX implementation

#include <pthread.h> // [amalgamate:leave]

namespace trace_out { namespace system
{

standard::uint64_t current_thread_id()
{
	return reinterpret_cast<standard::uint64_t>(pthread_self());
}

}
}

#elif defined(TRACE_OUT_WINDOWS)

//
// WinAPI implementation

#include <windows.h> // [amalgamate:leave]

namespace trace_out { namespace system
{

standard::uint64_t current_thread_id()
{
	return static_cast<standard::uint64_t>(GetCurrentThreadId());
}

}
}

#endif

