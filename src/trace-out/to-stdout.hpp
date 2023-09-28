#pragma once

#include <iostream>

//
// Public

#if defined(TRACE_OUT_TO_STDOUT)

namespace trace_out_to_stdout
{

static std::ostream &stream()
{
	return std::cout;
}

}

#endif

