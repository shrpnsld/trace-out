#pragma once

#include "trace-out/base-conversions.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/has-member.hpp"
#include "trace-out/number-bits-iterator.hpp"
#include "trace-out/number-format.hpp"
#include "trace-out/template-magic.hpp"
#include "trace-out/type-traits.hpp"
#include <bitset>
#include <cctype>
#include <iomanip>
#include <string>

#if TRACE_OUT_CPP_VERSION >= 201103L
	#include <memory> // [amalgamate:leave]
	#include <tuple> // [amalgamate:leave]
	#include <type_traits> // [amalgamate:leave]
#endif

#if TRACE_OUT_CPP_VERSION >= 201703L
	#include <optional> // [amalgamate:leave]
	#include <variant> // [amalgamate:leave]
#endif // TRACE_OUT_CPP_VERSION >= 201703L

#if TRACE_OUT_CPP_VERSION >= 202302L
	#include <expected> // [amalgamate:leave]
#endif // TRACE_OUT_CPP_VERSION >= 202302L

//
// Public

namespace trace_out
{

inline void pretty_print(std::ostream &stream, bool value);
inline void pretty_print(std::ostream &stream, char character);
inline void pretty_print(std::ostream &stream, signed char number);
inline void pretty_print(std::ostream &stream, unsigned char number);
inline void pretty_print(std::ostream &stream, signed short number);
inline void pretty_print(std::ostream &stream, unsigned short number);
inline void pretty_print(std::ostream &stream, signed int number);
inline void pretty_print(std::ostream &stream, unsigned int number);
inline void pretty_print(std::ostream &stream, signed long number);
inline void pretty_print(std::ostream &stream, unsigned long number);

#if TRACE_OUT_CPP_VERSION >= 201103L

inline void pretty_print(std::ostream &stream, signed long long number);
inline void pretty_print(std::ostream &stream, unsigned long long number);

template <typename Type_t>
typename enable_if<std::is_enum<Type_t>::value, void>::type pretty_print(std::ostream &stream, Type_t value);

#endif

inline void pretty_print(std::ostream &stream, float number);
inline void pretty_print(std::ostream &stream, double number);
inline void pretty_print(std::ostream &stream, long double number);
inline void pretty_print(std::ostream &stream, const void *pointer);
inline void pretty_print(std::ostream &stream, void *pointer);
inline void pretty_print(std::ostream &stream, const char *string);
inline void pretty_print(std::ostream &stream, const std::string &string);

template <typename Type_t, standard::size_t Size>
void pretty_print(std::ostream &stream, const Type_t (&array)[Size]);

template <typename Type_t>
typename enable_if<is_pointer<Type_t>::value, void>::type pretty_print(std::ostream &stream, Type_t pointer);

template <typename Type_t>
typename enable_if<!is_floating_point<Type_t>::value, void>::type pretty_print_binary(std::ostream &stream, Type_t value);

template <typename Type_t>
typename enable_if<is_floating_point<Type_t>::value, void>::type pretty_print_binary(std::ostream &stream, Type_t value);

template <typename Type_t>
void pretty_print_octal(std::ostream &stream, Type_t value);

template <typename Type_t>
void pretty_print_hexadecimal(std::ostream &stream, Type_t value);

//
// STL types

template <typename First_t, typename Second_t>
void pretty_print(std::ostream &stream, const std::pair<First_t, Second_t> &pair);

template <std::size_t Size>
void pretty_print(std::ostream &stream, const std::bitset<Size> &bits);

#if TRACE_OUT_CPP_VERSION >= 201103L

template <typename Type_t>
void pretty_print(std::ostream &stream, const std::unique_ptr<Type_t> &pointer);

template <typename Type_t>
void pretty_print(std::ostream &stream, const std::shared_ptr<Type_t> &pointer);

template <typename Type_t>
void pretty_print(std::ostream &stream, const std::weak_ptr<Type_t> &pointer);

template <typename ...Types_t>
void pretty_print(std::ostream &stream, const std::tuple<Types_t ...> &tuple);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

#if TRACE_OUT_CPP_VERSION >= 201703L

template <typename Type_t>
void pretty_print(std::ostream &stream, const std::optional<Type_t> &optional);

template <typename ...Types_t>
void pretty_print(std::ostream &stream, const std::variant<Types_t...> &variant);

#endif // TRACE_OUT_CPP_VERSION >= 201703L

#if TRACE_OUT_CPP_VERSION >= 202302L

template <typename Type_t, typename Error_t>
void pretty_print(std::ostream &stream, const std::expected<Type_t, Error_t> &expected);

#endif // TRACE_OUT_CPP_VERSION >= 202302L

//
// .begin(), .end()

template <typename Type_t>
typename enable_if<is_iterable<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &iterable);

