#pragma once

#include "trace-out/stuff/platform-detection.hpp"

namespace trace_out { namespace detail { namespace system
{

	static const char FILE_PATH_COMPONENT_DELIMITER =
#if defined(TRACE_OUT_POSIX)
	'/'
#elif defined(TRACE_OUT_WINDOWS)
	'\\'
#endif
	;

}
}
}

