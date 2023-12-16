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

template <typename Type_t>
const standard::uint8_t *first_byte_in_number(const Type_t &number);

inline const standard::uint8_t *first_byte_in_number(const standard::uint8_t *pointer, standard::size_t size);

template <typename Type_t>
const standard::uint8_t *last_byte_in_number(const Type_t &number);

inline const standard::uint8_t *last_byte_in_number(const standard::uint8_t *pointer, standard::size_t size);

static const next_number_byte_func_t next_byte_in_number = byte_order_t::current() == byte_order_t::LITTLE ? plus_one : minus_one;

}

//
// Implementation

namespace trace_out
{

template <typename Type_t>
const standard::uint8_t *first_byte_in_number(const Type_t &number)
{
	const standard::uint8_t *pointer = reinterpret_cast<const standard::uint8_t *>(&number);
	return byte_order_t::current() == byte_order_t::LITTLE ? pointer : pointer + (number_format<Type_t>::size() - 1);
}

const standard::uint8_t *first_byte_in_number(const standard::uint8_t *pointer, standard::size_t size)
{
	return byte_order_t::current() == byte_order_t::LITTLE ? pointer : pointer + (size - 1);
}

template <typename Type_t>
const standard::uint8_t *last_byte_in_number(const Type_t &number)
{
	const standard::uint8_t *pointer = reinterpret_cast<const standard::uint8_t *>(&number);
	return byte_order_t::current() == byte_order_t::LITTLE ? pointer + (number_format<Type_t>::size() - 1) : pointer;
}

const standard::uint8_t *last_byte_in_number(const standard::uint8_t *pointer, standard::size_t size)
{
	return byte_order_t::current() == byte_order_t::LITTLE ? pointer + (size - 1) : pointer;
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

