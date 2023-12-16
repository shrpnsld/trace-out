#pragma once

#include "trace-out/number-bytes-iterator.hpp"
#include "trace-out/byte-order.hpp"
#include "trace-out/integer.hpp"

//
// Public

namespace trace_out
{

class number_bits_iterator
{
public:
	inline number_bits_iterator(const standard::uint8_t *memory, standard::size_t size);

	inline unsigned operator *() const;
	inline number_bits_iterator &operator ++();

private:
	const standard::uint8_t *_current_byte;
	standard::size_t _current_bit_index;
};

}

//
// Implementation

namespace trace_out
{

number_bits_iterator::number_bits_iterator(const standard::uint8_t *memory, standard::size_t size)
	:
	_current_byte(byte_order_t::current() == byte_order_t::LITTLE ? memory : memory + (size - 1)),
	_current_bit_index(7)
{
}

unsigned number_bits_iterator::operator *() const
{
	standard::uint8_t mask = 1 << _current_bit_index;
	return (*_current_byte & mask) != 0;
}

number_bits_iterator &number_bits_iterator::operator ++()
{
	if (_current_bit_index > 0)
	{
		--_current_bit_index;
	}
	else
	{
		_current_byte = next_byte_in_number(_current_byte);
		_current_bit_index = 7;
	}

	return *this;
}

}

