#pragma once

#include <fstream>

//
// Public

#if defined(TRACE_OUT_TO_FILE)

namespace trace_out_to_file
{

static std::ostream &stream()
{
	static std::ofstream _stream(TRACE_OUT_TO_FILE, std::ios::out);
	assert(_stream.is_open());

	return _stream;
}

}

#endif

