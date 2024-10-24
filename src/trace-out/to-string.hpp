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
	std::stringstream stream;
	stream << value;
	return stream.str();
}

template <typename Type_t, typename Manipulator_t>
const std::string to_string(const Type_t &value, const Manipulator_t &manipulator)
{
	std::stringstream stream;
	stream << manipulator << value;
	return stream.str();
}

}

