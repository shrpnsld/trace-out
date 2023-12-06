#pragma once

#include "trace-out/byte-order.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/number-format.hpp"

//
// Private

namespace trace_out
{

typedef const standard::uint8_t *(*next_number_byte_func_t)(const standard::uint8_t *);

static inline const standard::uint8_t *plus_one(const standard::uint8_t *pointer);
static inline const standard::uint8_t *minus_one(const standard::uint8_t *pointer);

}

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


template <typename Type_t>
const standard::uint8_t *first_byte_in_number(const Type_t &number);

template <typename Type_t>
const standard::uint8_t *last_byte_in_number(const Type_t &number);

static const next_number_byte_func_t next_byte_in_number = CURRENT_BYTE_ORDER == LITTLE ? plus_one : minus_one;

}

//
// Implementation

namespace trace_out
{

number_bits_iterator::number_bits_iterator(const standard::uint8_t *memory, standard::size_t size)
	:
	_current_byte(CURRENT_BYTE_ORDER == LITTLE ? memory : memory + (size - 1)),
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

template <typename Type_t>
const standard::uint8_t *first_byte_in_number(const Type_t &number)
{
	const standard::uint8_t *pointer = reinterpret_cast<const standard::uint8_t *>(&number);
	return CURRENT_BYTE_ORDER == LITTLE ? pointer : pointer + (number_format<Type_t>::size() - 1);
}

template <typename Type_t>
const standard::uint8_t *last_byte_in_number(const Type_t &number)
{
	const standard::uint8_t *pointer = reinterpret_cast<const standard::uint8_t *>(&number);
	return CURRENT_BYTE_ORDER == LITTLE ? pointer + (number_format<Type_t>::size() - 1) : pointer;
}

const standard::uint8_t *plus_one(const standard::uint8_t *pointer)
{
	return pointer + 1;
}

const standard::uint8_t *minus_one(const standard::uint8_t *pointer)
{
	return pointer - 1;
}

}

