#pragma once

#include "trace-out/standard/integer.hpp"


namespace trace_out { namespace detail
{

#if defined(TRACE_OUT_INDENTATION)
	const char INDENTATION[] = TRACE_OUT_INDENTATION;
#else
	const char INDENTATION[] = "    ";
#endif

#if defined(TRACE_OUT_MARKER)
	const char MARKER[] = TRACE_OUT_MARKER " ";
#else
	const char MARKER[] = "";
#endif

	const char THREAD_HEADER_SEPARATOR = '~';
	const char DELIMITER[] = " |  ";
	const standard::size_t INDENTATION_WIDTH = sizeof(INDENTATION) - 1;

}
}

