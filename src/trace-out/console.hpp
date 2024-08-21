#pragma once

#include "trace-out/platform-detection.hpp"
#include "trace-out/integer.hpp"

//
// Public

namespace trace_out { namespace system
{

inline standard::size_t console_width();

}
}

//
// Private

namespace trace_out { namespace system
{

static const int CONSOLE_WIDTH_DEFAULT = 80;

}
}

//
// Implementation

#if defined(TRACE_OUT_STREAM_WIDTH)

namespace trace_out { namespace system
{

standard::size_t console_width()
{
	return TRACE_OUT_STREAM_WIDTH;
}

}
}

#elif defined(TRACE_OUT_POSIX)

//
// POSIX implementation

#include <sys/ioctl.h> // [amalgamate:leave]
#include <unistd.h> // [amalgamate:leave]

namespace trace_out { namespace system
{

standard::size_t console_width()
{
	winsize window_size;
	int retval = ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);
	if (retval == -1)
	{
		return CONSOLE_WIDTH_DEFAULT;
	}

	if (window_size.ws_col == 0)
	{
		return CONSOLE_WIDTH_DEFAULT;
	}

	return static_cast<standard::size_t>(window_size.ws_col - 1);
}

}
}

#elif defined(TRACE_OUT_WINDOWS)

//
// WinAPI implementation

#include "trace-out/windows-headers.hpp"

namespace trace_out { namespace system
{

standard::size_t console_width()
{
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;

	BOOL retval = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_buffer_info);
	if (retval == 0)
	{
		return CONSOLE_WIDTH_DEFAULT;
	}

	standard::size_t width = static_cast<standard::size_t>(screen_buffer_info.srWindow.Right - screen_buffer_info.srWindow.Left);
	return width;
}

}
}

#endif

