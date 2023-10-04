#pragma once

#include <iostream>

//
// Public

namespace trace_out_stream_to_stdout
{

inline std::ostream &stream();

}

//
// Implementation

namespace trace_out_stream_to_stdout
{

std::ostream &stream()
{
	return std::cout;
}

}