//
// Common member combinations

template <typename Type_t>
typename enable_if<has_members_x_y<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point);

template <typename Type_t>
typename enable_if<has_members_X_Y<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point);

template <typename Type_t>
typename enable_if<has_members_x_y_z<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point);

template <typename Type_t>
typename enable_if<has_members_X_Y_Z<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point);

template <typename Type_t>
typename enable_if<has_members_x_y_z_w<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point);

template <typename Type_t>
typename enable_if<has_members_X_Y_Z_W<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point);

template <typename Type_t>
typename enable_if<has_members_width_height<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &size);

template <typename Type_t>
typename enable_if<has_members_Width_Height<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &size);

template <typename Type_t>
typename enable_if<has_members_x_y_width_height<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rectangle);

template <typename Type_t>
typename enable_if<has_members_x_y_Width_Height<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rectangle);

template <typename Type_t>
typename enable_if<has_members_X_Y_Width_Height<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rectangle);

template <typename Type_t>
typename enable_if<has_members_origin_size<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rectangle);

template <typename Type_t>
typename enable_if<has_members_real_imag<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &complex);

//
// WinApi

template <typename Type_t>
typename enable_if<has_members_cx_cy<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &size);

template <typename Type_t>
typename enable_if<has_members_left_top_right_bottom<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rectangle);

//
// Unreal Engine

template <typename Type_t>
typename enable_if<has_members_Key_Value<Type_t>::value, void>::type pretty_print(std::ostream &, const Type_t &);

template <typename Type_t>
typename enable_if<has_members_v1_v2<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &vector_pair);

template <typename Type_t>
typename enable_if<has_members_Origin_Direction<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &ray);

template <typename Type_t>
typename enable_if<has_members_Vertex_Count<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &edge);

template <typename Type_t>
typename enable_if<has_members_Pitch_Roll_Yaw<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rotator);

template <typename Type_t>
typename enable_if<has_members_GetLowerBound_GetUpperBound<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &range);

template <typename Type_t>
typename enable_if<has_members_GetValue_IsExclusive_IsInclusive_IsOpen<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &range);

template <typename Type_t>
typename enable_if<has_members_Min_Max_bIsValid<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &box);

template <typename Type_t>
typename enable_if<has_members_Min_Max_IsValid<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &box);

template <typename Type_t>
typename enable_if<has_members_Center_W<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &sphere);

template <typename Type_t>
typename enable_if<has_members_Center_Radius_Orientation_Length<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &capsule);

template <typename Type_t>
typename enable_if<has_members_Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &box);

template <typename Type_t>
typename enable_if<has_members_Origin_BoxExtent_SphereRadius<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &bounds);

template <typename Type_t>
typename enable_if<has_members_GetCharArray<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &string);

template <typename Type_t>
typename enable_if<
#if TRACE_OUT_CPP_VERSION >= 201103L
	!std::is_enum<Type_t>::value &&
#endif
	!has_supported_members<Type_t>::value &&
	!is_pointer<Type_t>::value &&
	!is_iterable<Type_t>::value,
void>::type pretty_print(std::ostream &stream, const Type_t &);

}

