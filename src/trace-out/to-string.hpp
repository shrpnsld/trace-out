#pragma once

#include <sstream>
#include <string>

//
// Public

namespace trace_out
{

template <typename Type_t>
const std::string to_string(const Type_t &value);

template <typename Type_t, typename Manipulator_t>
const std::string to_string(const Type_t &value, const Manipulator_t &manipulator);

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

template <typename Type_t, typename Manipulator_t>
const std::string to_string(const Type_t &value, const Manipulator_t &manipulator)
{
	return (std::stringstream() << manipulator << value).str();
}

}

