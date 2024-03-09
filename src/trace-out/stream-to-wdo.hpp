#pragma once

#include "trace-out/platform-detection.hpp"
#include <streambuf>

#if defined(TRACE_OUT_STREAM_TO_WDO) && defined(TRACE_OUT_WINDOWS)

#include "trace-out/windows-headers.hpp"
#include <cstring> // [amalgamate:leave]

//
// Public

namespace trace_out_stream_to_wdo
{

inline std::ostream &stream();

}

//
// Private

namespace trace_out
{

class wdo_stream_buf
	:
	public std::basic_streambuf<char>
{
public:
	inline virtual std::streamsize xsputn(const char_type *what, std::streamsize how_much);
	inline virtual int_type overflow(int_type ch);
};

inline wdo_stream_buf &wdo_stream_buf_instance();

}

//
// Implementation

namespace trace_out_stream_to_wdo
{

inline std::ostream &stream()
{
	static std::ostream _stream(&trace_out::wdo_stream_buf_instance());

	return _stream;
}

}

namespace trace_out
{

wdo_stream_buf &wdo_stream_buf_instance()
{
	static wdo_stream_buf _buffer;

	return _buffer;
}

std::streamsize wdo_stream_buf::xsputn(const char_type *what, std::streamsize how_much)
{
	const std::streamsize BUFFER_SIZE = 128;
	const std::streamsize STRING_SIZE = BUFFER_SIZE - 1;
	char_type buffer[BUFFER_SIZE];

	for ( ; how_much > STRING_SIZE; what += STRING_SIZE, how_much -= STRING_SIZE)
	{
		std::memcpy(buffer, what, STRING_SIZE);
		buffer[STRING_SIZE] = 0;
		OutputDebugStringA(buffer);
	}

	std::memcpy(buffer, what, how_much);
	buffer[how_much] = 0;
	OutputDebugStringA(buffer);

	return how_much;
}

wdo_stream_buf::int_type wdo_stream_buf::overflow(int_type ch)
{
	char_type buffer[2] = {static_cast<char_type>(ch), 0};
	OutputDebugStringA(buffer);
	return traits_type::not_eof(ch);
}

}

#endif // defined(TRACE_OUT_STREAM_TO_WDO) && defined(TRACE_OUT_WINDOWS)

