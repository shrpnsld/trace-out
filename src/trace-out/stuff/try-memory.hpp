#pragma once

#include "trace-out/standard/integer.hpp"
#include <cstring>


namespace trace_out { namespace detail
{

	template <typename Type_t>
	void try_memory(const Type_t &variable);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	void try_memory(const Type_t &variable)
	{
		standard::uint8_t buffer[sizeof(variable)];
		std::memcpy(buffer, &variable, sizeof(buffer));
	}

}
}

