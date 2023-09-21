#pragma once

#include "trace-out/standard/integer.hpp"
#include <cstring>

//
// Public

namespace trace_out
{

template <typename Type_t>
void try_memory(const Type_t &variable);

}

//
// Implementation

namespace trace_out
{

template <typename Type_t>
void try_memory(const Type_t &variable)
{
	standard::uint8_t buffer[sizeof(variable)];
	std::memcpy(buffer, &variable, sizeof(buffer));
}

}

