#pragma once

#include "trace-out/indentation.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/console.hpp"
#include "trace-out/mutex.hpp"
#include "trace-out/nothing.hpp"
#include "trace-out/pretty-lines.hpp"
#include "trace-out/to-string.hpp"
#include <iomanip>
#include <ostream>
#include <limits>

//
// Public

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

inline void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size);

template <typename Option1_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1);

template <typename Option1_t, typename Option2_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1, const Option2_t &option2);

template <typename Option1_t, typename Option2_t, typename Option3_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1, const Option2_t &option2, const Option3_t &option3);

template <typename Option1_t, typename Option2_t, typename Option3_t, typename Option4_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1, const Option2_t &option2, const Option3_t &option3, const Option4_t &option4);

}

//
// Private

namespace trace_out
{

struct base_option
{
	inline explicit base_option(base_t value);

	base_t value;
};

struct grouping_option
{
	inline explicit grouping_option(standard::size_t value);

	standard::size_t value;
};

struct byte_order_option
{
	inline explicit byte_order_option(byte_order_t value);

	byte_order_t value;
};

struct column_count_option
{
	inline explicit column_count_option(standard::size_t value);

	standard::size_t value;
};

struct memory_display_options_t
{
	inline memory_display_options_t(base_t base, standard::size_t grouping, byte_order_t byte_order, standard::size_t column_count);

	inline void set_option(const base_option &option);
	inline void set_option(const grouping_option &option);
	inline void set_option(const byte_order_option &option);
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
inline standard::size_t printed_value_width_for_base_and_grouping(base_t base, standard::size_t grouping);
inline standard::size_t calculate_optimal_column_count(standard::size_t max_column_count);
inline standard::size_t calculate_column_count(standard::size_t preferred_column_count, standard::size_t stream_width, standard::size_t marker_width, standard::size_t file_line_width, standard::size_t indentation_width, standard::size_t pointer_width, standard::size_t delimiter_width, standard::size_t column_width);

typedef void (*print_chunk_t)(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);
inline print_chunk_t select_print_chunk_function(base_t base, standard::size_t chunk_size, byte_order_t byte_order);
inline void print_binary_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);
inline void print_binary_chunk_reverse(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);
inline void print_hexadecimal_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);
inline void print_hexadecimal_chunk_reverse(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);

template <typename Type_t>
void print_number_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);

template <typename Type_t>
void print_number_chunk_reverse(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);

inline void print_memory_with_display_options(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const memory_display_options_t &options);

}

//
// Implementation

namespace trace_out
{

void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size)
{
	print_memory_with_display_options(stream, file_line, name, memory, size, memory_display_options_t(HEX, 1, current_byte_order(), 0));
}

template <typename Option1_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1)
{
	memory_display_options_t options(HEX, 1, current_byte_order(), 0);
	options.set_option(option1);

	print_memory_with_display_options(stream, file_line, name, memory, size, options);
}

template <typename Option1_t, typename Option2_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1, const Option2_t &option2)
{
	memory_display_options_t options(HEX, 1, current_byte_order(), 0);
	options.set_option(option1);
	options.set_option(option2);

	print_memory_with_display_options(stream, file_line, name, memory, size, options);
}

template <typename Option1_t, typename Option2_t, typename Option3_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1, const Option2_t &option2, const Option3_t &option3)
{
	memory_display_options_t options(HEX, 1, current_byte_order(), 0);
	options.set_option(option1);
	options.set_option(option2);
	options.set_option(option3);

	print_memory_with_display_options(stream, file_line, name, memory, size, options);
}

template <typename Option1_t, typename Option2_t, typename Option3_t, typename Option4_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1, const Option2_t &option2, const Option3_t &option3, const Option4_t &option4)
{
	memory_display_options_t options(HEX, 1, current_byte_order(), 0);
	options.set_option(option1);
	options.set_option(option2);
	options.set_option(option3);
	options.set_option(option4);

	print_memory_with_display_options(stream, file_line, name, memory, size, options);
}

