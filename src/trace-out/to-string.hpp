#pragma once

#include "trace-out/nothing.hpp"
#include <sstream>
#include <string>

//
// Public

namespace trace_out
{

template <typename Type_t>
const std::string to_string(const Type_t &value);

template <typename Type_t, typename Manipulator1_t>
const std::string to_string(const Type_t &value, const Manipulator1_t &manipulator1);

template <typename Type_t, typename Manipulator1_t, typename Manipulator2_t>
const std::string to_string(const Type_t &value, const Manipulator1_t &manipulator1, const Manipulator2_t &manipulator2);

}

//
// Implementation

namespace trace_out
{

template <typename Type_t>
const std::string to_string(const Type_t &value)
{
	std::stringstream string_stream;
	string_stream << value;
	return string_stream.str();
}

template <typename Type_t, typename Manipulator1_t>
const std::string to_string(const Type_t &value, const Manipulator1_t &manipulator1)
{
	std::stringstream string_stream;
	string_stream << manipulator1 << value;
	return string_stream.str();
}

template <typename Type_t, typename Manipulator1_t, typename Manipulator2_t>
const std::string to_string(const Type_t &value, const Manipulator1_t &manipulator1, const Manipulator2_t &manipulator2)
{
	std::stringstream string_stream;
	string_stream << manipulator1 << manipulator2 << value;
	return string_stream.str();
}

}