//
// Private

namespace trace_out
{

#if TRACE_OUT_CPP_VERSION >= 201103L

template <standard::size_t Index, typename ...Types_t>
typename enable_if<Index == sizeof_pack<Types_t...>::value - 1, void>::type print_tuple(std::ostream &stream, const std::tuple<Types_t...> &tuple);

template <standard::size_t Index, typename ...Types_t>
typename enable_if<Index < sizeof_pack<Types_t...>::value - 1, void>::type print_tuple(std::ostream &stream, const std::tuple<Types_t...> &tuple);

#endif

template <typename Iterator_t>
void pretty_print_begin_end(std::ostream &stream, Iterator_t begin, Iterator_t end);

template <typename Iterator_t>
void pretty_print_begin_how_much(std::ostream &stream, Iterator_t iterator, standard::size_t how_much);

template <typename Iterator_t>
void print_string(std::ostream &stream, Iterator_t begin, Iterator_t end);

inline number_bits_iterator print_bits(std::ostream &stream, number_bits_iterator iterator, standard::size_t how_much);

template <typename Floating_t>
void pretty_print_floating_in_binary(std::ostream &stream, Floating_t value);

inline const standard::uint8_t *print_bytes_of_number(std::ostream &stream, const standard::uint8_t *iterator, standard::size_t how_much, const char *(*represent)(standard::uint8_t));

}

//
// Implementation

