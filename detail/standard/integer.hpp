#pragma once

#include <cstddef>

#include "trace-out/detail/stuff/platform-detection.hpp"

#if defined(TRACE_OUT_CPP11)
	#include <cstdint>
#else
	#include <stdint.h>
#endif


namespace trace_out { namespace detail { namespace standard
{

#if defined(TRACE_OUT_CPP11)
		typedef ::std::int8_t int8_t;
		typedef ::std::int16_t int16_t;
		typedef ::std::int32_t int32_t;
		typedef ::std::int64_t int64_t;

		typedef ::std::uint8_t uint8_t;
		typedef ::std::uint16_t uint16_t;
		typedef ::std::uint32_t uint32_t;
		typedef ::std::uint64_t uint64_t;

		typedef ::std::size_t size_t;
		typedef ::std::uintptr_t uintptr_t;
#else
		typedef ::int8_t int8_t;
		typedef ::int16_t int16_t;
		typedef ::int32_t int32_t;
		typedef ::int64_t int64_t;

		typedef ::uint8_t uint8_t;
		typedef ::uint16_t uint16_t;
		typedef ::uint32_t uint32_t;
		typedef ::uint64_t uint64_t;

		typedef ::size_t size_t;
		typedef ::uintptr_t uintptr_t;
#endif // defined(TRACE_OUT_CPP11)

}
}
}

