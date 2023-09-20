#pragma once

#include "trace-out/stuff/nothing.hpp"
#include <string>
#include <sstream>

namespace trace_out { namespace detail
{

	template <typename Manipulator_t>
	void apply_io_manipulators(std::ostream &stream, const Manipulator_t &manipulator);

	inline void apply_io_manipulators(std::ostream &stream, const nothing &);

	template <typename Type_t, typename Manipulator1_t = nothing, typename Manipulator2_t = nothing, typename Manipulator3_t = nothing>
	const std::string to_string(const Type_t &value, const Manipulator1_t &manipulator1 = Manipulator1_t(), const Manipulator2_t &manipulator2 = Manipulator2_t(), const Manipulator3_t &manipulator = Manipulator3_t());

}
}


namespace trace_out { namespace detail
{

	template <typename Manipulator_t>
	void apply_io_manipulators(std::ostream &stream, const Manipulator_t &manipulator)
	{
		stream << manipulator;
	}


	void apply_io_manipulators(std::ostream &, const nothing &)
	{
	}


	template <typename Type_t, typename Manipulator1_t, typename Manipulator2_t, typename Manipulator3_t>
	const std::string to_string(const Type_t &value, const Manipulator1_t &manipulator1, const Manipulator2_t &manipulator2, const Manipulator3_t &manipulator3)
	{
		std::stringstream string_stream;

		apply_io_manipulators(string_stream, manipulator1);
		apply_io_manipulators(string_stream, manipulator2);
		apply_io_manipulators(string_stream, manipulator3);

		string_stream << value;

		return string_stream.str();
	}

}
}