namespace trace_out
{

void pretty_print(std::ostream &stream, bool value)
{
	stream << std::boolalpha << value << std::noboolalpha;
}

void pretty_print(std::ostream &stream, char character)
{
	if (!std::isprint(character))
	{
		stream << "'\\x" << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << (character & 0xff) << '\'';
		stream.flags(static_cast<std::ios_base::fmtflags>(0));
		stream.width(0);
		stream.fill(' ');
		return;
	}

	stream << '\'' << character << '\'';
}

void pretty_print(std::ostream &stream, signed char number)
{
	stream << static_cast<signed int>(number);
}

void pretty_print(std::ostream &stream, unsigned char number)
{
	stream << static_cast<unsigned int>(number);
}

void pretty_print(std::ostream &stream, signed short number)
{
	stream << number;
}

void pretty_print(std::ostream &stream, unsigned short number)
{
	stream << number;
}

void pretty_print(std::ostream &stream, signed int number)
{
	stream << number;
}

void pretty_print(std::ostream &stream, unsigned int number)
{
	stream << number;
}

void pretty_print(std::ostream &stream, signed long number)
{
	stream << number;
}

void pretty_print(std::ostream &stream, unsigned long number)
{
	stream << number;
}

#if TRACE_OUT_CPP_VERSION >= 201103L

void pretty_print(std::ostream &stream, signed long long number)
{
	stream << number;
}

void pretty_print(std::ostream &stream, unsigned long long number)
{
	stream << number;
}

template <typename Type_t>
typename enable_if<std::is_enum<Type_t>::value, void>::type pretty_print(std::ostream &stream, Type_t value)
{
	stream << static_cast<typename std::underlying_type<Type_t>::type>(value);
}

#endif

void pretty_print(std::ostream &stream, float number)
{
	stream << number;
}

void pretty_print(std::ostream &stream, double number)
{
	stream << number;
}

void pretty_print(std::ostream &stream, long double number)
{
	stream << number;
}

void pretty_print(std::ostream &stream, const void *pointer)
{
	if (pointer == NULL)
	{
		stream << "<null>";
	}
	else
	{
		stream << pointer;
	}
}

void pretty_print(std::ostream &stream, void *pointer)
{
	pretty_print(stream, static_cast<const void *>(pointer));
}

void pretty_print(std::ostream &stream, const char *string)
{
	stream << '"' << string << '"';
}

void pretty_print(std::ostream &stream, const std::string &string)
{
	stream << '"' << string << '"';
}

template <typename Type_t, standard::size_t Size>
void pretty_print(std::ostream &stream, const Type_t (&array)[Size])
{
	pretty_print_begin_how_much(stream, array, Size);
}

template <typename Type_t>
typename enable_if<is_pointer<Type_t>::value, void>::type pretty_print(std::ostream &stream, Type_t pointer)
{
	pretty_print(stream, static_cast<const void *>(pointer));
	if (pointer == NULL)
	{
		return;
	}

	stream << " -> ";
	pretty_print(stream, *pointer);
}

template <typename Type_t>
typename enable_if<!is_floating_point<Type_t>::value, void>::type pretty_print_binary(std::ostream &stream, Type_t value)
{
	stream << "bin: ";

	const standard::uint8_t *iterator = first_byte_in_number(value);
	const standard::uint8_t *last = last_byte_in_number(value);
	for ( ; iterator != last; iterator = next_byte_in_number(iterator))
	{
		stream << byte_to_binary(*iterator) << ' ';
	}

	stream << byte_to_binary(*iterator);
}

template <typename Type_t>
typename enable_if<is_floating_point<Type_t>::value, void>::type pretty_print_binary(std::ostream &stream, Type_t value)
{
	pretty_print_floating_in_binary(stream, value);
}

template <typename Type_t>
void pretty_print_octal(std::ostream &stream, Type_t value)
{
	static const standard::size_t GROUPING = 2;

	stream << "oct: ";

	standard::size_t type_size = number_format<Type_t>::size();
	if (type_size == 1)
	{
		stream << byte_to_octal(value);
	}
	else
	{
		standard::size_t left = type_size;
		const standard::uint8_t *iterator = first_byte_in_number(value);
		iterator = print_bytes_of_number(stream, iterator, GROUPING, byte_to_octal);
		left -= GROUPING;
		while (left > 0)
		{
			stream << ' ';
			iterator = print_bytes_of_number(stream, iterator, GROUPING, byte_to_octal);
			left -= GROUPING;
		}
	}
}

template <typename Type_t>
void pretty_print_hexadecimal(std::ostream &stream, Type_t value)
{
	static const standard::size_t GROUPING = 4;

	stream << "hex: ";

	standard::size_t type_size = number_format<Type_t>::size();
	if (type_size == 1)
	{
		stream << byte_to_hexadecimal(value);
	}
	else if (type_size == 2)
	{
		const standard::uint8_t *iterator = first_byte_in_number(value);
		stream << byte_to_hexadecimal(*iterator);
		iterator = next_byte_in_number(iterator);
		stream << byte_to_hexadecimal(*iterator);
	}
	else
	{
		standard::size_t left = type_size;
		const standard::uint8_t *iterator = first_byte_in_number(value);
		if (type_size == 10)
		{
			stream << byte_to_hexadecimal(*iterator);
			iterator = next_byte_in_number(iterator);
			stream << byte_to_hexadecimal(*iterator);
			iterator = next_byte_in_number(iterator);
			stream << ' ';
			left -= 2;
		}

		iterator = print_bytes_of_number(stream, iterator, GROUPING, byte_to_hexadecimal);
		left -= GROUPING;
		while (left > 0)
		{
			stream << ' ';
			iterator = print_bytes_of_number(stream, iterator, GROUPING, byte_to_hexadecimal);
			left -= GROUPING;
		}
	}
}

//
// STL types

template <typename First_t, typename Second_t>
void pretty_print(std::ostream &stream, const std::pair<First_t, Second_t> &pair)
{
	stream << '{';
	pretty_print(stream, pair.first);
	stream << ", ";
	pretty_print(stream, pair.second);
	stream << '}';
}

template <std::size_t Size>
void pretty_print(std::ostream &stream, const std::bitset<Size> &bits)
{
	stream << bits.to_string();
}

#if TRACE_OUT_CPP_VERSION >= 201103L

template <typename Type_t>
void pretty_print(std::ostream &stream, const std::unique_ptr<Type_t> &pointer)
{
	pretty_print(stream, pointer.get());
}

template <typename Type_t>
void pretty_print(std::ostream &stream, const std::shared_ptr<Type_t> &pointer)
{
	pretty_print(stream, reinterpret_cast<const void *>(pointer.get()));
	if (pointer.get() != NULL)
	{
		stream << " (use_count: " << pointer.use_count() << ')';
		stream << " -> ";
		pretty_print(stream, *pointer);
	}
}

template <typename Type_t>
void pretty_print(std::ostream &stream, const std::weak_ptr<Type_t> &pointer)
{
	stream << "(use_count: " << pointer.use_count() << ')';
}

template <standard::size_t Index, typename ...Types_t>
typename enable_if<Index == sizeof_pack<Types_t...>::value - 1, void>::type print_tuple(std::ostream &stream, const std::tuple<Types_t...> &tuple)
{
	pretty_print(stream, std::get<Index>(tuple));
	stream << '}';
}

#if defined(TRACE_OUT_MVS)
#pragma warning(push)
#pragma warning(disable:4296) // "expression is always false"
#endif

template <standard::size_t Index, typename ...Types_t>
typename enable_if<Index < sizeof_pack<Types_t...>::value - 1, void>::type print_tuple(std::ostream &stream, const std::tuple<Types_t...> &tuple)
{
	pretty_print(stream, std::get<Index>(tuple));
	stream << ", ";
	print_tuple<Index + 1>(stream, tuple);
}

#if defined(TRACE_OUT_MVS)
#pragma warning(pop)
#endif

template <typename ...Types_t>
void pretty_print(std::ostream &stream, const std::tuple<Types_t ...> &tuple)
{
	stream << '{';
	print_tuple<0>(stream, tuple);
}

#endif // TRACE_OUT_CPP_VERSION >= 201103L

#if TRACE_OUT_CPP_VERSION >= 201703L

template <typename Type_t>
void pretty_print(std::ostream &stream, const std::optional<Type_t> &optional)
{
	if (!optional.has_value())
	{
		stream << "<empty>";
		return;
	}

	pretty_print(stream, optional.value());
}

template <typename ...Types_t>
void pretty_print(std::ostream &stream, const std::variant<Types_t...> &variant)
{
	std::visit(
		[&stream](const auto &value)
		{
			pretty_print(stream, value);
		},
		variant);
}

#endif // TRACE_OUT_CPP_VERSION >= 201703L

#if TRACE_OUT_CPP_VERSION >= 202302L

template <typename Type_t, typename Error_t>
void pretty_print(std::ostream &stream, const std::expected<Type_t, Error_t> &expected)
{
	if (!expected.has_value())
	{
		pretty_print(stream, expected.error());
		stream << " // error";
		return;
	}

	pretty_print(stream, expected.value());
}

#endif // TRACE_OUT_CPP_VERSION >= 202302L

//
// .begin(), .end()

// Using this to infer type of iterator in a pre C++11 way
template <typename Iterator_t>
void pretty_print_begin_end(std::ostream &stream, Iterator_t begin, Iterator_t end)
{
	// Unreal Engine has only 'operator !=' overloaded for its iterators,
	// and I want this to be an early return
	if (!(begin != end))
	{
		stream << "[]";
		return;
	}

	stream << '[';
	Iterator_t iterator = begin;
	pretty_print(stream, *iterator);
	for (++iterator; iterator != end; ++iterator)
	{
		stream << ", ";
		pretty_print(stream, *iterator);
	}
	stream << ']';
}

template <typename Iterator_t>
void pretty_print_begin_how_much(std::ostream &stream, Iterator_t iterator, standard::size_t how_much)
{
	stream << '[';

	if (how_much > 0)
	{
		pretty_print(stream, *iterator);
		for (++iterator, --how_much; how_much > 0; ++iterator, --how_much)
		{
			stream << ", ";
			pretty_print(stream, *iterator);
		}
	}

	stream << ']';
}

template <typename Type_t>
typename enable_if<is_iterable<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &iterable)
{
	pretty_print_begin_end(stream, iterable.begin(), iterable.end());
}

