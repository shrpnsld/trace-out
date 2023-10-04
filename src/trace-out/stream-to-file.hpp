#pragma once

#include <fstream>

#if defined(TRACE_OUT_STREAM_TO_FILE)

//
// Public

namespace trace_out_stream_to_file
{

inline std::ostream &stream();

}

//
// Implementaation

namespace trace_out_stream_to_file
{

std::ostream &stream()
{
	static std::ofstream _stream(TRACE_OUT_STREAM_TO_FILE, std::ios::out);
	assert(_stream.is_open());

	return _stream;
}

}

#endif

