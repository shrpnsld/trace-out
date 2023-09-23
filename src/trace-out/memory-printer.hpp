#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/nothing.hpp"
#include "trace-out/out-stream.hpp"
#include "trace-out/to-string.hpp"
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

//
// Public

#define $bin trace_out::bin_or_hex_option(trace_out::BIN)
#define $hex trace_out::bin_or_hex_option(trace_out::HEX)
#define $sdec trace_out::decimal_option(trace_out::SDEC)
#define $udec trace_out::decimal_option(trace_out::UDEC)
#define $flt trace_out::floating_point_option(trace_out::FLT)
#define $dbl trace_out::floating_point_option(trace_out::DBL)
#define $ldbl trace_out::floating_point_option(trace_out::LDBL)

#define $be trace_out::BIG
#define $le trace_out::LITTLE

#define $col(value) trace_out::column_count_option(value)

namespace trace_out
{

template <typename Option1_t = nothing, typename Option2_t = nothing>
void print_memory(const std::string &filename_line, const char *name, const standard::uint8_t *memory, standard::size_t size, Option1_t option1 = Option1_t(), Option2_t option2 = Option2_t());

}

//
// Private

namespace trace_out
{

enum base_t
{
	BIN,
	SDEC,
	UDEC,
	FLT,
	DBL,
	LDBL,
	HEX
};

enum byte_order_t
{
	BIG,
	LITTLE
};

struct bin_or_hex_option
{
	inline bin_or_hex_option(base_t base);

	inline const bin_or_hex_option &operator ()(standard::size_t new_grouping);

	base_t base;
	standard::size_t grouping;
};

struct decimal_option
{
	inline decimal_option(base_t base);

	inline const decimal_option &operator ()(standard::size_t new_grouping);
	inline const decimal_option &operator ()(byte_order_t byte_order);
	inline const decimal_option &operator ()(byte_order_t byte_order, standard::size_t new_grouping);
	inline const decimal_option &operator ()(standard::size_t new_grouping, byte_order_t byte_order);

	base_t base;
	standard::size_t grouping;
	byte_order_t byte_order;
};

struct floating_point_option
{
	inline floating_point_option(base_t base);

	inline const floating_point_option &operator ()(byte_order_t new_byte_order);
	inline static standard::size_t grouping_from_base(base_t base);

	base_t base;
	standard::size_t grouping;
	byte_order_t byte_order;
};

struct column_count_option
{
	inline column_count_option(standard::size_t value);

	standard::size_t value;
};

struct memory_display_options_t
{
	inline memory_display_options_t(base_t base, standard::size_t grouping, byte_order_t byte_order, standard::size_t column_count);

	inline void set_option(const bin_or_hex_option &option);
	inline void set_option(const decimal_option &option);
	inline void set_option(const floating_point_option &option);
	inline void set_option(const column_count_option &option);
	inline void set_option(nothing);

	base_t base;
	standard::size_t grouping;
	byte_order_t byte_order;
	standard::size_t column_count;
};

template <typename Type_t>
struct printable_number_t
{
	typedef Type_t type;
};

template <>
struct printable_number_t<standard::int8_t>
{
	typedef int type;
};

template <>
struct printable_number_t<standard::uint8_t>
{
	typedef unsigned int type;
};

inline byte_order_t current_byte_order();
inline const char *base_name(base_t value);
inline const char *byte_order_name(byte_order_t value);
inline standard::size_t field_width_for_base_and_grouping(base_t base, standard::size_t grouping);
inline standard::size_t power_of_2_under(standard::size_t number);
inline standard::size_t calculate_column_count(standard::size_t requested_column_count, standard::size_t stream_width, standard::size_t indentation_width, standard::size_t pointer_width, standard::size_t delimiter_width, standard::size_t padding_width, standard::size_t field_width);

typedef void (*print_chunk_t)(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width);
inline print_chunk_t select_print_chunk_function(base_t base, standard::size_t chunk_size, byte_order_t byte_order);
inline void print_binary_chunk(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width);
inline void print_hexadecimal_chunk(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width);

template <typename Type_t>
void print_number_chunk(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width);

template <typename Type_t>
void print_number_chunk_reverse(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width);

}

//
// Implementation

