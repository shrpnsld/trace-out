#pragma once

//
// Public

namespace trace_out
{

template <typename Type_t>
struct number_format
{
public:
	static standard::size_t exponent_length();
	static standard::size_t exponent_first_byte_length();
	static standard::size_t exponent_rest_bytes_count();

	static standard::size_t mantissa_length();
	static standard::size_t mantissa_first_byte_length();
	static standard::size_t mantissa_rest_bytes_count();

	static standard::size_t length();
	static standard::size_t size();
};

}

//
// Private

namespace trace_out
{

template <typename Type_t>
standard::size_t length_in_bits(Type_t number);

}

//
// Implementation

namespace trace_out
{

template <typename Type_t>
standard::size_t number_format<Type_t>::exponent_length()
{
	return length_in_bits(std::numeric_limits<Type_t>::max_exponent);
}

template <typename Type_t>
standard::size_t number_format<Type_t>::exponent_first_byte_length()
{
	return number_format<Type_t>::exponent_length() % 8;
}

template <typename Type_t>
standard::size_t number_format<Type_t>::exponent_rest_bytes_count()
{
	return (number_format<Type_t>::exponent_length() - number_format<Type_t>::exponent_first_byte_length()) / 8;
}

template <typename Type_t>
standard::size_t number_format<Type_t>::mantissa_length()
{
	// 80-bit floating points don't have implicit leading 1, so this code compensates for that
	return std::numeric_limits<Type_t>::digits - ((1 + number_format<Type_t>::exponent_length() + std::numeric_limits<Type_t>::digits) % 8);
}

template <typename Type_t>
standard::size_t number_format<Type_t>::length()
{
	return 1 + number_format<Type_t>::exponent_length() + number_format<Type_t>::mantissa_length();
}

template <typename Type_t>
standard::size_t number_format<Type_t>::mantissa_first_byte_length()
{
	return number_format<Type_t>::mantissa_length() % 8;
}

template <typename Type_t>
standard::size_t number_format<Type_t>::mantissa_rest_bytes_count()
{
	return (number_format<Type_t>::mantissa_length() - number_format<Type_t>::mantissa_first_byte_length()) / 8;
}

template <typename Type_t>
standard::size_t number_format<Type_t>::size()
{
	// size of 80-bit floating point variable would usually be 16 bytes due to alignment.
	// this function returns size the type itself
	return number_format<Type_t>::length() / 8;
}

template <typename Type_t>
standard::size_t length_in_bits(Type_t number)
{
	standard::size_t length = 0;
	for ( ; number > 0; number >>= 1)
	{
		++length;
	}

	return length;
}

}
