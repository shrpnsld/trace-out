#pragma once

#include "trace-out/stuff/platform-detection.hpp"

namespace trace_out { namespace detail { namespace system
{

	inline int console_width();

}
}
}

#if defined(TRACE_OUT_POSIX)

#include <sys/ioctl.h> // [amalgamate:leave]
#include <unistd.h> // [amalgamate:leave]

namespace trace_out { namespace detail { namespace system
{

	int console_width()
	{
		winsize window_size;
		int retval = ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);
		if (retval == -1)
		{
			return -1;
		}

		return static_cast<int>(window_size.ws_col) - 1;
	}

}
}
}

#elif defined(TRACE_OUT_WINDOWS)

#include <windows.h> // [amalgamate:leave]

namespace trace_out { namespace detail { namespace system
{

	int console_width()
	{
		CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;

		BOOL retval = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_buffer_info);
		if (retval == 0)
		{
			return -1;
		}

		int width = static_cast<int>(screen_buffer_info.srWindow.Right - screen_buffer_info.srWindow.Left);
		return width;
	}

}
}
}

#endif