//
// Common member combinations

template <typename Type_t>
typename enable_if<has_members_x_y<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point)
{
	stream << '{';
	pretty_print(stream, dereference_member(point, &Type_t::x));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::y));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_X_Y<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point)
{
	stream << '{';
	pretty_print(stream, dereference_member(point, &Type_t::X));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::Y));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_x_y_z<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point)
{
	stream << '{';
	pretty_print(stream, dereference_member(point, &Type_t::x));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::y));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::z));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_X_Y_Z<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point)
{
	stream << '{';
	pretty_print(stream, dereference_member(point, &Type_t::X));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::Y));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::Z));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_x_y_z_w<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point)
{
	stream << '{';
	pretty_print(stream, dereference_member(point, &Type_t::x));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::y));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::z));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::w));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_X_Y_Z_W<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &point)
{
	stream << '{';
	pretty_print(stream, dereference_member(point, &Type_t::X));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::Y));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::Z));
	stream << ", ";
	pretty_print(stream, dereference_member(point, &Type_t::W));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_width_height<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &size)
{
	stream << '{';
	pretty_print(stream, dereference_member(size, &Type_t::width));
	stream << " x ";
	pretty_print(stream, dereference_member(size, &Type_t::height));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_Width_Height<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &size)
{
	stream << '{';
	pretty_print(stream, dereference_member(size, &Type_t::Width));
	stream << " x ";
	pretty_print(stream, dereference_member(size, &Type_t::Height));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_x_y_width_height<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rectangle)
{
	stream << '{';
	pretty_print(stream, dereference_member(rectangle, &Type_t::x));
	stream << ", ";
	pretty_print(stream, dereference_member(rectangle, &Type_t::y));
	stream << "} {";
	pretty_print(stream, dereference_member(rectangle, &Type_t::width));
	stream << " x ";
	pretty_print(stream, dereference_member(rectangle, &Type_t::height));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_x_y_Width_Height<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rectangle)
{
	stream << '{';
	pretty_print(stream, dereference_member(rectangle, &Type_t::x));
	stream << ", ";
	pretty_print(stream, dereference_member(rectangle, &Type_t::y));
	stream << "} {";
	pretty_print(stream, dereference_member(rectangle, &Type_t::Width));
	stream << " x ";
	pretty_print(stream, dereference_member(rectangle, &Type_t::Height));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_X_Y_Width_Height<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rectangle)
{
	stream << '{';
	pretty_print(stream, dereference_member(rectangle, &Type_t::X));
	stream << ", ";
	pretty_print(stream, dereference_member(rectangle, &Type_t::Y));
	stream << "} {";
	pretty_print(stream, dereference_member(rectangle, &Type_t::Width));
	stream << " x ";
	pretty_print(stream, dereference_member(rectangle, &Type_t::Height));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_origin_size<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rectangle)
{
	pretty_print(stream, dereference_member(rectangle, &Type_t::origin));
	stream << ' ';
	pretty_print(stream, dereference_member(rectangle, &Type_t::size));
}

