#pragma once

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include "trace-out/standard/integer.hpp"
#include "trace-out/stuff/stuff.hpp"
#include "trace-out/pretty-printing/out-stream.hpp"


#define $bin trace_out::detail::bin_or_hex_option(trace_out::detail::BIN)
#define $hex trace_out::detail::bin_or_hex_option(trace_out::detail::HEX)
#define $sdec trace_out::detail::decimal_option(trace_out::detail::SDEC)
#define $udec trace_out::detail::decimal_option(trace_out::detail::UDEC)
#define $flt trace_out::detail::floating_point_option(trace_out::detail::FLT)
#define $dbl trace_out::detail::floating_point_option(trace_out::detail::DBL)
#define $ldbl trace_out::detail::floating_point_option(trace_out::detail::LDBL)

#define $be trace_out::detail::BIG
#define $le trace_out::detail::LITTLE

#define $col(value) trace_out::detail::column_count_option(value)


namespace trace_out { namespace detail
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
		bin_or_hex_option(base_t base);

		const bin_or_hex_option &operator ()(standard::size_t new_grouping);

		base_t base;
		standard::size_t grouping;
	};


	struct decimal_option
	{
		decimal_option(base_t base);

		const decimal_option &operator ()(standard::size_t new_grouping);
		const decimal_option &operator ()(byte_order_t byte_order);
		const decimal_option &operator ()(byte_order_t byte_order, standard::size_t new_grouping);
		const decimal_option &operator ()(standard::size_t new_grouping, byte_order_t byte_order);

		base_t base;
		standard::size_t grouping;
		byte_order_t byte_order;
	};


	struct floating_point_option
	{
		floating_point_option(base_t base);

		const floating_point_option &operator ()(byte_order_t new_byte_order);

		static standard::size_t grouping_from_base(base_t base);

		base_t base;
		standard::size_t grouping;
		byte_order_t byte_order;
	};


	struct column_count_option
	{
		column_count_option(standard::size_t value);

		standard::size_t value;
	};


	struct memory_display_options_t
	{
		struct nothing {};

		memory_display_options_t(base_t base, standard::size_t grouping, byte_order_t byte_order, standard::size_t column_count);

		void set_option(const bin_or_hex_option &option);
		void set_option(const decimal_option &option);
		void set_option(const floating_point_option &option);
		void set_option(const column_count_option &option);
		void set_option(nothing);

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


	template <typename Option1_t = nothing, typename Option2_t = nothing>
	void print_memory(const std::string &filename_line, const char *name, const standard::uint8_t *memory, standard::size_t size, Option1_t option1 = Option1_t(), Option2_t option2 = Option2_t());

}
}


namespace trace_out { namespace detail
{

	byte_order_t current_byte_order();
	const char *base_name(base_t value);
	const char *byte_order_name(byte_order_t value);
	standard::size_t field_width_for_base_and_grouping(base_t base, standard::size_t grouping);
	standard::size_t calculate_column_count(standard::size_t requested_column_count, standard::size_t stream_width, standard::size_t indentation_width, standard::size_t pointer_width, standard::size_t delimiter_width, standard::size_t padding_width, standard::size_t field_width);

	typedef void (*print_chunk_t)(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width);
	print_chunk_t select_print_chunk_function(base_t base, standard::size_t chunk_size, byte_order_t byte_order);
	void print_binary_chunk(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width);
	void print_hexadecimal_chunk(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width);

	template <typename Type_t>
	void print_number_chunk(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width);

	template <typename Type_t>
	void print_number_chunk_reverse(out_stream &stream, const standard::uint8_t *chunk, standard::size_t size, standard::size_t field_width);

}
}


namespace trace_out { namespace detail
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
		std::string printed_value = (std::stringstream() << std::setprecision(std::numeric_limits<Type_t>::digits10) << printable_number).str();

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

}
}
