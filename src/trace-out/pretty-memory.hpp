#pragma once

#include "trace-out/base-conversions.hpp"
#include "trace-out/byte-order.hpp"
#include "trace-out/indentation.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/console.hpp"
#include "trace-out/mutex.hpp"
#include "trace-out/nothing.hpp"
#include "trace-out/number-format.hpp"
#include "trace-out/pretty-lines.hpp"
#include "trace-out/to-string.hpp"
#include <algorithm>
#include <cctype>
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

static const standard::size_t MEMORY_MAX_DEFAULT_STREAM_WIDTH = 80;
static const standard::size_t MEMORY_MAX_DEFAULT_COLUMN_COUNT = 16;
static const char MEMORY_VALUE_AND_TEXT_DELIMITER[] = "  ";
static const standard::size_t MEMORY_VALUE_AND_TEXT_DELIMITER_WIDTH = (sizeof(MEMORY_VALUE_AND_TEXT_DELIMITER) - 1) / sizeof(MEMORY_VALUE_AND_TEXT_DELIMITER[0]);

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
	inline explicit byte_order_option(byte_order_t::enumeration value);

	byte_order_t::enumeration value;
};

struct column_count_option
{
	inline explicit column_count_option(standard::size_t value);

	standard::size_t value;
};

struct memory_display_options_t
{
	inline memory_display_options_t(base_t base, standard::size_t grouping, byte_order_t::enumeration byte_order, standard::size_t column_count);

	inline void set_option(const base_option &option);
	inline void set_option(const grouping_option &option);
	inline void set_option(const byte_order_option &option);
	inline void set_option(const column_count_option &option);
	inline void set_option(nothing);

	base_t base;
	standard::size_t grouping;
	byte_order_t::enumeration byte_order;
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

inline const char *base_name(base_t value);
inline const char *byte_order_name(byte_order_t::enumeration byte_order, base_t base, standard::size_t grouping);
inline standard::size_t printed_value_width_for_base_and_grouping(base_t base, standard::size_t grouping);
inline standard::size_t closest_power_of_2(standard::size_t max_column_count);
inline standard::size_t calculate_optimal_column_count(standard::size_t preferred_column_count, standard::size_t stream_width, standard::size_t marker_width, standard::size_t file_line_width, standard::size_t indentation_width, standard::size_t pointer_width, standard::size_t delimiter_width, standard::size_t grouping, standard::size_t column_width);

typedef void (*print_chunk_t)(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);
inline print_chunk_t select_print_chunk_function(base_t base, standard::size_t chunk_size, byte_order_t::enumeration byte_order);
inline void print_binary_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);
inline void print_binary_chunk_reverse(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);
inline void print_hexadecimal_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);
inline void print_hexadecimal_chunk_reverse(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);

template <typename Type_t>
void print_number_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);

template <typename Type_t>
void print_number_chunk_reverse(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width);

inline void print_memory_with_display_options(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const memory_display_options_t &options);

inline void print_memory_values(std::ostream &stream, print_chunk_t print_chunk, const standard::uint8_t *line, standard::size_t column_count, standard::size_t grouping, standard::size_t column_width);
inline void print_text_representation(std::ostream &stream, const standard::uint8_t *line, standard::size_t char_count);

}

//
// Implementation

namespace trace_out
{

void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size)
{
	print_memory_with_display_options(stream, file_line, name, memory, size, memory_display_options_t(HEX, 1, byte_order_t::NOT_SPECIFIED, 0));
}

template <typename Option1_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1)
{
	memory_display_options_t options(HEX, 1, byte_order_t::NOT_SPECIFIED, 0);
	options.set_option(option1);

	print_memory_with_display_options(stream, file_line, name, memory, size, options);
}

template <typename Option1_t, typename Option2_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1, const Option2_t &option2)
{
	memory_display_options_t options(HEX, 1, byte_order_t::NOT_SPECIFIED, 0);
	options.set_option(option1);
	options.set_option(option2);

	print_memory_with_display_options(stream, file_line, name, memory, size, options);
}

template <typename Option1_t, typename Option2_t, typename Option3_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1, const Option2_t &option2, const Option3_t &option3)
{
	memory_display_options_t options(HEX, 1, byte_order_t::NOT_SPECIFIED, 0);
	options.set_option(option1);
	options.set_option(option2);
	options.set_option(option3);

	print_memory_with_display_options(stream, file_line, name, memory, size, options);
}

template <typename Option1_t, typename Option2_t, typename Option3_t, typename Option4_t>
void print_memory(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const Option1_t &option1, const Option2_t &option2, const Option3_t &option3, const Option4_t &option4)
{
	memory_display_options_t options(HEX, 1, byte_order_t::NOT_SPECIFIED, 0);
	options.set_option(option1);
	options.set_option(option2);
	options.set_option(option3);
	options.set_option(option4);

	print_memory_with_display_options(stream, file_line, name, memory, size, options);
}