template <typename Type_t>
typename enable_if<has_members_real_imag<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &complex)
{
	stream << '{';
	pretty_print(stream, dereference_member(complex, &Type_t::real));
	stream << ", ";
	pretty_print(stream, dereference_member(complex, &Type_t::imag));
	stream << '}';
}

//
// WinApi

template <typename Type_t>
typename enable_if<has_members_cx_cy<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &size)
{
	stream << '{';
	pretty_print(stream, dereference_member(size, &Type_t::cx));
	stream << " x ";
	pretty_print(stream, dereference_member(size, &Type_t::cy));
	stream << '}';
}

template <typename Type_t>
typename enable_if<has_members_left_top_right_bottom<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rectangle)
{
	stream << '{';
	pretty_print(stream, dereference_member(rectangle, &Type_t::left));
	stream << ", ";
	pretty_print(stream, dereference_member(rectangle, &Type_t::top));
	stream << "} {";
	pretty_print(stream, dereference_member(rectangle, &Type_t::right));
	stream << " x ";
	pretty_print(stream, dereference_member(rectangle, &Type_t::bottom));
	stream << '}';
}

//
// Unreal Engine

template <typename Type_t>
typename enable_if<has_members_Key_Value<Type_t>::value, void>::type pretty_print(std::ostream &, const Type_t &)
{
	// TODO: do
}

