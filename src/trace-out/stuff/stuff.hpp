#pragma once

#include <cstring>

#include "trace-out/standard/integer.hpp"


namespace trace_out { namespace detail
{

	struct nothing {};

	template <typename Type_t>
	void crash_on_bad_memory(const Type_t &variable);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	void crash_on_bad_memory(const Type_t &variable)
	{
		standard::uint8_t buffer[sizeof(variable)];
		std::memcpy(buffer, &variable, sizeof(buffer));
	}

}
}

