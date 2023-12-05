#pragma once

//
// Private

namespace trace_out
{

static const standard::uint16_t BYTE_ORDER_TEST_VALUE = static_cast<standard::uint16_t>(0x0001);

}

//
// Public

namespace trace_out
{

enum byte_order_t
{
	LITTLE = 0,
	BIG = 1
};

static const byte_order_t CURRENT_BYTE_ORDER = static_cast<byte_order_t>(*reinterpret_cast<const standard::uint8_t *>(&BYTE_ORDER_TEST_VALUE) == static_cast<standard::uint8_t>(0x01));

}

