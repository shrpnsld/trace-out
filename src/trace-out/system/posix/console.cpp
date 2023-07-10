//#include "trace-out/stuff/platform-detection.hpp" // [amalgamate:uncomment]
//#if defined(TRACE_OUT_POSIX) // [amalgamate:uncomment]

#include <sys/ioctl.h> // [amalgamate:leave]
#include <unistd.h> // [amalgamate:leave]

#include "trace-out/system/console.hpp"


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


//#endif // defined(TRACE_OUT_POSIX) // [amalgamate:uncomment]