template <typename Type_t>
typename enable_if<has_members_v1_v2<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &vector_pair)
{
	pretty_print(stream, vector_pair.v1);
	stream << ", ";
	pretty_print(stream, vector_pair.v2);
}

template <typename Type_t>
typename enable_if<has_members_Origin_Direction<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &ray)
{
	stream << "O:";
	pretty_print(stream, ray.Origin);
	stream << ", D:";
	pretty_print(stream, ray.Direction);
}

template <typename Type_t>
typename enable_if<has_members_Vertex_Count<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &edge)
{
	pretty_print(stream, edge.Vertex[0]);
	stream << ", " << pretty_print(stream, edge.Vertex[1]);
}

template <typename Type_t>
typename enable_if<has_members_Pitch_Roll_Yaw<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &rotator)
{
	stream << '(';
	pretty_print(stream, rotator.Pitch);
	stream << ", ";
	pretty_print(stream, rotator.Roll);
	stream << ", ";
	pretty_print(stream, rotator.Yaw);
	stream << ')';
}

template <typename Type_t>
typename enable_if<has_members_GetLowerBound_GetUpperBound<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &range)
{
	if (range.GetLowerBound().IsOpen())
	{
		stream << "(-inf";
	}
	else if (range.GetLowerBound().IsExclusive())
	{
		stream << '(';
		pretty_print(stream, range.GetLowerBound().GetValue());
	}
	else
	{
		stream << '[';
		pretty_print(stream, range.GetLowerBound().GetValue());
	}

	stream << ", ";

	if (range.GetUpperBound().IsOpen())
	{
		stream << "+inf)";
	}
	else if (range.GetUpperBound().IsExclusive())
	{
		pretty_print(stream, range.GetUpperBound().GetValue());
		stream << ')';
	}
	else
	{
		pretty_print(stream, range.GetUpperBound().GetValue());
		stream << ']';
	}

}

template <typename Type_t>
typename enable_if<has_members_GetValue_IsExclusive_IsInclusive_IsOpen<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &range)
{
	if (range.IsOpen())
	{
		stream << "Open";
	}
	else
	{
		pretty_print(stream, range.GetValue());
		stream << '|';
		if (range.IsExclusive())
		{
			stream << "Exclusive";
		}
		else if (range.IsInclusive())
		{
			stream << "Inclusive";
		}
	}

}

template <typename Type_t>
typename enable_if<has_members_Min_Max_bIsValid<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &box)
{
	pretty_print(stream, box.Min);
	stream << ", ";
	pretty_print(stream, box.Max);
	if (!box.bIsValid)
	{
		stream << " - invalid";
	}
}

template <typename Type_t>
typename enable_if<has_members_Min_Max_IsValid<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &box)
{
	pretty_print(stream, box.Min);
	stream << ", ";
	pretty_print(stream, box.Max);
	if (!box.IsValid)
	{
		stream << " - invalid";
	}

}

template <typename Type_t>
typename enable_if<has_members_Center_W<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &sphere)
{
	stream << "C:";
	pretty_print(stream, sphere.Center);
	stream << ", R:";
	pretty_print(stream, sphere.W);
}

template <typename Type_t>
typename enable_if<has_members_Center_Radius_Orientation_Length<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &capsule)
{
	stream << "C:";
	pretty_print(stream, capsule.Center);
	stream << ", R:";
	pretty_print(stream, capsule.Radius);
	stream << ", O:";
	pretty_print(stream, capsule.Orientation);
	stream << ", L:";
	pretty_print(stream, capsule.Length);
}

