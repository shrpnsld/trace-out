#include "trace-out/detail/stuff/platform-detection.hpp"
#if defined(TRACE_OUT_POSIX)

#include "trace-out/detail/system/constants.hpp"


namespace trace_out { namespace detail
{

	const char FILE_PATH_COMPONENT_DELIMITER = '/';

}
}


#endif // defined(TRACE_OUT_POSIX)

