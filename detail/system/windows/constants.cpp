#include "trace-out/detail/stuff/platform-detection.hpp"
#if defined(TRACE_OUT_WINDOWS)

#include "trace-out/detail/system/constants.hpp"


namespace trace_out { namespace detail { namespace system
{

	const char FILE_PATH_COMPONENT_DELIMITER = '\\';

}
}
}


#endif // defined(TRACE_OUT_WINDOWS)

