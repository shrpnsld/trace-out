#pragma once

#include <limits>
#include <string>
#include <sstream>

#include "trace-out/standard/integer.hpp"
#include "trace-out/stuff/stuff.hpp"
#include "trace-out/pretty-printing/out-stream.hpp"


namespace trace_out
{

	enum base_t
	{
		BIN,
		SDEC,
		UDEC,
		HEX,
		FLT,
		DBL,
		LDBL
	};

	enum endianness_t
	{
		BIG,
		LITTLE
	};
}


namespace trace_out { namespace detail
{

	struct memory_display_options_t
	{
		struct nothing {};

		memory_display_options_t(standard::size_t column_count, base_t base, endianness_t endianness);

		void set_option(standard::size_t value);
		void set_option(base_t value);
		void set_option(endianness_t value);
		void set_option(nothing);

		standard::size_t column_count;
		base_t base;
		endianness_t endianness;
	};

	typedef std::streamsize outputwidth_t;


	enum typefamily_t
	{
		TYPE_FAMILY_INTEGER,
		TYPE_FAMILY_FLOATING_POINT,
		TYPE_FAMILY_OTHER
	};


	template <typename Type_t>
	struct type_family
	{
		enum
		{
			value = std::numeric_limits<Type_t>::is_integer ? TYPE_FAMILY_INTEGER : (std::numeric_limits<Type_t>::is_specialized ? TYPE_FAMILY_FLOATING_POINT : TYPE_FAMILY_OTHER)
		};
	};


	template <typefamily_t Family, standard::size_t Size, bool IsSigned>
	struct print_traits_details
	{
		typedef standard::uint8_t unit_t;
		static const outputwidth_t field_width = 2;
		static const base_t default_base = HEX;
		typedef void signed_t;
		typedef void unsigned_t;
	};

#define TRACE_OUT__DEFINE_PRINT_TRAITS(family, type_size, is_signed, unit_type, field_width_value, default_base_value, to_signed_type, to_unsigned_type) \
		template <> \
		struct print_traits_details<family, type_size, is_signed> \
		{ \
			typedef unit_type unit_t; \
			static const outputwidth_t field_width = field_width_value; \
			static const base_t default_base = default_base_value; \
			typedef to_signed_type signed_t; \
			typedef to_unsigned_type unsigned_t; \
		}

	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_INTEGER, 1, true, standard::int8_t, 4, HEX, standard::int8_t, standard::uint8_t);
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_INTEGER, 2, true, standard::int16_t, 6, SDEC, standard::int16_t, standard::uint16_t);
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_INTEGER, 4, true, standard::int32_t, 11, SDEC, standard::int32_t, standard::uint32_t);
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_INTEGER, 8, true, standard::int64_t, 21, SDEC, standard::int64_t, standard::uint64_t);

	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_INTEGER, 1, false, standard::uint8_t, 3, HEX, standard::int8_t, standard::uint8_t);
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_INTEGER, 2, false, standard::uint16_t, 5, UDEC, standard::int16_t, standard::uint16_t);
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_INTEGER, 4, false, standard::uint32_t, 10, UDEC, standard::int32_t, standard::uint32_t);
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_INTEGER, 8, false, standard::uint64_t, 20, UDEC, standard::int64_t, standard::uint64_t);

	// sign + first_digit + point + precision + 'e' + exponent_sign + exponent
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_FLOATING_POINT, 4, true, float, 1 + 1 + 1 + std::numeric_limits<float>::digits10 + 1 + 1 + 3, FLT, float, float);
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_FLOATING_POINT, 8, true, double, 1 + 1 + 1 + std::numeric_limits<float>::digits10 + 1 + 1 + 4, DBL, double, double);
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_FLOATING_POINT, 10, true, long double, 1 + 1 + 1 + std::numeric_limits<float>::digits10 + 1 + 1 + 5, LDBL, long double, long double);
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_FLOATING_POINT, 12, true, long double, 1 + 1 + 1 + std::numeric_limits<float>::digits10 + 1 + 1 + 5, LDBL, long double, long double);
	TRACE_OUT__DEFINE_PRINT_TRAITS(TYPE_FAMILY_FLOATING_POINT, 16, true, long double, 1 + 1 + 1 + std::numeric_limits<float>::digits10 + 1 + 1 + 5, LDBL, long double, long double);

