#pragma once

//
// Public

namespace trace_out
{

struct byte_order_t
{
	enum enumeration
	{
		NOT_SPECIFIED = 0,
		LITTLE = 1,
		BIG = 2
	};

	inline static byte_order_t::enumeration current();
};

}

//
// Implementation

namespace trace_out
{

byte_order_t::enumeration byte_order_t::current()
{
	static const standard::uint16_t TEST_VALUE = static_cast<standard::uint16_t>(0x0001);

	return *reinterpret_cast<const standard::uint8_t *>(&TEST_VALUE) == static_cast<standard::uint8_t>(0x01) ? BIG : LITTLE;
}

}