namespace trace_out
{

template <typename Option1_t, typename Option2_t>
void print_memory(const std::string &filename_line, const char *name, const standard::uint8_t *memory, standard::size_t size, Option1_t option1, Option2_t option2)
{
	memory_display_options_t options(HEX, 1, current_byte_order(), 0);
	options.set_option(option1);
	options.set_option(option2);

	standard::size_t field_width = field_width_for_base_and_grouping(options.base, options.grouping);
	print_chunk_t print_chunk = select_print_chunk_function(options.base, options.grouping, options.byte_order);

	out_stream stream(filename_line);
	stream << name << ", " << to_string(size) << " bytes of " << to_string(options.grouping) + "-byte " << base_name(options.base);
	if (options.grouping > 1 && options.base != BIN && options.base != HEX)
	{
		stream << ", " << byte_order_name(options.byte_order);
	}

	indentation_add();

	standard::size_t chunk_count = size / options.grouping;
	const standard::uint8_t *chunks_end = memory + chunk_count * options.grouping;
	standard::size_t column = 0;
	standard::size_t column_count = calculate_column_count(options.column_count, stream.width(), indentation().size(), to_string(static_cast<const void *>(memory)).size(), 1, field_width, 1);

	for (const standard::uint8_t *chunk = memory; chunk < chunks_end; chunk += options.grouping)
	{
		if (column % column_count == 0)
		{
			stream << NEWLINE << make_pretty(static_cast<const void *>(chunk)) << ":";
			column = 0;
		}

		stream << " " << FLUSH;
		print_chunk(stream, chunk, options.grouping, field_width);
		++column;
	}

	if (chunks_end < memory + size)
	{
		const standard::uint8_t *leftovers = chunks_end;
		const standard::uint8_t *leftovers_end = memory + size;
		stream << NEWLINE << NEWLINE << "leftovers:" << NEWLINE << make_pretty(static_cast<const void *>(leftovers)) << ":";
		for ( ; leftovers < leftovers_end; ++leftovers)
		{
			stream << " " << FLUSH;
			print_hexadecimal_chunk(stream, leftovers, 1, 2);
		}
	}

	stream << NEWLINE;
	indentation_remove();
	stream << ENDLINE;
}

template <typename Type_t>
void print_number_chunk(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width)
{
	Type_t number = *reinterpret_cast<const Type_t *>(chunk);
	typename printable_number_t<Type_t>::type printable_number = number;
	std::string printed_value = to_string(printable_number, std::setprecision(std::numeric_limits<Type_t>::digits10));

	for (standard::size_t padding_width = field_width - printed_value.size(); padding_width > 0; --padding_width)
	{
		stream << ' ';
	}

	stream << printed_value;
}

template <typename Type_t>
void print_number_chunk_reverse(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width)
{
	standard::uint8_t reversed_chunk[16];
	std::reverse_copy(chunk, chunk + size, reversed_chunk);

	Type_t number = *reinterpret_cast<const Type_t *>(reversed_chunk);
	typename printable_number_t<Type_t>::type printable_number = number;
	std::string printed_value = (std::stringstream() << std::setprecision(std::numeric_limits<Type_t>::digits10) << printable_number).str();

	for (standard::size_t padding_width = field_width - printed_value.size(); padding_width > 0; --padding_width)
	{
		stream << ' ';
	}

	stream << printed_value;
}

bin_or_hex_option::bin_or_hex_option(base_t base)
	:
	base(base),
	grouping(1)
{
}

const bin_or_hex_option &bin_or_hex_option::operator ()(standard::size_t new_grouping)
{
	grouping = new_grouping;

	return *this;
}

decimal_option::decimal_option(base_t base)
	:
	base(base),
	grouping(1),
	byte_order(current_byte_order())
{
}

const decimal_option &decimal_option::operator ()(standard::size_t new_grouping)
{
	grouping = new_grouping;

	return *this;
}

const decimal_option &decimal_option::operator ()(byte_order_t new_byte_order)
{
	byte_order = new_byte_order;

	return *this;
}

const decimal_option &decimal_option::operator ()(byte_order_t new_byte_order, standard::size_t new_grouping)
{
	grouping = new_grouping;
	byte_order = new_byte_order;
	return *this;
}

const decimal_option &decimal_option::operator ()(standard::size_t new_grouping, byte_order_t new_byte_order)
{
	grouping = new_grouping;
	byte_order = new_byte_order;
	return *this;
}

floating_point_option::floating_point_option(base_t base)
	:
	base(base),
	grouping(grouping_from_base(base))
{
}

const floating_point_option &floating_point_option::operator ()(byte_order_t new_byte_order)
{
	byte_order = new_byte_order;
	return *this;
}

standard::size_t floating_point_option::grouping_from_base(base_t base)
{
	switch (base)
	{
		case FLT:
			return sizeof(float);

		case DBL:
			return sizeof(double);

		case LDBL:
			return sizeof(long double);

		default:
			return 0;
	}
}

column_count_option::column_count_option(standard::size_t value)
	:
	 value(value)
{
}

memory_display_options_t::memory_display_options_t(base_t base, standard::size_t grouping, byte_order_t byte_order, standard::size_t column_count)
	:
	base(base),
	grouping(grouping),
	byte_order(byte_order),
	column_count(column_count)
{
}

void memory_display_options_t::set_option(const bin_or_hex_option &option)
{
	base = option.base;
	grouping = option.grouping;
}

void memory_display_options_t::set_option(const decimal_option &option)
{
	base = option.base;
	grouping = option.grouping;
	byte_order = option.byte_order;
}

void memory_display_options_t::set_option(const floating_point_option &option)
{
	base = option.base;
	grouping = option.grouping;
	byte_order = option.byte_order;
}

void memory_display_options_t::set_option(const column_count_option &option)
{
	column_count = option.value;
}

void memory_display_options_t::set_option(nothing)
{
}

byte_order_t current_byte_order()
{
	const standard::uint16_t VALUE = static_cast<standard::uint16_t>(0x0001);
	const standard::uint8_t FIRST_BYTE = *reinterpret_cast<const standard::uint8_t *>(&VALUE);

	if (FIRST_BYTE == static_cast<standard::uint8_t>(0x01))
	{
		return BIG;
	}
	else
	{
		return LITTLE;
	}
}

const char *base_name(base_t value)
{
	switch (value)
	{
		case BIN:
			return "binary";

		case HEX:
			return "hexadecimal";

		case SDEC:
			return "signed decimal";

		case UDEC:
			return "unsigned decimal";

		case FLT:
			return "float";

		case DBL:
			return "double";

		case LDBL:
			return "long double";
	}
}

const char *byte_order_name(byte_order_t value)
{
	switch (value)
	{
		case LITTLE:
			return "little-endian";

		case BIG:
			return "big-endian";
	}
}

standard::size_t field_width_for_base_and_grouping(base_t base, standard::size_t grouping)
{
	switch (base)
	{
		case BIN:
			return 8 * grouping;

		case HEX:
			return 2 * grouping;

		case SDEC:
		{
			switch (grouping)
			{
				case 1:
					return 4;

				case 2:
					return 6;

				case 4:
					return 11;

				case 8:
					return 21;

				default:
					return 0;
			}
		}

		case UDEC:
		{
			switch (grouping)
			{
				case 1:
					return 3;

				case 2:
					return 5;

				case 4:
					return 10;

				case 8:
					return 20;

				default:
					return 0;
			}
		}

		case FLT:
			return 1 + 1 + 1 + std::numeric_limits<float>::digits10 + 1 + 1 + 3;

		case DBL:
			return 1 + 1 + 1 + std::numeric_limits<double>::digits10 + 1 + 1 + 4;

		case LDBL:
			return 1 + 1 + 1 + std::numeric_limits<long double>::digits10 + 1 + 1 + 5;

		default:
			return 0;
	}
}

standard::size_t power_of_2_under(standard::size_t number)
{
	standard::size_t shift_count = 0;
	while (number > 1)
	{
		number >>= 1;
		++shift_count;
	}

	return number << shift_count;
}

standard::size_t calculate_column_count(standard::size_t requested_column_count, standard::size_t stream_width, standard::size_t indentation_width, standard::size_t pointer_width, standard::size_t delimiter_width, standard::size_t padding_width, standard::size_t field_width)
{
	standard::size_t content_width = stream_width - (indentation_width + pointer_width + delimiter_width);
	standard::size_t column_count = content_width / (padding_width + field_width);
	if (column_count == 0)
	{
		column_count = 1;
	}

	standard::size_t optimal_column_count = power_of_2_under(column_count);
	if (requested_column_count > 0 && requested_column_count < optimal_column_count)
	{
		return requested_column_count;
	}

	return optimal_column_count;
}

static const char *byte_to_binary(standard::uint8_t byte)
{
	static const char *const BINARY_VALUES[] = {
		"00000000", "00000001", "00000010", "00000011", "00000100", "00000101", "00000110", "00000111",
		"00001000", "00001001", "00001010", "00001011", "00001100", "00001101", "00001110", "00001111",
		"00010000", "00010001", "00010010", "00010011", "00010100", "00010101", "00010110", "00010111",
		"00011000", "00011001", "00011010", "00011011", "00011100", "00011101", "00011110", "00011111",
		"00100000", "00100001", "00100010", "00100011", "00100100", "00100101", "00100110", "00100111",
		"00101000", "00101001", "00101010", "00101011", "00101100", "00101101", "00101110", "00101111",
		"00110000", "00110001", "00110010", "00110011", "00110100", "00110101", "00110110", "00110111",
		"00111000", "00111001", "00111010", "00111011", "00111100", "00111101", "00111110", "00111111",
		"01000000", "01000001", "01000010", "01000011", "01000100", "01000101", "01000110", "01000111",
		"01001000", "01001001", "01001010", "01001011", "01001100", "01001101", "01001110", "01001111",
		"01010000", "01010001", "01010010", "01010011", "01010100", "01010101", "01010110", "01010111",
		"01011000", "01011001", "01011010", "01011011", "01011100", "01011101", "01011110", "01011111",
		"01100000", "01100001", "01100010", "01100011", "01100100", "01100101", "01100110", "01100111",
		"01101000", "01101001", "01101010", "01101011", "01101100", "01101101", "01101110", "01101111",
		"01110000", "01110001", "01110010", "01110011", "01110100", "01110101", "01110110", "01110111",
		"01111000", "01111001", "01111010", "01111011", "01111100", "01111101", "01111110", "01111111",
		"10000000", "10000001", "10000010", "10000011", "10000100", "10000101", "10000110", "10000111",
		"10001000", "10001001", "10001010", "10001011", "10001100", "10001101", "10001110", "10001111",
		"10010000", "10010001", "10010010", "10010011", "10010100", "10010101", "10010110", "10010111",
		"10011000", "10011001", "10011010", "10011011", "10011100", "10011101", "10011110", "10011111",
		"10100000", "10100001", "10100010", "10100011", "10100100", "10100101", "10100110", "10100111",
		"10101000", "10101001", "10101010", "10101011", "10101100", "10101101", "10101110", "10101111",
		"10110000", "10110001", "10110010", "10110011", "10110100", "10110101", "10110110", "10110111",
		"10111000", "10111001", "10111010", "10111011", "10111100", "10111101", "10111110", "10111111",
		"11000000", "11000001", "11000010", "11000011", "11000100", "11000101", "11000110", "11000111",
		"11001000", "11001001", "11001010", "11001011", "11001100", "11001101", "11001110", "11001111",
		"11010000", "11010001", "11010010", "11010011", "11010100", "11010101", "11010110", "11010111",
		"11011000", "11011001", "11011010", "11011011", "11011100", "11011101", "11011110", "11011111",
		"11100000", "11100001", "11100010", "11100011", "11100100", "11100101", "11100110", "11100111",
		"11101000", "11101001", "11101010", "11101011", "11101100", "11101101", "11101110", "11101111",
		"11110000", "11110001", "11110010", "11110011", "11110100", "11110101", "11110110", "11110111",
		"11111000", "11111001", "11111010", "11111011", "11111100", "11111101", "11111110", "11111111"
	};

	return BINARY_VALUES[byte];
}

static const char *byte_to_hexadecimal(standard::uint8_t byte)
{
	static const char *const HEXADECIMAL_VALUES[] = {
		"00", "01", "02", "03", "04", "05", "06", "07",
		"08", "09", "0a", "0b", "0c", "0d", "0e", "0f",
		"10", "11", "12", "13", "14", "15", "16", "17",
		"18", "19", "1a", "1b", "1c", "1d", "1e", "1f",
		"20", "21", "22", "23", "24", "25", "26", "27",
		"28", "29", "2a", "2b", "2c", "2d", "2e", "2f",
		"30", "31", "32", "33", "34", "35", "36", "37",
		"38", "39", "3a", "3b", "3c", "3d", "3e", "3f",
		"40", "41", "42", "43", "44", "45", "46", "47",
		"48", "49", "4a", "4b", "4c", "4d", "4e", "4f",
		"50", "51", "52", "53", "54", "55", "56", "57",
		"58", "59", "5a", "5b", "5c", "5d", "5e", "5f",
		"60", "61", "62", "63", "64", "65", "66", "67",
		"68", "69", "6a", "6b", "6c", "6d", "6e", "6f",
		"70", "71", "72", "73", "74", "75", "76", "77",
		"78", "79", "7a", "7b", "7c", "7d", "7e", "7f",
		"80", "81", "82", "83", "84", "85", "86", "87",
		"88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
		"90", "91", "92", "93", "94", "95", "96", "97",
		"98", "99", "9a", "9b", "9c", "9d", "9e", "9f",
		"a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7",
		"a8", "a9", "aa", "ab", "ac", "ad", "ae", "af",
		"b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7",
		"b8", "b9", "ba", "bb", "bc", "bd", "be", "bf",
		"c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7",
		"c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf",
		"d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",
		"d8", "d9", "da", "db", "dc", "dd", "de", "df",
		"e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7",
		"e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef",
		"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7",
		"f8", "f9", "fa", "fb", "fc", "fd", "fe", "ff"
	};

	return HEXADECIMAL_VALUES[byte];
}

print_chunk_t select_print_chunk_function(base_t base, standard::size_t chunk_size, byte_order_t byte_order)
{
	switch (base)
	{
		case BIN:
			return print_binary_chunk;

		case HEX:
			return print_hexadecimal_chunk;

		case SDEC:
		{
			switch (chunk_size)
			{
				case 1:
					return byte_order == current_byte_order() ? print_number_chunk<standard::int8_t> : print_number_chunk_reverse<standard::int8_t>;

				case 2:
					return byte_order == current_byte_order() ? print_number_chunk<standard::int16_t> : print_number_chunk_reverse<standard::int16_t>;

				case 4:
					return byte_order == current_byte_order() ? print_number_chunk<standard::int32_t> : print_number_chunk_reverse<standard::int32_t>;

				case 8:
					return byte_order == current_byte_order() ? print_number_chunk<standard::int64_t> : print_number_chunk_reverse<standard::int64_t>;

				default:
					return NULL;
			}
		}

		case UDEC:
			switch (chunk_size)
			{
				case 1:
					return byte_order == current_byte_order() ? print_number_chunk<standard::uint8_t> : print_number_chunk_reverse<standard::uint8_t>;

				case 2:
					return byte_order == current_byte_order() ? print_number_chunk<standard::uint16_t> : print_number_chunk_reverse<standard::uint16_t>;

				case 4:
					return byte_order == current_byte_order() ? print_number_chunk<standard::uint32_t> : print_number_chunk_reverse<standard::uint32_t>;

				case 8:
					return byte_order == current_byte_order() ? print_number_chunk<standard::uint64_t> : print_number_chunk_reverse<standard::uint64_t>;

				default:
					return NULL;
			}

		case FLT:
			return byte_order == current_byte_order() ? print_number_chunk<float> : print_number_chunk_reverse<float>;

		case DBL:
			return byte_order == current_byte_order() ? print_number_chunk<double> : print_number_chunk_reverse<double>;

		case LDBL:
			return byte_order == current_byte_order() ? print_number_chunk<long double> : print_number_chunk_reverse<long double>;
	}
}

void print_binary_chunk(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width)
{
	for (const standard::uint8_t *end = chunk + size; chunk < end; ++chunk)
	{
		stream << byte_to_binary(*chunk);
	}
}

void print_hexadecimal_chunk(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width)
{
	for (const standard::uint8_t *end = chunk + size; chunk < end; ++chunk)
	{
		stream << byte_to_hexadecimal(*chunk);
	}
}

}