template <typename Type_t>
typename enable_if<has_members_Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &box)
{
	stream << "C:";
	pretty_print(stream, box.Center);
	stream << ", A:(";
	pretty_print(stream, box.AxisX);
	stream << ", ";
	pretty_print(stream, box.AxisY);
	stream << ", ";
	pretty_print(stream, box.AxisZ);
	stream << "), E:(";
	pretty_print(stream, box.ExtentX);
	stream << ", ";
	pretty_print(stream, box.ExtentY);
	stream << ", ";
	pretty_print(stream, box.ExtentZ);
	stream << ')';
}

template <typename Type_t>
typename enable_if<has_members_Origin_BoxExtent_SphereRadius<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &bounds)
{
	stream << "O:";
	pretty_print(stream, bounds.Origin);
	stream << ", E:";
	pretty_print(stream, bounds.BoxExtent);
	stream << ", R:";
	pretty_print(stream, bounds.SphereRadius);
}

template <typename Iterator_t>
void print_string(std::ostream &stream, Iterator_t begin, Iterator_t end)
{
	for ( ; begin != end; ++begin)
	{
		stream << *begin;
	}
}

template <typename Type_t>
typename enable_if<has_members_GetCharArray<Type_t>::value, void>::type pretty_print(std::ostream &stream, const Type_t &string)
{
	stream << '"';
	print_string(stream, string.begin(), string.end());
	stream << '"';
}

//
// Fallback

template <typename Type_t>
typename enable_if<
#if TRACE_OUT_CPP_VERSION >= 201103L
	!std::is_enum<Type_t>::value &&
#endif
	!has_supported_members<Type_t>::value &&
	!is_pointer<Type_t>::value &&
	!is_iterable<Type_t>::value,
void>::type pretty_print(std::ostream &stream, const Type_t &)
{
	stream << "<unknown-type>";
}

//
// Private

number_bits_iterator print_bits(std::ostream &stream, number_bits_iterator iterator, standard::size_t how_much)
{
	for (; how_much > 0; --how_much)
	{
		stream << *iterator;
		++iterator;
	}

	return iterator;
}

template <typename Floating_t>
void pretty_print_floating_in_binary(std::ostream &stream, Floating_t value)
{
	union
	{
		Floating_t floating_point_value;
		standard::uint8_t bits[sizeof(value)];
	};

	floating_point_value = value;

	number_bits_iterator iterator(bits, number_format<Floating_t>::length() / 8);

	stream << "bin: " << *iterator << ' ';
	++iterator;

	if (number_format<Floating_t>::exponent_first_byte_length() > 0)
	{
		stream << ' ';
		iterator = print_bits(stream, iterator, number_format<Floating_t>::exponent_first_byte_length());
	}

	for (standard::size_t left = number_format<Floating_t>::exponent_rest_bytes_count(); left > 0; --left)
	{
		stream << ' ';
		iterator = print_bits(stream, iterator, 8);
	}

	stream << ' ';

	if (number_format<Floating_t>::mantissa_first_byte_length() > 0)
	{
		stream << ' ';
		iterator = print_bits(stream, iterator, number_format<Floating_t>::mantissa_first_byte_length());
	}

	for (standard::size_t left = number_format<Floating_t>::mantissa_rest_bytes_count(); left > 0; --left)
	{
		stream << ' ';
		iterator = print_bits(stream, iterator, 8);
	}
}

const standard::uint8_t *print_bytes_of_number(std::ostream &stream, const standard::uint8_t *iterator, standard::size_t how_much, const char *(*represent)(standard::uint8_t))
{
	for ( ; how_much > 0; --how_much)
	{
		stream << represent(*iterator);
		iterator = next_byte_in_number(iterator);
	}

	return iterator;
}

}