void print_memory_with_display_options(std::ostream &stream, const file_line_t &file_line, const char *name, const standard::uint8_t *memory, standard::size_t size, const memory_display_options_t &options)
{
	print_chunk_t print_chunk = select_print_chunk_function(options.base, options.grouping, options.byte_order);
	standard::size_t pointer_width = to_string(reinterpret_cast<standard::uint64_t>(memory), std::hex).size();
	standard::size_t column_width = printed_value_width_for_base_and_grouping(options.base, options.grouping) + 1;
	standard::size_t item_count = size / options.grouping;
	standard::size_t column_count = calculate_optimal_column_count(options.column_count, system::console_width(), 0, 0, indentation().size() + INDENTATION_UNIT_WIDTH, pointer_width, 1, options.grouping, column_width);
	standard::size_t line_count = item_count / column_count;
	standard::size_t leftover_item_count = item_count - line_count * column_count;

	standard::size_t memory_line_size = column_count * options.grouping;
	standard::size_t leftover_memory_size = size - item_count * options.grouping;

	{
#if defined(TRACE_OUT_SYNC_STREAM)
		autolock<system::mutex> lock(stream_mutex());
#endif

		stream << THREAD_INFO << NEW_PARAGRAPH(file_line) << name << ", " << size << " bytes of " << options.grouping << "-byte " << base_name(options.base);
		const char *byte_order_str = byte_order_name(options.byte_order, options.base, options.grouping);
		if (byte_order_str != NULL)
		{
			stream << ", " << byte_order_str;
		}

		indentation_add();

		for (standard::size_t line_number = 0; line_number < line_count; ++line_number)
		{
			const standard::uint8_t *line = &memory[line_number * memory_line_size];

			stream << '\n' << CONTINUE_PARAGRAPH;
			stream << std::hex << reinterpret_cast<standard::uint64_t>(line) << RESET_FLAGS << ':';
			print_memory_values(stream, print_chunk, line, column_count, options.grouping, column_width);
			stream << MEMORY_VALUE_AND_TEXT_DELIMITER;
			print_text_representation(stream, line, column_count * options.grouping);
		}

		if (leftover_item_count > 0)
		{
			const standard::uint8_t *line = &memory[line_count * memory_line_size];
			int padding_width = static_cast<int>((column_count - leftover_item_count) * column_width);

			stream << '\n' << CONTINUE_PARAGRAPH;
			stream << std::hex << reinterpret_cast<standard::uint64_t>(line) << RESET_FLAGS << ':';
			print_memory_values(stream, print_chunk, line, leftover_item_count, options.grouping, column_width);
			stream << std::setw(padding_width) << "" << MEMORY_VALUE_AND_TEXT_DELIMITER;
			print_text_representation(stream, line, leftover_item_count * options.grouping);
		}

		if (leftover_memory_size > 0)
		{
			const standard::uint8_t *line = &memory[size - leftover_memory_size];
			int padding_width = static_cast<int>((column_count * column_width) - (leftover_memory_size * 3));

			stream << '\n' << SEPARATE_PARAGRAPH << '\n' << CONTINUE_PARAGRAPH << "leftovers:" << '\n' << CONTINUE_PARAGRAPH;
			stream << std::hex << reinterpret_cast<standard::uint64_t>(line) << RESET_FLAGS << ':';
			print_memory_values(stream, print_hexadecimal_chunk, line, leftover_memory_size, 1, 3);
			stream << std::setw(padding_width) << "" << MEMORY_VALUE_AND_TEXT_DELIMITER;
			print_text_representation(stream, line, leftover_memory_size);
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

byte_order_option::byte_order_option(byte_order_t::enumeration value)
	:
	value(value)
{
}

column_count_option::column_count_option(standard::size_t value)
	:
	value(value)
{
}

memory_display_options_t::memory_display_options_t(base_t base, standard::size_t grouping, byte_order_t::enumeration byte_order, standard::size_t column_count)
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
			grouping = number_format<float>::size();
			break;

		case DBL:
			grouping = number_format<double>::size();
			break;

		case LDBL:
			grouping = number_format<long double>::size();
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

const char *byte_order_name(byte_order_t::enumeration byte_order, base_t base, standard::size_t grouping)
{
	if (grouping == 1)
	{
		return NULL;
	}

	if (byte_order == byte_order_t::NOT_SPECIFIED && base != BIN && base != HEX)
	{
		byte_order = byte_order_t::current();
	}

	switch (byte_order)
	{
		case byte_order_t::LITTLE:
			return "little-endian";

		case byte_order_t::BIG:
			return "big-endian";

		case byte_order_t::NOT_SPECIFIED:
			return NULL;
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

standard::size_t closest_power_of_2(standard::size_t max_column_count)
{
	standard::size_t power_of_2 = 1;
	while (power_of_2 << 1 <= max_column_count)
	{
		power_of_2 <<= 1;
	}

	return power_of_2;
}

standard::size_t calculate_optimal_column_count(standard::size_t preferred_column_count, standard::size_t stream_width, standard::size_t marker_width, standard::size_t file_line_width, standard::size_t indentation_width, standard::size_t pointer_width, standard::size_t delimiter_width, standard::size_t grouping, standard::size_t column_width)
{
	if (preferred_column_count > 0)
	{
		return preferred_column_count;
	}

	if (stream_width > MEMORY_MAX_DEFAULT_STREAM_WIDTH)
	{
		stream_width = MEMORY_MAX_DEFAULT_STREAM_WIDTH;
	}

	standard::size_t width_left = stream_width - (marker_width + file_line_width + indentation_width + pointer_width + delimiter_width + MEMORY_VALUE_AND_TEXT_DELIMITER_WIDTH);
	standard::size_t column_count = width_left / (column_width + grouping);
	if (column_count == 0)
	{
		return 1;
	}

	if (column_count > MEMORY_MAX_DEFAULT_COLUMN_COUNT)
	{
		return MEMORY_MAX_DEFAULT_COLUMN_COUNT;
	}

	return closest_power_of_2(column_count);
}

print_chunk_t select_print_chunk_function(base_t base, standard::size_t chunk_size, byte_order_t::enumeration byte_order)
{
	switch (base)
	{
		case BIN:
			return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_binary_chunk : print_binary_chunk_reverse;

		case HEX:
			return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_hexadecimal_chunk : print_hexadecimal_chunk_reverse;

		case SDEC:
		{
			switch (chunk_size)
			{
				case 1:
					return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<standard::int8_t> : print_number_chunk_reverse<standard::int8_t>;

				case 2:
					return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<standard::int16_t> : print_number_chunk_reverse<standard::int16_t>;

				case 4:
					return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<standard::int32_t> : print_number_chunk_reverse<standard::int32_t>;

				case 8:
					return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<standard::int64_t> : print_number_chunk_reverse<standard::int64_t>;

				default:
					return NULL;
			}
		}

		case UDEC:
			switch (chunk_size)
			{
				case 1:
					return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<standard::uint8_t> : print_number_chunk_reverse<standard::uint8_t>;

				case 2:
					return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<standard::uint16_t> : print_number_chunk_reverse<standard::uint16_t>;

				case 4:
					return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<standard::uint32_t> : print_number_chunk_reverse<standard::uint32_t>;

				case 8:
					return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<standard::uint64_t> : print_number_chunk_reverse<standard::uint64_t>;

				default:
					return NULL;
			}

		case FLT:
			return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<float> : print_number_chunk_reverse<float>;

		case DBL:
			return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<double> : print_number_chunk_reverse<double>;

		case LDBL:
			return byte_order == byte_order_t::current() || byte_order == byte_order_t::NOT_SPECIFIED ? print_number_chunk<long double> : print_number_chunk_reverse<long double>;
	}
}

void print_binary_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t /*column_width*/)
{
	stream << ' ';
	const standard::uint8_t *end = chunk + size;
	for ( ; chunk < end; ++chunk)
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

void print_hexadecimal_chunk(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t /*column_width*/)
{
	stream << ' ';
	const standard::uint8_t *end = chunk + size;
	for ( ; chunk < end; ++chunk)
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
	stream << std::setw(static_cast<int>(column_width)) << std::setfill(' ') << std::setprecision(std::numeric_limits<Type_t>::digits10) << printable_number << RESET_FLAGS;
}

template <typename Type_t>
void print_number_chunk_reverse(std::ostream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t column_width)
{
	standard::uint8_t reversed_chunk[16];
	std::reverse_copy(chunk, chunk + size, reversed_chunk);
	print_number_chunk<Type_t>(stream, reversed_chunk, size, column_width);
}

void print_memory_values(std::ostream &stream, print_chunk_t print_chunk, const standard::uint8_t *line, standard::size_t column_count, standard::size_t grouping, standard::size_t column_width)
{
	for (standard::size_t column = 0; column < column_count; ++column)
	{
		print_chunk(stream, &line[column * grouping], grouping, column_width);
	}
}

void print_text_representation(std::ostream &stream, const standard::uint8_t *line, standard::size_t char_count)
{
	for (standard::size_t index = 0; index < char_count; ++index)
	{
		char character = line[index];
		stream << (std::isprint(character) ? character : '.');
	}
}

}