#undef TRACE_OUT__DEFINE_PRINT_TRAITS


	template <typename Type_t>
	struct print_traits :
		public print_traits_details<static_cast<typefamily_t>(type_family<Type_t>::value), sizeof(Type_t), std::numeric_limits<Type_t>::is_signed>
	{
	};


	class is_column_start_t
	{
	public:
		virtual bool operator ()(standard::size_t index) const = 0;
	};


	class check_column_start_t
		:
		public is_column_start_t
	{
	public:
		check_column_start_t(standard::size_t columns);

		bool operator ()(standard::size_t index) const;

	private:
		standard::size_t _columns;
	};


	class ignore_column_start_t
		:
		public is_column_start_t
	{
	public:
		bool operator ()(standard::size_t index) const;
	};


	const char *base_option_name(base_t value);
	const char *endianness_option_name(endianness_t value);
	const char *byte_to_binary(standard::uint8_t byte);
	const char *byte_to_hexadecimal(standard::uint8_t byte);

	template <typename Type_t>
	outputwidth_t field_width(base_t base);

	template <typename Type_t>
	const std::string bytes_to_binary_string(Type_t value);

	template <typename Type_t>
	const std::string bytes_to_signed_decimal_string(Type_t value);

	template <typename Type_t>
	const std::string bytes_to_unsigned_decimal_string(Type_t value);

	template <typename Type_t>
	const std::string bytes_to_floating_point_string(Type_t value);

	template <typename Type_t>
	const std::string bytes_to_hexadecimal_string(Type_t value);

	template <typename Type_t>
	const std::string (*select_conversion(base_t base))(Type_t);

	endianness_t current_byte_order();
	void do_not_reverse_bytes(void *destination, const void *source, standard::size_t size);
	void reverse_bytes(void *destination, const void *source, standard::size_t size);
	void (*select_byte_ordering_function(endianness_t byte_order))(void *, const void *, standard::size_t);

	template <typename Type_t>
	void print_memory_content(out_stream &stream, const Type_t *pointer, standard::size_t size, outputwidth_t column_width, const is_column_start_t &is_column_start, const std::string (*bytes_to_string)(Type_t), void (*order_bytes)(void *, const void *, standard::size_t));

	template <typename Type_t>
	void print_memory_impl(const std::string &filename_line, const char *name, const Type_t *pointer, standard::size_t size, memory_display_options_t options);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	outputwidth_t field_width(base_t base)
	{
		switch (base)
		{
			case BIN:
				return sizeof(typename print_traits<Type_t>::unit_t) * 8;

			case SDEC:
				return print_traits<Type_t>::field_width + (!std::numeric_limits<Type_t>::is_signed ? 1 : 0);

			case UDEC:
				return print_traits<Type_t>::field_width - (std::numeric_limits<Type_t>::is_signed ? 1 : 0);

			case FLT:
			case DBL:
			case LDBL:
				return print_traits<Type_t>::field_width;

			case HEX:
			default:
				return sizeof(typename print_traits<Type_t>::unit_t) * 2;
		}
	}


	template <typename Type_t>
	const std::string bytes_to_binary_string(Type_t value)
	{
		std::stringstream stream;
		standard::uint8_t *data = reinterpret_cast<standard::uint8_t *>(&value);
		for (standard::size_t index = 0; index < sizeof(value); ++index)
		{
			stream << byte_to_binary(data[index]);
		}

		return stream.str();
	}


	template <typename Type_t>
	const std::string bytes_to_signed_decimal_string(Type_t value)
	{
		typedef typename print_traits<Type_t>::signed_t signed_promotion_t;

		signed_promotion_t signed_value = static_cast<signed_promotion_t>(value);
		standard::int64_t signed_integer = static_cast<standard::int64_t>(signed_value);

		return to_string(signed_integer);
	}


	template <typename Type_t>
	const std::string bytes_to_unsigned_decimal_string(Type_t value)
	{
		typedef typename print_traits<Type_t>::unsigned_t unsigned_promotion_t;

		unsigned_promotion_t unsigned_value = static_cast<unsigned_promotion_t>(value);
		standard::uint64_t unsigned_integer = static_cast<standard::uint64_t>(unsigned_value);

		return to_string(unsigned_integer);
	}


	template <typename Type_t>
	const std::string bytes_to_floating_point_string(Type_t value)
	{
		std::stringstream stream;
		stream.precision(std::numeric_limits<Type_t>::digits10);
		stream << std::scientific << value;

		return stream.str();
	}


	template <typename Type_t>
	const std::string bytes_to_hexadecimal_string(Type_t value)
	{
		std::stringstream stream;
		standard::uint8_t *data = reinterpret_cast<standard::uint8_t *>(&value);
		for (standard::size_t index = 0; index < sizeof(value); ++index)
		{
			stream << byte_to_hexadecimal(data[index]);
		}

		return stream.str();
	}


	template <typename Type_t>
	const std::string (*select_conversion(base_t base))(Type_t)
	{
		switch (base)
		{
			case BIN:
				return bytes_to_binary_string<Type_t>;

			case SDEC:
				return bytes_to_signed_decimal_string<Type_t>;

			case UDEC:
				return bytes_to_unsigned_decimal_string<Type_t>;

			case FLT:
			case DBL:
			case LDBL:
				return bytes_to_floating_point_string<Type_t>;

			case HEX:
			default:
				return bytes_to_hexadecimal_string<Type_t>;
		}
	}


	template <typename Type_t>
	void print_memory_content(out_stream &stream, const Type_t *pointer, standard::size_t size, outputwidth_t column_width, const is_column_start_t &is_column_start, const std::string (*bytes_to_string)(Type_t), void (*order_bytes)(void *, const void *, standard::size_t))
	{
		std::stringstream string_stream;

		standard::size_t length = size / sizeof(Type_t);

		stream << make_pretty(static_cast<const void *>(pointer)) << ":";
		for (standard::size_t index = 0; index < length; ++index)
		{
			const std::string string_representation = string_stream.str();
			if (string_representation.length() + static_cast<standard::size_t>(column_width) + 1 > stream.width_left() || is_column_start(index))
			{
				stream << string_representation;
				string_stream.str("");

				stream << NEWLINE << make_pretty(static_cast<const void *>(&pointer[index])) << ":";
			}

			const Type_t &bytes = pointer[index];

			crash_on_bad_memory(bytes);

			Type_t ordered_bytes;
			order_bytes(&ordered_bytes, &bytes, sizeof(Type_t));

			string_stream << " ";
			string_stream.fill(' ');
			string_stream.width(column_width);
			string_stream.flags(std::ios::right);

			string_stream << bytes_to_string(ordered_bytes);
		}

		const std::string string_representation = string_stream.str();
		if (!string_representation.empty())
		{
			stream << string_representation << NEWLINE;
		}
	}


	template <typename Type_t>
	void print_memory_impl(const std::string &filename_line, const char *name, const Type_t *pointer, standard::size_t size, memory_display_options_t options)
	{
		typedef typename print_traits<Type_t>::unit_t unit_t;

		const char *base_name = base_option_name(options.base);
		const char *byte_order_name = endianness_option_name(options.endianness);

		out_stream stream(filename_line);
		stream << name << ", " << to_string(size) << " bytes; " << base_name << ", " << byte_order_name;
		indentation_add();
		stream << NEWLINE;

		const std::string (*bytes_to_string_function)(Type_t) = select_conversion<Type_t>(options.base);
		outputwidth_t column_width = field_width<Type_t>(options.base);

		standard::size_t max_column_count = (stream.width_left() - (to_string(static_cast<void *>(0), std::hex, std::showbase, NULL).size() + 1)) / (1 + column_width);
		bool use_custom_column_count = options.column_count > 0 && options.column_count < max_column_count;
		const is_column_start_t &is_column_start = use_custom_column_count ? static_cast<const is_column_start_t &>(check_column_start_t(options.column_count)) : static_cast<const is_column_start_t &>(ignore_column_start_t());

		void (*order_bytes)(void *, const void *, standard::size_t) = select_byte_ordering_function(options.endianness);

		print_memory_content(stream, static_cast<const unit_t *>(pointer), size, column_width, is_column_start, bytes_to_string_function, order_bytes);

		indentation_remove();
		stream << ENDLINE;
	}


	template <typename Type_t, typename Option1_t = memory_display_options_t::nothing, typename Option2_t = memory_display_options_t::nothing, typename Option3_t = memory_display_options_t::nothing>
	void print_memory(const std::string &filename_line, const char *name, const Type_t *pointer, standard::size_t size, Option1_t option1 = Option1_t(), Option2_t option2 = Option2_t(), Option3_t option3 = Option3_t())
	{
		memory_display_options_t options(0, print_traits<Type_t>::default_base, current_byte_order());
		options.set_option(option1);
		options.set_option(option2);
		options.set_option(option3);

		print_memory_impl(filename_line, name, pointer, size, options);
	}

}
}