void print_memory_with_display_options(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const memory_display_options_t &options)
{
	print_chunk_t print_chunk = select_print_chunk_function(options.base, options.grouping, options.byte_order);

	standard::size_t column_width = printed_value_width_for_base_and_grouping(options.base, options.grouping) + 1;
	standard::size_t item_count = size / options.grouping;
	standard::size_t column_count = calculate_column_count(options.column_count, system::console_width(), 0, 0, indentation().size() + INDENTATION_UNIT_WIDTH, to_string(static_cast<const void *>(memory)).size(), 1, column_width);
	standard::size_t line_count = item_count / column_count;
	standard::size_t leftover_item_count = item_count - line_count * column_count;

	standard::size_t memory_line_size = column_count * options.grouping;
	standard::size_t leftover_memory_size = size - item_count * options.grouping;

	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << name << ", " << size << " bytes of " << options.grouping << "-byte " << base_name(options.base);
		if (options.grouping > 1)
		{
			stream << ", " << byte_order_name(options.byte_order);
		}

		indentation_add();

		for (standard::size_t line_number = 0; line_number < line_count; ++line_number)
		{
			const standard::uint8_t *line = &memory[line_number * memory_line_size];

			stream << '\n' << CONTINUE_PARAGRAPH;
			stream << std::hex << reinterpret_cast<standard::uint64_t>(line) << RESET_FLAGS << ':';
			for (standard::size_t current_column = 0; current_column < column_count; ++current_column)
			{
				print_chunk(stream, &line[current_column * options.grouping], options.grouping, column_width);
			}
		}

		if (leftover_item_count > 0)
		{
			const standard::uint8_t *line = &memory[line_count * memory_line_size];

			stream << '\n' << CONTINUE_PARAGRAPH;
			stream << std::hex << reinterpret_cast<standard::uint64_t>(line) << RESET_FLAGS << ':';
			for (standard::size_t current_column = 0; current_column < leftover_item_count; ++current_column)
			{
				print_chunk(stream, &line[current_column * options.grouping], options.grouping, column_width);
			}
		}

		if (leftover_memory_size > 0)
		{
			const standard::uint8_t *line = &memory[size - leftover_memory_size];

			stream << '\n' << SEPARATE_PARAGRAPH << '\n' << CONTINUE_PARAGRAPH << "leftovers:" << '\n' << CONTINUE_PARAGRAPH;
			stream << std::hex << reinterpret_cast<standard::uint64_t>(line) << RESET_FLAGS << ':';
			for (standard::size_t current_column = 0; current_column < leftover_memory_size; ++current_column)
			{
				print_hexadecimal_chunk(stream, &line[current_column], 1, 3);
			}
		}

		indentation_remove();

		stream << '\n' << SEPARATE_PARAGRAPH << '\n';
	}
}

base_option::base_option(base_t value)
	:
	value(value)
{
}

grouping_option::grouping_option(standard::size_t value)
	:
	value(value)
{
}

byte_order_option::byte_order_option(byte_order_t value)
	:
	value(value)
{
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

void memory_display_options_t::set_option(const base_option &option)
{
	base = option.value;

	switch (base)
	{
		case FLT:
			grouping = sizeof(float);
			break;

		case DBL:
			grouping = sizeof(double);
			break;

		case LDBL:
			grouping = sizeof(long double);
			break;

		default:
			break;
	};
}

void memory_display_options_t::set_option(const grouping_option &option)
{
	grouping = option.value;
}

void memory_display_options_t::set_option(const byte_order_option &option)
{
	byte_order = option.value;
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

standard::size_t printed_value_width_for_base_and_grouping(base_t base, standard::size_t grouping)
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

standard::size_t calculate_optimal_column_count(standard::size_t max_column_count)
{
	standard::size_t power_of_2 = 1;
	while (power_of_2 << 1 <= max_column_count)
	{
		power_of_2 <<= 1;
	}

	return power_of_2;
}

standard::size_t calculate_column_count(standard::size_t preferred_column_count, standard::size_t stream_width, standard::size_t marker_width, standard::size_t file_line_width, standard::size_t indentation_width, standard::size_t pointer_width, standard::size_t delimiter_width, standard::size_t column_width)
{
	standard::size_t width_left = stream_width - (marker_width + file_line_width + indentation_width + pointer_width + delimiter_width);
	standard::size_t max_column_count = width_left / column_width;
	if (max_column_count == 0)
	{
		max_column_count = 1;
	}

	if (preferred_column_count == 0 || preferred_column_count > max_column_count)
	{
		return calculate_optimal_column_count(max_column_count);
	}

	return preferred_column_count;
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
			return byte_order == current_byte_order() ? print_binary_chunk : print_binary_chunk_reverse;

		case HEX:
			return byte_order == current_byte_order() ? print_hexadecimal_chunk : print_hexadecimal_chunk_reverse;

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

void print_binary_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width)
{
	stream << std::setw((column_width % 8) + 8) << std::setfill(' ') << byte_to_binary(*chunk) << RESET_FLAGS;
	const standard::uint8_t *end = chunk + size;
	for (++chunk; chunk < end; ++chunk)
	{
		stream << byte_to_binary(*chunk);
	}
}

void print_binary_chunk_reverse(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width)
{
	standard::uint8_t reversed_chunk[16];
	std::reverse_copy(chunk, chunk + size, reversed_chunk);
	print_binary_chunk(stream, reversed_chunk, size, column_width);
}

void print_hexadecimal_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width)
{
	stream << std::setw((column_width % 2) + 2) << std::setfill(' ') << byte_to_hexadecimal(*chunk) << RESET_FLAGS;
	const standard::uint8_t *end = chunk + size;
	for (++chunk; chunk < end; ++chunk)
	{
		stream << byte_to_hexadecimal(*chunk);
	}
}

void print_hexadecimal_chunk_reverse(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width)
{
	standard::uint8_t reversed_chunk[16];
	std::reverse_copy(chunk, chunk + size, reversed_chunk);
	print_hexadecimal_chunk(stream, reversed_chunk, size, column_width);
}

template <typename Type_t>
void print_number_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t, standard::size_t column_width)
{
	Type_t number = *reinterpret_cast<const Type_t *>(chunk);
	typename printable_number_t<Type_t>::type printable_number = number;
	stream << std::setw(column_width) << std::setfill(' ') << std::setprecision(std::numeric_limits<Type_t>::digits10) << printable_number << RESET_FLAGS;
}

template <typename Type_t>
void print_number_chunk_reverse(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width)
{
	standard::uint8_t reversed_chunk[16];
	std::reverse_copy(chunk, chunk + size, reversed_chunk);
	print_number_chunk<Type_t>(stream, reversed_chunk, size, column_width);
}

}
