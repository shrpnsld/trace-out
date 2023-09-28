#pragma once

#include <sstream>
#include <string>

//
// Public

namespace trace_out
{

template <typename Type_t>
const std::string to_string(const Type_t &value);

}

//
// Implementation

namespace trace_out
{

template <typename Type_t>
const std::string to_string(const Type_t &value)
{
	return (std::stringstream() << value).str();
}

}

