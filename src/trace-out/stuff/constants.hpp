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
	const char FILENAME_FIELD_EXCESS_PADDING[] = "~";
	const standard::size_t FILENAME_FIELD_EXCESS_PADDING_SIZE = sizeof(FILENAME_FIELD_EXCESS_PADDING);
	const standard::size_t FILENAME_FIELD_WIDTH = 20;
	const standard::size_t LINE_FIELD_WIDTH = 4;
	const char DELIMITER[] = " |  ";
	const standard::size_t INDENTATION_WIDTH = sizeof(INDENTATION) - 1;

}
}

