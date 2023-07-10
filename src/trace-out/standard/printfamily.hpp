#pragma once

#include <cstdarg>

#include "trace-out/standard/integer.hpp"


namespace trace_out { namespace detail { namespace standard
{

	size_t vsnprintf_string_length(const char *format, va_list arguments);
	int vsnprintf(char *buffer, size_t size, const char *format, va_list arguments);

}
}
}
