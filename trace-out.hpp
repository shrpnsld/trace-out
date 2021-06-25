#pragma once

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdarg>
#include <cstddef>
#include <cstring>
#include <ctime>
#include <ios>
#include <iterator>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>


#if defined(__clang__)
	#define TRACE_OUT_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
	#define TRACE_OUT_GCC
#elif defined(_MSC_VER)
	#define TRACE_OUT_MVS
#else
	#error Failed to detect compiler
#endif

#if defined(__MINGW32__)
	#define TRACE_OUT_MINGW
#endif

#if defined(__unix__) || defined(__APPLE__)
	#define TRACE_OUT_POSIX
#elif defined(_WIN32)
	#define TRACE_OUT_WINDOWS
#else
	#error Failed to detect platform
#endif


// Visual Studio was defining '__cplusplus' macro as '199711L', and now they have '/Zc:__cplusplus' to fix this.
// If, for some reason, you don't want to use this option, you can define macro 'TRACE_OUT_CPP_VERSION' with a valid '__cplusplus' macro value
#if !defined(TRACE_OUT_CPP_VERSION)
	#define TRACE_OUT_CPP_VERSION __cplusplus
#endif


#if TRACE_OUT_CPP_VERSION >= 201103L
	#include <cstdint>
#else
	#include <stdint.h>
#endif


namespace trace_out { namespace detail { namespace standard
{

#if TRACE_OUT_CPP_VERSION >= 201103L
		typedef ::std::int8_t int8_t;
		typedef ::std::int16_t int16_t;
		typedef ::std::int32_t int32_t;
		typedef ::std::int64_t int64_t;

		typedef ::std::uint8_t uint8_t;
		typedef ::std::uint16_t uint16_t;
		typedef ::std::uint32_t uint32_t;
		typedef ::std::uint64_t uint64_t;

		typedef ::std::size_t size_t;
		typedef ::std::uintptr_t uintptr_t;
#else
		typedef ::int8_t int8_t;
		typedef ::int16_t int16_t;
		typedef ::int32_t int32_t;
		typedef ::int64_t int64_t;

		typedef ::uint8_t uint8_t;
		typedef ::uint16_t uint16_t;
		typedef ::uint32_t uint32_t;
		typedef ::uint64_t uint64_t;

		typedef ::size_t size_t;
		typedef ::uintptr_t uintptr_t;
#endif // TRACE_OUT_CPP_VERSION >= 201103L

}
}
}


#if TRACE_OUT_CPP_VERSION >= 201103L
	#include <tuple>
#endif


#define trace_out_private__concat_impl(a, b) \
			a##b

#define trace_out_private__concat(a, b) \
			trace_out_private__concat_impl(a, b)

#define trace_out_private__unify(identifier_base) \
			trace_out_private__concat(identifier_base, __COUNTER__)

#define trace_out_private__id \
			trace_out_private__concat(id, __COUNTER__)


#define trace_out_private__dereference_macro_impl(name) \
			name

#define trace_out_private__dereference_macro(name) \
			trace_out_private__dereference_macro_impl(name)


#define trace_out_private__quotize_impl(something) \
			#something

#define trace_out_private__quotize(something) \
			trace_out_private__quotize_impl(something)


#if defined(TRACE_OUT_STRIP_NAMESPACES)
	#define trace_out_private__strip_namespaces(string) \
				trace_out::detail::strip_namespaces(string, TRACE_OUT_STRIP_NAMESPACES)
#else
	#define trace_out_private__strip_namespaces(string) \
				string
#endif


#define TRACE_OUT_FILENAME_LINE \
			(trace_out::detail::filename_line_field(trace_out::detail::filename_from_path(__FILE__), static_cast<unsigned long>(__LINE__)))


#if defined(TRACE_OUT_CLANG) || defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)
	#define TRACE_OUT_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(TRACE_OUT_MVS)
	#define TRACE_OUT_FUNCTION_SIGNATURE __FUNCSIG__
#else
	#error Cannot find function signature macro for current compiler. Try to add one manualy to this block.
#endif


namespace trace_out { namespace detail
{

	const std::string filename_from_path(const char *path);
	const std::string filename_line_field(const std::string &file, unsigned long line);

	template <typename Type_t>
	Type_t &reference(Type_t &object);

	template <typename Type_t>
	const Type_t &reference(const Type_t &object);

	template <typename Type_t>
	Type_t &reference(Type_t *object);

	template <typename Type_t>
	const Type_t &reference(const Type_t *object);

	template <typename Type_t>
	void crash_on_bad_memory(const Type_t &variable);


	typedef std::ios_base &(*manipulator_t)(std::ios_base &);

	void apply_io_manipulators(std::ostream &stream, va_list manipulators);

	template <typename Type_t>
	const std::string to_string(const Type_t &value, manipulator_t first_manipulator = NULL, ...);

	std::string first_token(const std::string &tokens);
	std::string rest_tokens(const std::string &tokens);

	std::string strip_namespaces(const std::string &line, std::size_t parent_namespace_count = 0);


	template <typename First_t, typename Second_t>
	struct is_same;


	template <typename Type_t>
	struct is_same<Type_t, Type_t>
	{
		enum
		{
			value = true
		};
	};


	template <typename First_t, typename Second_t>
	struct is_same
	{
		enum
		{
			value = false
		};
	};


	template <typename Type_t>
	struct is_structural
	{
		typedef standard::uint8_t yes;
		typedef standard::uint16_t no;


		template <typename Some_t>
		static yes do_check(int Some_t::*)
		{
			return yes();
		}


		template <typename Some_t>
		static no do_check(...)
		{
			return no();
		}


		enum
		{
			value = sizeof(do_check<Type_t>(0)) == sizeof(yes)
		};
	};


	template <bool Condition, typename True_t, typename False_t>
	struct conditional
	{
		typedef False_t type;
	};


	template <typename True_t, typename False_t>
	struct conditional<true, True_t, False_t>
	{
		typedef True_t type;
	};


	template <bool Condition, typename Type_t>
	struct enable_if;


	template <typename Type_t>
	struct enable_if<true, Type_t>
	{
		typedef Type_t type;
	};


#if TRACE_OUT_CPP_VERSION >= 201103L

	// need this to fix printing of std::tuple
	template <typename ...Types_t>
	struct sizeof_pack
	{
		enum
		{
			value = sizeof...(Types_t)
		};
	};

#endif // TRACE_OUT_CPP_VERSION >= 201103L


#define trace_out_private__define_has_member(name) \
			template <typename Struct_t> \
			struct has_member_##name \
			{ \
				struct fallback \
				{ \
					int name; \
				}; \
				\
				struct dummy \
				{ \
				}; \
				\
				struct derived \
					: conditional<is_structural<Struct_t>::value, Struct_t, dummy>::type, fallback \
				{ \
					derived(const derived &) \
					{ \
					} \
					\
					derived &operator =(const derived &) \
					{ \
						return *this; \
					} \
				}; \
				\
				template <typename Type_t, Type_t> \
				struct do_check; \
				\
				template <typename Type_t> \
				static char (&function(do_check<int fallback::*, &Type_t::name> *))[1]; \
				\
				template <typename Type_t> \
				static char (&function(...))[2]; \
				\
				enum \
				{ \
					value = sizeof(function<derived>(0)) == 2 \
				}; \
			}

	//
	// Common members

	trace_out_private__define_has_member(x);
	trace_out_private__define_has_member(y);
	trace_out_private__define_has_member(z);
	trace_out_private__define_has_member(w);
	trace_out_private__define_has_member(X);
	trace_out_private__define_has_member(Y);
	trace_out_private__define_has_member(Z);
	trace_out_private__define_has_member(W);
	trace_out_private__define_has_member(width);
	trace_out_private__define_has_member(height);
	trace_out_private__define_has_member(Width);
	trace_out_private__define_has_member(Height);
	trace_out_private__define_has_member(origin);
	trace_out_private__define_has_member(size);
	trace_out_private__define_has_member(real);
	trace_out_private__define_has_member(imag);
	trace_out_private__define_has_member(begin);
	trace_out_private__define_has_member(end);


	//
	// WinApi

	trace_out_private__define_has_member(cx);
	trace_out_private__define_has_member(cy);
	trace_out_private__define_has_member(left);
	trace_out_private__define_has_member(top);
	trace_out_private__define_has_member(right);
	trace_out_private__define_has_member(bottom);


	//
	// Unreal Engine

	trace_out_private__define_has_member(Key);
	trace_out_private__define_has_member(Value);
	trace_out_private__define_has_member(v1);
	trace_out_private__define_has_member(v2);
	trace_out_private__define_has_member(Origin);
	trace_out_private__define_has_member(Direction);
	trace_out_private__define_has_member(Pitch);
	trace_out_private__define_has_member(Roll);
	trace_out_private__define_has_member(Yaw);
	trace_out_private__define_has_member(GetLowerBound);
	trace_out_private__define_has_member(GetUpperBound);
	trace_out_private__define_has_member(GetValue);
	trace_out_private__define_has_member(IsExclusive);
	trace_out_private__define_has_member(IsInclusive);
	trace_out_private__define_has_member(IsOpen);
	trace_out_private__define_has_member(Vertex);
	trace_out_private__define_has_member(Count);
	trace_out_private__define_has_member(Min);
	trace_out_private__define_has_member(Max);
	trace_out_private__define_has_member(Center);
	trace_out_private__define_has_member(Radius);
	trace_out_private__define_has_member(Orientation);
	trace_out_private__define_has_member(Length);
	trace_out_private__define_has_member(AxisX);
	trace_out_private__define_has_member(AxisY);
	trace_out_private__define_has_member(AxisZ);
	trace_out_private__define_has_member(ExtentX);
	trace_out_private__define_has_member(ExtentY);
	trace_out_private__define_has_member(ExtentZ);
	trace_out_private__define_has_member(bIsValid);
	trace_out_private__define_has_member(IsValid);
	trace_out_private__define_has_member(BoxExtent);
	trace_out_private__define_has_member(SphereRadius);
	trace_out_private__define_has_member(GetCharArray);

#undef trace_out_private__define_has_member


#define trace_out_private__define_has_members(name, template_parameter_name, ...) \
	template <typename template_parameter_name> \
	struct has_members_##name \
	{ \
		enum \
		{ \
			value = __VA_ARGS__ \
		}; \
	}


	//
	// Common member combinations

	trace_out_private__define_has_members(x_y, Type_t,
		has_member_x<Type_t>::value && has_member_y<Type_t>::value &&
		!has_member_z<Type_t>::value && !has_member_w<Type_t>::value && !has_member_width<Type_t>::value && !has_member_height<Type_t>::value);

	trace_out_private__define_has_members(X_Y, Type_t,
		has_member_X<Type_t>::value && has_member_Y<Type_t>::value &&
		!has_member_Z<Type_t>::value && !has_member_W<Type_t>::value && !has_member_Width<Type_t>::value && !has_member_Height<Type_t>::value);

	trace_out_private__define_has_members(x_y_z, Type_t,
		has_member_x<Type_t>::value && has_member_y<Type_t>::value && has_member_z<Type_t>::value &&
		!has_member_w<Type_t>::value);

	trace_out_private__define_has_members(X_Y_Z, Type_t,
		has_member_X<Type_t>::value && has_member_Y<Type_t>::value && has_member_Z<Type_t>::value &&
		!has_member_W<Type_t>::value);

	trace_out_private__define_has_members(x_y_z_w, Type_t,
		has_member_x<Type_t>::value && has_member_y<Type_t>::value && has_member_z<Type_t>::value && has_member_w<Type_t>::value);

	trace_out_private__define_has_members(X_Y_Z_W, Type_t,
		has_member_X<Type_t>::value && has_member_Y<Type_t>::value && has_member_Z<Type_t>::value && has_member_W<Type_t>::value);

	trace_out_private__define_has_members(width_height, Type_t,
		has_member_width<Type_t>::value && has_member_height<Type_t>::value &&
		!has_member_x<Type_t>::value && !has_member_y<Type_t>::value);

	trace_out_private__define_has_members(Width_Height, Type_t,
		has_member_Width<Type_t>::value && has_member_Height<Type_t>::value &&
		!has_member_X<Type_t>::value && !has_member_Y<Type_t>::value);

	trace_out_private__define_has_members(x_y_width_height, Type_t,
		has_member_x<Type_t>::value && has_member_y<Type_t>::value && has_member_width<Type_t>::value && has_member_height<Type_t>::value);

	trace_out_private__define_has_members(X_Y_Width_Height, Type_t,
		has_member_X<Type_t>::value && has_member_Y<Type_t>::value && has_member_Width<Type_t>::value && has_member_Height<Type_t>::value);

	trace_out_private__define_has_members(origin_size, Type_t,
		has_member_origin<Type_t>::value && has_member_size<Type_t>::value);

	trace_out_private__define_has_members(real_imag, Type_t,
		has_member_real<Type_t>::value && has_member_imag<Type_t>::value);

	trace_out_private__define_has_members(begin_end, Type_t,
		has_member_begin<Type_t>::value && has_member_end<Type_t>::value &&
		!has_member_GetCharArray<Type_t>::value);


	//
	// WinApi

	// SIZE
	trace_out_private__define_has_members(cx_cy, Type_t,
		has_member_cx<Type_t>::value && has_member_cy<Type_t>::value);

	// RECTs
	trace_out_private__define_has_members(left_top_right_bottom, Type_t,
		has_member_left<Type_t>::value && has_member_top<Type_t>::value && has_member_right<Type_t>::value && has_member_bottom<Type_t>::value);


	//
	// Unreal Engine

	trace_out_private__define_has_members(Key_Value, Type_t,
		has_member_Key<Type_t>::value && has_member_Value<Type_t>::value);

	// FTwoVectors
	trace_out_private__define_has_members(v1_v2, Type_t,
		has_member_v1<Type_t>::value && has_member_v2<Type_t>::value);

	// FRay
	trace_out_private__define_has_members(Origin_Direction, Type_t,
		has_member_Origin<Type_t>::value && has_member_Direction<Type_t>::value);

	// FEdge
	trace_out_private__define_has_members(Vertex_Count, Type_t,
		has_member_Vertex<Type_t>::value && has_member_Count<Type_t>::value);

	// FRotator
	trace_out_private__define_has_members(Pitch_Roll_Yaw, Type_t,
		has_member_Pitch<Type_t>::value && has_member_Roll<Type_t>::value && has_member_Yaw<Type_t>::value);

	// TRange
	trace_out_private__define_has_members(GetLowerBound_GetUpperBound, Type_t,
		has_member_GetLowerBound<Type_t>::value && has_member_GetUpperBound<Type_t>::value);

	// TRangeBound
	trace_out_private__define_has_members(GetValue_IsExclusive_IsInclusive_IsOpen, Type_t,
		has_member_GetValue<Type_t>::value && has_member_IsExclusive<Type_t>::value && has_member_IsInclusive<Type_t>::value && has_member_IsOpen<Type_t>::value);

	// FBox2D
	trace_out_private__define_has_members(Min_Max_bIsValid, Type_t,
		has_member_Min<Type_t>::value && has_member_Max<Type_t>::value && has_member_bIsValid<Type_t>::value);

	// FBox
	trace_out_private__define_has_members(Min_Max_IsValid, Type_t,
		has_member_Min<Type_t>::value && has_member_Max<Type_t>::value && has_member_IsValid<Type_t>::value);

	// FSphere
	trace_out_private__define_has_members(Center_W, Type_t,
		has_member_Center<Type_t>::value && has_member_W<Type_t>::value);

	// FCapsuleShape
	trace_out_private__define_has_members(Center_Radius_Orientation_Length, Type_t,
		has_member_Center<Type_t>::value && has_member_Radius<Type_t>::value && has_member_Orientation<Type_t>::value && has_member_Length<Type_t>::value);

	// FOrientedBox
	trace_out_private__define_has_members(Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ, Type_t,
		has_member_Center<Type_t>::value && has_member_AxisX<Type_t>::value && has_member_AxisY<Type_t>::value && has_member_AxisZ<Type_t>::value && has_member_ExtentX<Type_t>::value && has_member_ExtentY<Type_t>::value && has_member_ExtentZ<Type_t>::value);

	// FBoxSphereBounds
	trace_out_private__define_has_members(Origin_BoxExtent_SphereRadius, Type_t,
		has_member_Origin<Type_t>::value && has_member_BoxExtent<Type_t>::value && has_member_SphereRadius<Type_t>::value);

	// FString
	trace_out_private__define_has_members(GetCharArray, Type_t,
		has_member_GetCharArray<Type_t>::value);

#undef trace_out_private__define_has_members


	template <typename Type_t>
	struct has_supported_members
	{
		enum
		{
			value =
				has_members_x_y<Type_t>::value ||
				has_members_X_Y<Type_t>::value ||
				has_members_x_y_z<Type_t>::value ||
				has_members_X_Y_Z<Type_t>::value ||
				has_members_x_y_z_w<Type_t>::value ||
				has_members_X_Y_Z_W<Type_t>::value ||
				has_members_width_height<Type_t>::value ||
				has_members_Width_Height<Type_t>::value ||
				has_members_x_y_width_height<Type_t>::value ||
				has_members_X_Y_Width_Height<Type_t>::value ||
				has_members_origin_size<Type_t>::value ||
				has_members_real_imag<Type_t>::value ||
				has_members_cx_cy<Type_t>::value ||
				has_members_left_top_right_bottom<Type_t>::value ||
				has_members_Key_Value<Type_t>::value ||
				has_members_v1_v2<Type_t>::value ||
				has_members_Origin_Direction<Type_t>::value ||
				has_members_Vertex_Count<Type_t>::value ||
				has_members_Pitch_Roll_Yaw<Type_t>::value ||
				has_members_GetLowerBound_GetUpperBound<Type_t>::value ||
				has_members_GetValue_IsExclusive_IsInclusive_IsOpen<Type_t>::value ||
				has_members_Min_Max_bIsValid<Type_t>::value ||
				has_members_Min_Max_IsValid<Type_t>::value ||
				has_members_Center_W<Type_t>::value ||
				has_members_Center_Radius_Orientation_Length<Type_t>::value ||
				has_members_Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ<Type_t>::value ||
				has_members_Origin_BoxExtent_SphereRadius<Type_t>::value ||
				has_members_GetCharArray<Type_t>::value
		};
	};


	template <typename Type_t>
	struct is_iterable
	{
		enum
		{
			value = has_members_begin_end<Type_t>::value && !is_same<Type_t, std::string>::value
		};
	};

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	Type_t &reference(Type_t &object)
	{
		return object;
	}


	template <typename Type_t>
	const Type_t &reference(const Type_t &object)
	{
		return object;
	}


	template <typename Type_t>
	Type_t &reference(Type_t *object)
	{
		return *object;
	}


	template <typename Type_t>
	const Type_t &reference(const Type_t *object)
	{
		return *object;
	}


	template <typename Type_t>
	void crash_on_bad_memory(const Type_t &variable)
	{
		standard::uint8_t buffer[sizeof(variable)];
		std::memcpy(buffer, &variable, sizeof(buffer));
	}


	template <typename Type_t>
	const std::string to_string(const Type_t &value, manipulator_t first_manipulator, ...)
	{
		std::stringstream string_stream;

		if (first_manipulator != NULL)
		{
			va_list rest_manipulators;
			va_start(rest_manipulators, first_manipulator);

			string_stream << first_manipulator;
			apply_io_manipulators(string_stream, rest_manipulators);

			va_end(rest_manipulators);
		}

		string_stream << value;

		return string_stream.str();
	}

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	class pretty
	{
	public:
		pretty(const Type_t &data);
		pretty(const pretty &another);

		const Type_t &get() const;
		const Type_t &unsafe_get() const;

	private:
		pretty &operator =(const pretty &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L

		pretty &operator =(pretty &&another); // = delete

#endif // TRACE_OUT_CPP_VERSION >= 201103L

		const Type_t &_data;
	};


	template <typename Type_t>
	class pretty_condition
	{
	public:
		pretty_condition(const Type_t &data);
		pretty_condition(const pretty_condition &another);

		const Type_t &get() const;

	private:
		pretty_condition &operator =(const pretty_condition &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L

		pretty_condition &operator =(pretty_condition &&another); // = delete

#endif // TRACE_OUT_CPP_VERSION >= 201103L

		const Type_t &_data;
	};


	template <typename Type_t>
	pretty_condition<Type_t> make_pretty_condition(const Type_t &value);


	template <typename Type_t>
	class pretty_structural
	{
	public:
		pretty_structural(const Type_t &data);
		pretty_structural(const pretty_structural &another);

		const Type_t &get() const;
		const Type_t &unsafe_get() const;

	private:
		pretty_structural &operator =(const pretty_structural &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L

		pretty_structural &operator =(pretty_structural &&another); // = delete

#endif // TRACE_OUT_CPP_VERSION >= 201103L

		const Type_t &_data;
	};


	template <typename Type_t>
	class pretty_iterable
	{
	public:
		pretty_iterable(const Type_t &data);
		pretty_iterable(const pretty_iterable &another);

		const Type_t &get() const;
		const Type_t &unsafe_get() const;

	private:
		pretty_iterable &operator =(const pretty_iterable &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L

		pretty_iterable &operator =(pretty_iterable &&another); // = delete

#endif // TRACE_OUT_CPP_VERSION >= 201103L

		const Type_t &_data;
	};


	template <typename Iterator_t>
	class pretty_range_closed
	{
	public:
		pretty_range_closed(const Iterator_t &begin, const Iterator_t &end);
		pretty_range_closed(const pretty_range_closed &another);

		const Iterator_t &get_begin() const;
		const Iterator_t &get_end() const;

	private:
		pretty_range_closed &operator =(const pretty_range_closed &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L
		pretty_range_closed &operator =(pretty_range_closed &&another); // = delete
#endif // TRACE_OUT_CPP_VERSION >= 201103L

	private:
		const Iterator_t &_begin;
		const Iterator_t &_end;
	};


	template <typename Iterator_t>
	class pretty_range_open
	{
	public:
		pretty_range_open(const Iterator_t &begin, const std::size_t &how_much);
		pretty_range_open(const pretty_range_open &another);

		const Iterator_t &get_begin() const;
		const std::size_t &get_how_much() const;

	private:
		pretty_range_open &operator =(const pretty_range_open &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L
		pretty_range_open &operator =(pretty_range_open &&another); // = delete
#endif // TRACE_OUT_CPP_VERSION >= 201103L

	public:
		const Iterator_t &_begin;
		const std::size_t &_how_much;
	};


	template <typename Type_t>
	typename enable_if<!is_iterable<Type_t>::value && has_supported_members<Type_t>::value, pretty_structural<Type_t> >::type make_pretty(const Type_t &value)
	{
		return pretty_structural<Type_t>(value);
	}


	template <typename Type_t>
	typename enable_if<is_iterable<Type_t>::value && !is_same<Type_t, std::string>::value, pretty_iterable<Type_t> >::type make_pretty(const Type_t &value)
	{
		return pretty_iterable<Type_t>(value);
	}


	template <typename Type_t>
	typename enable_if<!is_iterable<Type_t>::value && !has_supported_members<Type_t>::value, pretty<Type_t> >::type make_pretty(const Type_t &value)
	{
		return pretty<Type_t>(value);
	}

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	pretty<Type_t>::pretty(const Type_t &data)
		:
		_data(data)
	{
	}


	template <typename Type_t>
	pretty<Type_t>::pretty(const pretty &another)
		:
		_data(another._data)
	{
	}


	template <typename Type_t>
	const Type_t &pretty<Type_t>::get() const
	{
		crash_on_bad_memory(_data);

		return _data;
	}


	template <typename Type_t>
	const Type_t &pretty<Type_t>::unsafe_get() const
	{
		return _data;
	}


	template <typename Type_t>
	pretty_condition<Type_t>::pretty_condition(const Type_t &data)
		:
		_data(data)
	{
	}


	template <typename Type_t>
	pretty_condition<Type_t>::pretty_condition(const pretty_condition &another)
		:
		_data(another._data)
	{
	}


	template <typename Type_t>
	const Type_t &pretty_condition<Type_t>::get() const
	{
		return _data;
	}


	template <typename Type_t>
	pretty_condition<Type_t> make_pretty_condition(const Type_t &value)
	{
		return pretty_condition<Type_t>(value);
	}


	template <typename Type_t>
	pretty_structural<Type_t>::pretty_structural(const Type_t &data)
		:
		_data(data)
	{
	}


	template <typename Type_t>
	pretty_structural<Type_t>::pretty_structural(const pretty_structural &another)
		:
		_data(another._data)
	{
	}


	template <typename Type_t>
	const Type_t &pretty_structural<Type_t>::get() const
	{
		crash_on_bad_memory(_data);

		return _data;
	}


	template <typename Type_t>
	const Type_t &pretty_structural<Type_t>::unsafe_get() const
	{
		return _data;
	}


	template <typename Type_t>
	pretty_iterable<Type_t>::pretty_iterable(const Type_t &data)
		:
		_data(data)
	{
	}


	template <typename Type_t>
	pretty_iterable<Type_t>::pretty_iterable(const pretty_iterable &another)
		:
		_data(another._data)
	{
	}


	template <typename Type_t>
	const Type_t &pretty_iterable<Type_t>::get() const
	{
		crash_on_bad_memory(_data);

		return _data;
	}


	template <typename Type_t>
	const Type_t &pretty_iterable<Type_t>::unsafe_get() const
	{
		return _data;
	}


	template <typename Iterator_t>
	pretty_range_closed<Iterator_t>::pretty_range_closed(const Iterator_t &begin, const Iterator_t &end)
		:
		_begin(begin),
		_end(end)
	{
	}


	template <typename Iterator_t>
	pretty_range_closed<Iterator_t>::pretty_range_closed(const pretty_range_closed &another)
		:
		_begin(another._begin),
		_end(another._end)
	{
	}


	template <typename Iterator_t>
	const Iterator_t &pretty_range_closed<Iterator_t>::get_begin() const
	{
		crash_on_bad_memory(_begin);

		return _begin;
	}


	template <typename Iterator_t>
	const Iterator_t &pretty_range_closed<Iterator_t>::get_end() const
	{
		crash_on_bad_memory(_end);

		return _end;
	}


	template <typename Iterator_t>
	pretty_range_open<Iterator_t>::pretty_range_open(const Iterator_t &begin, const std::size_t &how_much)
		:
		_begin(begin),
		_how_much(how_much)
	{
	}


	template <typename Iterator_t>
	pretty_range_open<Iterator_t>::pretty_range_open(const pretty_range_open &another)
		:
		_begin(another._begin),
		_how_much(another._how_much)
	{
	}


	template <typename Iterator_t>
	const Iterator_t &pretty_range_open<Iterator_t>::get_begin() const
	{
		crash_on_bad_memory(_begin);

		return _begin;
	}


	template <typename Iterator_t>
	const std::size_t &pretty_range_open<Iterator_t>::get_how_much() const
	{
		crash_on_bad_memory(_how_much);

		return _how_much;
	}


	template <typename Iterator_t>
	pretty_range_closed<Iterator_t> make_pretty_range(const Iterator_t &begin, const Iterator_t &end)
	{
		return pretty_range_closed<Iterator_t>(begin, end);
	}


	template <typename Iterator_t>
	pretty_range_open<Iterator_t> make_pretty_range(const Iterator_t &begin, const std::size_t &how_much)
	{
		return pretty_range_open<Iterator_t>(begin, how_much);
	}

}
}


namespace trace_out { namespace detail
{

	const std::string &indentation();
	void indentation_add();
	void indentation_remove();

	void set_current_thread_name(const std::string &name);

	class newline_manipulator;
	class endline_manipulator;
	class flush_manipulator;

	extern const newline_manipulator NEWLINE;
	extern const endline_manipulator ENDLINE;
	extern const flush_manipulator FLUSH;


	class out_stream
	{
	public:
		out_stream(const std::string &filename_line);
		out_stream();
		~out_stream();

		out_stream &operator <<(char character);
		out_stream &operator <<(const char *string);
		out_stream &operator <<(const std::string &string);
		out_stream &operator <<(const newline_manipulator &);
		out_stream &operator <<(const endline_manipulator &);
		out_stream &operator <<(const flush_manipulator &);
		standard::size_t width_left() const;
		void printf(const char *format, ...);
		void flush();

		static standard::size_t width();

	private:
		standard::size_t _current_line_length;
	};


	out_stream &operator <<(out_stream &stream, const pretty<bool> &value);
	out_stream &operator <<(out_stream &stream, const pretty<char> &value);
	out_stream &operator <<(out_stream &stream, const pretty<wchar_t> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned char> &value);
	out_stream &operator <<(out_stream &stream, const pretty<const char *> &value);
	out_stream &operator <<(out_stream &stream, const pretty<std::string> &value);
	out_stream &operator <<(out_stream &stream, const pretty<short> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned short> &value);
	out_stream &operator <<(out_stream &stream, const pretty<int> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned int> &value);
	out_stream &operator <<(out_stream &stream, const pretty<long> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned long> &value);

#if TRACE_OUT_CPP_VERSION >= 201103L

	out_stream &operator <<(out_stream &stream, const pretty<long long> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned long long> &value);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	out_stream &operator <<(out_stream &stream, const pretty<float> &value);
	out_stream &operator <<(out_stream &stream, const pretty<double> &value);
	out_stream &operator <<(out_stream &stream, const pretty<long double> &value);
	out_stream &operator <<(out_stream &stream, const pretty<const void *> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<const Type_t *> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t *> &value);

	template <typename Type_t, standard::size_t Size>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t[Size]> &value);


	//
	// Common member combinations

	template <typename Type_t>
	typename enable_if<has_members_x_y<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_X_Y<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_x_y_z<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_X_Y_Z<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_x_y_z_w<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_X_Y_Z_W<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_width_height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_x_y_width_height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_X_Y_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_origin_size<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_real_imag<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);


	//
	// WinApi

	template <typename Type_t>
	typename enable_if<has_members_cx_cy<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);


	template <typename Type_t>
	typename enable_if<has_members_left_top_right_bottom<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);


	//
	// Unreal Engine

	template <typename Type_t>
	typename enable_if<has_members_v1_v2<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Origin_Direction<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Vertex_Count<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Pitch_Roll_Yaw<Type_t>::value, out_stream>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_GetLowerBound_GetUpperBound<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_GetValue_IsExclusive_IsInclusive_IsOpen<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Min_Max_bIsValid<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Center_W<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Center_Radius_Orientation_Length<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Origin_BoxExtent_SphereRadius<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_GetCharArray<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

#if TRACE_OUT_CPP_VERSION < 201703L

#if defined(TRACE_OUT_GCC)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::auto_ptr<Type_t> > &value);

#if defined(TRACE_OUT_GCC)
	#pragma GCC diagnostic pop
#endif

#endif // TRACE_OUT_CPP_VERSION < 201703L

#if TRACE_OUT_CPP_VERSION >= 201103L

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::unique_ptr<Type_t> > &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::shared_ptr<Type_t> > &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::weak_ptr<Type_t> > &value);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	template <typename First_t, typename Second_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::pair<First_t, Second_t> > &value);

#if TRACE_OUT_CPP_VERSION >= 201103L

	template <typename ...Types_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::tuple<Types_t ...> > &value);

#endif // TRACE_OUT_CPP_VERSION >= 201103L


	template <std::size_t Size>
	out_stream &operator <<(out_stream &stream, const pretty<std::bitset<Size> > &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_iterable<Type_t> &value);

	template <typename Iterator_t>
	out_stream &operator <<(out_stream &stream, const pretty_range_closed<Iterator_t> &value);

	template <typename Iterator_t>
	out_stream &operator <<(out_stream &stream, const pretty_range_open<Iterator_t> &value);

	out_stream &operator <<(out_stream &stream, const pretty_condition<bool> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_condition<Type_t> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t> &value);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<const Type_t *> &value)
	{
		stream << FLUSH;
		const Type_t *pointer = value.get();
		stream << make_pretty(static_cast<const void *>(pointer)) << " ";
		if (pointer != NULL)
		{
			stream << FLUSH;
			stream << "-> " << make_pretty(*pointer);
		}

		return stream;
	}


	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t *> &value)
	{
		stream << FLUSH;
		return stream << make_pretty(static_cast<const Type_t *>(value.get()));
	}


	template <typename Type_t, standard::size_t Size>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t[Size]> &value)
	{
		stream << FLUSH;
		const Type_t *c_array = value.get();

		stream << "[";
		standard::size_t index = 0;
		for ( ; index < Size - 1; ++index)
		{
			stream << make_pretty(c_array[index]) << ", ";
		}

		stream << make_pretty(c_array[index]) << "]";

		return stream;
	}


	template <typename Structure_t, typename Type_t>
	Type_t get_member_value(const Structure_t &instance, Type_t (Structure_t::*member_function)() const)
	{
		return (instance.*member_function)();
	}


	template <typename Structure_t, typename Type_t>
	Type_t get_member_value(const Structure_t &instance, Type_t Structure_t::*data_member)
	{
		return instance.*data_member;
	}


	//
	// Common member combinations

	template <typename Type_t>
	typename enable_if<has_members_x_y<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::x)) << ", " << make_pretty(get_member_value(point, &Type_t::y)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_X_Y<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::X)) << ", " << make_pretty(get_member_value(point, &Type_t::Y)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_x_y_z<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::x)) << ", " << make_pretty(get_member_value(point, &Type_t::y)) << ", " << make_pretty(get_member_value(point, &Type_t::z)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_X_Y_Z<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::X)) << ", " << make_pretty(get_member_value(point, &Type_t::Y)) << ", " << make_pretty(get_member_value(point, &Type_t::Z)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_x_y_z_w<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::x)) << ", " << make_pretty(get_member_value(point, &Type_t::y)) << ", " << make_pretty(get_member_value(point, &Type_t::z)) << ", " << make_pretty(get_member_value(point, &Type_t::w)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_X_Y_Z_W<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::X)) << ", " << make_pretty(get_member_value(point, &Type_t::Y)) << ", " << make_pretty(get_member_value(point, &Type_t::Z)) << ", " << make_pretty(get_member_value(point, &Type_t::W)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_width_height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "(" << make_pretty(get_member_value(size, &Type_t::width)) << " x " << make_pretty(get_member_value(size, &Type_t::height)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "(" << make_pretty(get_member_value(size, &Type_t::Width)) << " x " << make_pretty(get_member_value(size, &Type_t::Height)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_x_y_width_height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t origin_size = value.get();
		stream << "(" << make_pretty(get_member_value(origin_size, &Type_t::x)) << ", " << make_pretty(get_member_value(origin_size, &Type_t::y)) << ") (" << make_pretty(get_member_value(origin_size, &Type_t::width)) << " x " << make_pretty(get_member_value(origin_size, &Type_t::height)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_X_Y_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t origin_size = value.get();
		stream << "(" << make_pretty(get_member_value(origin_size, &Type_t::X)) << ", " << make_pretty(get_member_value(origin_size, &Type_t::Y)) << ") (" << make_pretty(get_member_value(origin_size, &Type_t::Width)) << " x " << make_pretty(get_member_value(origin_size, &Type_t::Height)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_origin_size<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &rect = value.get();
		stream << make_pretty(get_member_value(rect, &Type_t::origin)) << " " << make_pretty(get_member_value(rect, &Type_t::size));
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_real_imag<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &complex = value.get();
		stream << "(" << make_pretty(get_member_value(complex, &Type_t::real)) << ", " << make_pretty(get_member_value(complex, &Type_t::imag)) << ")";
		return stream;
	}


	//
	// WinApi

	template <typename Type_t>
	typename enable_if<has_members_cx_cy<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "(" << make_pretty(get_member_value(size, &Type_t::cx)) << " x " << make_pretty(get_member_value(size, &Type_t::cy)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_left_top_right_bottom<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t origin_size = value.get();
		stream << "(" << make_pretty(get_member_value(origin_size, &Type_t::left)) << ", " << make_pretty(get_member_value(origin_size, &Type_t::top)) << ") (" << make_pretty(get_member_value(origin_size, &Type_t::right)) << " x " << make_pretty(get_member_value(origin_size, &Type_t::bottom)) << ")";
		return stream;
	}


	//
	// Unreal Engine

	template <typename Type_t>
	typename enable_if<has_members_Key_Value<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &key_value = value.get();
		//stream << "{" << make_pretty(get_member_value(key_value, &Type_t::Key)) << ": " << make_pretty(get_member_value(key_value, &Type_t::Value)) << "}";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_v1_v2<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &vectors = value.get();
		stream << make_pretty(vectors.v1) << ", " << make_pretty(vectors.v2);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Origin_Direction<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &ray = value.get();
		stream << "O:" << make_pretty(ray.Origin) << ", D:" << make_pretty(ray.Direction);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Vertex_Count<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &edge = value.get();
		stream << make_pretty(edge.Vertex[0]) << ", " << make_pretty(edge.Vertex[1]);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Pitch_Roll_Yaw<Type_t>::value, out_stream>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &rotator = value.get();
		stream << "(" << make_pretty(rotator.Pitch) << ", " << make_pretty(rotator.Roll) << ", " << make_pretty(rotator.Yaw) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_GetLowerBound_GetUpperBound<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &range = value.get();

		if (range.GetLowerBound().IsOpen())
		{
			stream << "(-inf";
		}
		else if (range.GetLowerBound().IsExclusive())
		{
			stream << "(" << make_pretty(range.GetLowerBound().GetValue());
		}
		else
		{
			stream << "[" << make_pretty(range.GetLowerBound().GetValue());
		}

		stream << ", ";

		if (range.GetUpperBound().IsOpen())
		{
			stream << "+inf)";
		}
		else if (range.GetUpperBound().IsExclusive())
		{
			stream << make_pretty(range.GetUpperBound().GetValue()) << ")";
		}
		else
		{
			stream << make_pretty(range.GetUpperBound().GetValue()) << "]";
		}

		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_GetValue_IsExclusive_IsInclusive_IsOpen<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &bound_range = value.get();
		if (bound_range.IsOpen())
		{
			stream << "Open";
		}
		else
		{
			stream << make_pretty(bound_range.GetValue()) << "|";
			if (bound_range.IsExclusive())
			{
				stream << "Exclusive";
			}
			else if (bound_range, &Type_t::IsInclusive)
			{
				stream << "Inclusive";
			}
		}

		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Min_Max_bIsValid<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &box = value.get();
		stream << make_pretty(box.Min) << ", " << make_pretty(box.Max);
		bool validity = box.bIsValid;
		if (!validity)
		{
			stream << " - invalid";
		}
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Min_Max_IsValid<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &box = value.get();
		stream << make_pretty(box.Min) << ", " << make_pretty(box.Max);
		bool validity = static_cast<bool>(box.IsValid);
		if (!validity)
		{
			stream << " - invalid";
		}

		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Center_W<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &sphere = value.get();
		stream << "C:" << make_pretty(sphere.Center) << ", R:" << make_pretty(sphere.W);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Center_Radius_Orientation_Length<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &capsule = value.get();
		stream << "C:" << make_pretty(capsule.Center) << ", R:" << make_pretty(capsule.Radius) << ", O:" << make_pretty(capsule.Orientation) << ", L:" << make_pretty(capsule.Length);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &box = value.get();
		stream << "C:" << make_pretty(box.Center) << ", A:(" << make_pretty(box.AxisX) << ", " << make_pretty(box.AxisY) << ", " << make_pretty(box.AxisZ) << "), E:(" << make_pretty(box.ExtentX) << ", " << make_pretty(box.ExtentY) << ", " << make_pretty(box.ExtentZ) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Origin_BoxExtent_SphereRadius<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &bounds = value.get();
		stream << "O:" << make_pretty(bounds.Origin) << ", E:" << make_pretty(bounds.BoxExtent) << ", R:" << make_pretty(bounds.SphereRadius);
		return stream;
	}


	template <typename Iterator_t>
	void print_string(out_stream &stream, Iterator_t begin, Iterator_t end)
	{
		for ( ; begin != end; ++begin)
		{
			stream << *begin;
		}
	}


	template <typename Type_t>
	typename enable_if<has_members_GetCharArray<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &str = value.get();
		stream << "\"";
		print_string(stream, str.begin(), str.end());
		stream << "\"";
		return stream;
	}


#if TRACE_OUT_CPP_VERSION < 201703L

#if defined(TRACE_OUT_GCC)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations" // seems it does not turn off the warning if there's no C++11
#endif

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::auto_ptr<Type_t> > &value)
	{
		stream << FLUSH;
		const std::auto_ptr<Type_t> &pointer = value.get();
		return stream << make_pretty(static_cast<const Type_t *>(pointer.get()));
	}

#if defined(TRACE_OUT_GCC)
	#pragma GCC diagnostic pop
#endif

#endif // TRACE_OUT_CPP_VERSION < 201703L


#if TRACE_OUT_CPP_VERSION >= 201103L

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::unique_ptr<Type_t> > &value)
	{
		stream << FLUSH;
		const std::unique_ptr<Type_t> &pointer = value.get();
		return stream << make_pretty(static_cast<const Type_t *>(pointer.get()));
	}


	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::shared_ptr<Type_t> > &value)
	{
		stream << FLUSH;
		const std::shared_ptr<Type_t> &pointer = value.get();
		stream << make_pretty(static_cast<const void *>(pointer.get())) << " (use_count: " << to_string(pointer.use_count()) << ")";
		if (pointer.get() != NULL)
		{
			stream << " -> " << FLUSH;
			stream << make_pretty(*(value.get()));
		}

		return stream;
	}


	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::weak_ptr<Type_t> > &value)
	{
		stream << FLUSH;
		const std::weak_ptr<Type_t> &pointer = value.get();
		stream << "(use_count: " << to_string(pointer.use_count()) << ")";

		return stream;
	}

#endif // TRACE_OUT_CPP_VERSION >= 201103L


	template <typename First_t, typename Second_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::pair<First_t, Second_t> > &value)
	{
		stream << FLUSH;
		const std::pair<First_t, Second_t> &pair = value.get();
		stream << "{";
		stream << make_pretty(pair.first) << ", ";
		stream << make_pretty(pair.second) << "}";
		return stream;
	}


#if TRACE_OUT_CPP_VERSION >= 201103L

	template <standard::size_t Index, typename ...Types_t>
	typename enable_if<Index == sizeof_pack<Types_t...>::value - 1, out_stream &>::type print_tuple(out_stream &stream, const std::tuple<Types_t...> &tuple)
	{
		return stream << make_pretty(std::get<Index>(tuple)) << "}";
	}


#if defined(TRACE_OUT_MVS)

	#pragma warning(push)
	#pragma warning(disable:4296) // "expression is always false"

#endif

	template <standard::size_t Index, typename ...Types_t>
	typename enable_if<Index < sizeof_pack<Types_t...>::value - 1, out_stream &>::type print_tuple(out_stream &stream, const std::tuple<Types_t...> &tuple)
	{
		stream << make_pretty(std::get<Index>(tuple)) << ", ";
		return print_tuple<Index + 1>(stream, tuple);
	}

#if defined(TRACE_OUT_MVS)

	#pragma warning(pop)

#endif


	template <typename ...Types_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::tuple<Types_t ...> > &value)
	{
		stream << FLUSH;
		const std::tuple<Types_t ...> &tuple = value.get();
		stream << "{";
		return print_tuple<0>(stream, tuple);
	}

#endif // TRACE_OUT_CPP_VERSION >= 201103L


	template <std::size_t Size>
	out_stream &operator <<(out_stream &stream, const pretty<std::bitset<Size> > &value)
	{
		stream << FLUSH;
		const std::bitset<Size> &bits = value.get();
		return stream << bits.to_string();
	}


	template <typename Type_t>
	Type_t next_itr(Type_t iterator)
	{
		++iterator;
		return iterator;
	}


	// Using this to infer type of iterator in a pre C++11 way
	template <typename Iterator_t>
	void print_begin_end(out_stream &stream, Iterator_t begin, Iterator_t end)
	{
		// Unreal Engine has only 'operator !=' overloaded for its iterators,
		// and I want this to be an early return
		if (!(begin != end))
		{
			return;
		}

		Iterator_t iterator = begin;
		stream << make_pretty(*iterator);
		for (++iterator; iterator != end; ++iterator)
		{
			stream << ", " << make_pretty(*iterator);
		}
	}


	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_iterable<Type_t> &value)
	{
		stream << FLUSH << "[";

		const Type_t &container = value.get();
		print_begin_end(stream, container.begin(), container.end());

		stream << "]";
		return stream;
	}


	template <typename Iterator_t>
	out_stream &operator <<(out_stream &stream, const pretty_range_closed<Iterator_t> &value)
	{
		stream << FLUSH << "[";

		Iterator_t iterator = value.get_begin();
		Iterator_t end = value.get_end();
		if (iterator != end)
		{
			stream << make_pretty(*iterator);
			for (++iterator; iterator != end; ++iterator)
			{
				stream << ", " << make_pretty(*iterator);
			}
		}

		stream << "]";
		return stream;
	}


	template <typename Iterator_t>
	out_stream &operator <<(out_stream &stream, const pretty_range_open<Iterator_t> &value)
	{
		stream << FLUSH << "[";

		Iterator_t iterator = value.get_begin();
		std::size_t how_much = value.get_how_much();
		if (how_much > 0)
		{
			stream << make_pretty(*iterator);
			for (++iterator, --how_much; how_much > 0; ++iterator, --how_much)
			{
				stream << ", " << make_pretty(*iterator);
			}
		}

		stream << "]";
		return stream;
	}


	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_condition<Type_t> &value)
	{
		stream << FLUSH;
		stream << (value.get() ? "true" : "false") << " (" << FLUSH;
		stream << make_pretty(value.get()) << ")";
		return stream;
	}


	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t> &value)
	{
		stream << FLUSH;
		value.get();
		return stream << "<unknown-type>";
	}

}
}


namespace trace_out { namespace detail
{

#if TRACE_OUT_CPP_VERSION < 201103L

	template <typename Type_t>
	const Type_t &expression(const std::string &filename_line, const char *name, const Type_t &value);

	template <typename Type_t>
	Type_t &expression(const std::string &filename_line, const char *name, Type_t &value);

	template <typename Type_t>
	void watch(const std::string &filename_line, const char *name, const Type_t &value);

#else

	template <typename Type_t>
	Type_t &&expression(const std::string &filename_line, const char *name, Type_t &&value);

	template <typename ...Types_t>
	void watch(const std::string &filename_line, const char *names, const Types_t &...values);

#endif // TRACE_OUT_CPP_VERSION < 201103L

}
}


namespace trace_out { namespace detail
{

#if TRACE_OUT_CPP_VERSION < 201103L

	template <typename Type_t>
	const Type_t &expression(const std::string &filename_line, const char *name, const Type_t &value)
	{
		out_stream stream(filename_line);
		stream << name << " = " << make_pretty(value) << ENDLINE;
		return value;
	}


	template <typename Type_t>
	Type_t &expression(const std::string &filename_line, const char *name, Type_t &value)
	{
		out_stream stream(filename_line);
		stream << name << " = " << make_pretty(value) << ENDLINE;
		return value;
	}


	template <typename Type_t>
	void watch(const std::string &filename_line, const char *name, const Type_t &value)
	{
		out_stream stream(filename_line);
		stream << name << " = " << make_pretty(value) << ENDLINE;
	}

#else

	template <typename Type_t>
	Type_t &&expression(const std::string &filename_line, const char *name, Type_t &&value)
	{
		out_stream stream(filename_line);
		stream << name << " = " << make_pretty(value) << ENDLINE;
		return std::forward<Type_t>(value);
	}


	template <typename Type_t>
	void print_values(out_stream &stream, const std::string &name, const Type_t &value)
	{
		stream << name << " = " << make_pretty(value) << ENDLINE;
	}


	template <typename FirstType_t, typename ...RestTypes_t>
	void print_values(out_stream &stream, const std::string &names, const FirstType_t &first_value, const RestTypes_t &...rest_values)
	{
		stream << first_token(names) << " = " << make_pretty(first_value) << NEWLINE;
		print_values(stream, rest_tokens(names), rest_values...);
	}

	template <typename ...Types_t>
	void watch(const std::string &filename_line, const char *names, const Types_t &...values)
	{
		out_stream stream(filename_line);
		print_values(stream, names, values...);
		if (sizeof...(values) > 1)
		{
			out_stream() << ENDLINE;
		}
	}

#endif // TRACE_OUT_CPP_VERSION < 201103L

}
}


namespace trace_out { namespace detail
{

	template <typename Iterator_t>
	void range(const std::string &filename_line, const char *begin_name, const char *end_name, const Iterator_t &begin, const Iterator_t &end);

	template <typename Iterator_t>
	void range(const std::string &filename_line, const char *begin_name, const char *how_much_name, const Iterator_t &begin, std::size_t how_much);

}
}


namespace trace_out { namespace detail
{

	template <typename Iterator_t>
	void range(const std::string &filename_line, const char *begin_name, const char *end_name, const Iterator_t &begin, const Iterator_t &end)
	{
		out_stream stream(filename_line);
		stream << "[" << begin_name << ", " << end_name << ") = " << pretty_range_closed<Iterator_t>(begin, end) << ENDLINE;
	}


	template <typename Iterator_t>
	void range(const std::string &filename_line, const char *begin_name, const char *how_much_name, const Iterator_t &begin, std::size_t how_much)
	{
		out_stream stream(filename_line);
		stream << "[" << begin_name << ": " << how_much_name << "] = " << pretty_range_open<Iterator_t>(begin, how_much) << ENDLINE;
	}

}
}


namespace trace_out { namespace detail
{

	class function_printer
	{
	public:
		function_printer(const std::string &filename_line, const std::string &function_signature);
		~function_printer();

	private:
		std::string _filename_line;
		std::string _function_signature;
	};


	function_printer make_function_printer(const std::string &filename_line, const std::string &function_signature);


	class return_printer
	{
	public:
		return_printer(const std::string &filename_line);

		template <typename T>
		const T &operator ,(const T &value);

	private:
		std::string _filename_line;
	};


	return_printer make_return_printer(const std::string &filename_line);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	const Type_t &return_printer::operator ,(const Type_t &value)
	{
		out_stream stream(_filename_line);
		stream << "return " << make_pretty(value) << ENDLINE;
		return value;
	}

}
}


namespace trace_out { namespace detail
{

	typedef standard::uint32_t option_t;

	const standard::size_t OPTIONS_START_BASE = 0;
	const standard::size_t OPTIONS_START_BYTE_ORDER = 16;

}
}


namespace trace_out
{

	const detail::option_t BIN = static_cast<detail::option_t>(0x1) << (detail::OPTIONS_START_BASE + 0);
	const detail::option_t SDEC = static_cast<detail::option_t>(0x1) << (detail::OPTIONS_START_BASE + 1);
	const detail::option_t UDEC = static_cast<detail::option_t>(0x1) << (detail::OPTIONS_START_BASE + 2);
	const detail::option_t HEX = static_cast<detail::option_t>(0x1) << (detail::OPTIONS_START_BASE + 3);
	const detail::option_t FLT = static_cast<detail::option_t>(0x1) << (detail::OPTIONS_START_BASE + 4);
	const detail::option_t DBL = static_cast<detail::option_t>(0x1) << (detail::OPTIONS_START_BASE + 5);
	const detail::option_t LDBL = static_cast<detail::option_t>(0x1) << (detail::OPTIONS_START_BASE + 6);

	const detail::option_t LITTLE = static_cast<detail::option_t>(0x1) << (detail::OPTIONS_START_BYTE_ORDER + 0);
	const detail::option_t BIG = static_cast<detail::option_t>(0x1) << (detail::OPTIONS_START_BYTE_ORDER + 1);

}


namespace trace_out { namespace detail
{

	extern const char *const BASE_NAMES[];
	extern const standard::size_t BASE_NAMES_LENGTH;

	extern const char *const BYTE_ORDER_NAMES[];
	extern const standard::size_t BYTE_ORDER_NAMES_LENGTH;

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
		static const option_t default_base = HEX;
		typedef void signed_t;
		typedef void unsigned_t;
	};

#define TRACE_OUT__DEFINE_PRINT_TRAITS(family, type_size, is_signed, unit_type, field_width_value, default_base_value, to_signed_type, to_unsigned_type) \
		template <> \
		struct print_traits_details<family, type_size, is_signed> \
		{ \
			typedef unit_type unit_t; \
			static const outputwidth_t field_width = field_width_value; \
			static const option_t default_base = default_base_value; \
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


	option_t base_value_from_options(option_t options, option_t default_value);
	option_t byte_order_value_from_options(option_t options, option_t default_value);
	const char *option_name(option_t option, const char *const names[], standard::size_t names_length, const char *default_name);
	const char *byte_to_binary(standard::uint8_t byte);
	const char *byte_to_hexadecimal(standard::uint8_t byte);

	template <typename Type_t>
	outputwidth_t field_width(option_t base);

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
	const std::string (*select_conversion(option_t base))(Type_t);

	option_t current_byte_order();
	void reverse_bytes(void *destination, const void *source, standard::size_t size);
	void order_bytes(void *ordered_bytes, const void *unordered_bytes, standard::size_t size, option_t byte_order);

	template <typename Type_t>
	void print_memory(const std::string &filename_line, const char *name, const Type_t *pointer, standard::size_t size = sizeof(Type_t), option_t options = 0);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	outputwidth_t field_width(option_t base)
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
	const std::string (*select_conversion(option_t base))(Type_t)
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
	void print_memory_contents(out_stream &stream, const Type_t *pointer, standard::size_t size, outputwidth_t column_width, const std::string (*bytes_to_string)(Type_t), option_t byte_order)
	{
		std::stringstream string_stream;

		const Type_t *iterator = pointer;
		standard::size_t length = size / sizeof(Type_t);

		stream << make_pretty(static_cast<const void *>(iterator)) << ":";
		for (standard::size_t index = 0; index < length; ++index)
		{
			const std::string string_representation = string_stream.str();
			if (string_representation.length() + static_cast<standard::size_t>(column_width) + 1 > stream.width_left())
			{
				stream << string_representation;
				string_stream.str("");

				stream << NEWLINE << make_pretty(static_cast<const void *>(&iterator[index])) << ":";
			}

			const Type_t &bytes = iterator[index];

			crash_on_bad_memory(bytes);

			Type_t ordered_bytes;
			order_bytes(&ordered_bytes, &bytes, sizeof(Type_t), byte_order);

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
	void print_memory(const std::string &filename_line, const char *name, const Type_t *pointer, standard::size_t size, option_t options)
	{
		typedef typename print_traits<Type_t>::unit_t unit_t;

		option_t base = base_value_from_options(options, print_traits<Type_t>::default_base);
		option_t byte_order = byte_order_value_from_options(options, current_byte_order());

		const char *base_name = option_name((base >> OPTIONS_START_BASE), BASE_NAMES, BASE_NAMES_LENGTH, "?");
		const char *byte_order_name = option_name((byte_order >> OPTIONS_START_BYTE_ORDER), BYTE_ORDER_NAMES, BYTE_ORDER_NAMES_LENGTH, "?");

		out_stream stream(filename_line);
		stream << name << " (" << base_name << ", " << byte_order_name << "):";
		indentation_add();
		stream << NEWLINE;

		const std::string (*bytes_to_string)(Type_t) = select_conversion<Type_t>(base);
		outputwidth_t column_width = field_width<Type_t>(base);
		print_memory_contents(stream, static_cast<const unit_t *>(pointer), size, column_width, bytes_to_string, byte_order);

		indentation_remove();

		stream << ENDLINE;
	}

}
}


namespace trace_out { namespace detail
{

	class auto_indentation
	{
	public:
		auto_indentation();
		~auto_indentation();
	};


	class block
	{
	public:
		block(bool value);
		block(const block &another);
		~block();

		operator bool() const;

	private:
		block &operator =(const block &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L

		block &operator =(block &&another); // = delete

#endif // TRACE_OUT_CPP_VERSION >= 201103L

		bool _value;
	};


	class if_block
	{
	public:
		if_block(bool value);
		if_block(const if_block &another);
		~if_block();

		operator bool() const;

	private:
		if_block &operator =(const if_block &another); // = delete

#if TRACE_OUT_CPP_VERSION >= 201103L

		if_block &operator =(if_block &&another); // = delete

#endif

	private:
		bool _value;
	};


	template <typename Type_t>
	if_block make_if_block(const std::string &filename_line, const char *condition, const Type_t &value);

	block iteration_block(const std::string &filename_line, const char *loop, standard::size_t iteration);


	class loop_block
	{
	public:
		loop_block(const std::string &filename_line, const char *expression);
		~loop_block();

		operator bool() const;
		standard::size_t iteration();

	private:
		const char *_expression;
		standard::size_t _iteration_number;
	};


	loop_block make_loop_block(const std::string &filename_line, const char *expression);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	if_block make_if_block(const std::string &filename_line, const char *condition, const Type_t &value)
	{
		out_stream stream(filename_line);
		stream << "if (" << condition << ") => " << FLUSH;
		stream << make_pretty_condition(value) << ENDLINE;

		return if_block(!!value);
	}

}
}


namespace trace_out { namespace detail
{

	void print_execution_time_in_milliseconds(const std::string &filename_line, const char *label, standard::uint64_t milliseconds);
	void print_execution_time_in_clocks(const std::string &filename_line, const char *label, std::clock_t clocks, double milliseconds);

	void print_execution_statistics(const std::string &filename_line, const char *label, std::vector<standard::uint64_t> &results, const char *units);
}
}


namespace trace_out { namespace detail { namespace system
{

	standard::uint64_t time_in_milliseconds();

}
}
}


#if defined(TRACE_OUT_CLANG)

	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
	#pragma clang diagnostic ignored "-Wvariadic-macros"
	#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

#elif defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wvariadic-macros" // seems it does not turn off the warning if there's no C++11

#endif


#if (!defined(NDEBUG) && !defined(TRACE_OUT_OFF)) || defined(TRACE_OUT_ON)

	#define $e(...) \
				trace_out::detail::expression(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__, ##__VA_ARGS__)

	#define $w(...) \
				trace_out::detail::watch(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__, ##__VA_ARGS__);

	#define $r(begin, end_OR_how_much) \
				trace_out::detail::range(TRACE_OUT_FILENAME_LINE, #begin, #end_OR_how_much, (begin), (end_OR_how_much));

	#define $m(pointer, ...) \
				trace_out::detail::print_memory(TRACE_OUT_FILENAME_LINE, #pointer, pointer, ##__VA_ARGS__);

	#define $f \
				trace_out::detail::function_printer trace_out_private__unify(trace_out_f) = trace_out::detail::make_function_printer(TRACE_OUT_FILENAME_LINE, trace_out_private__strip_namespaces(TRACE_OUT_FUNCTION_SIGNATURE));

	#define $return \
				return trace_out::detail::make_return_printer(TRACE_OUT_FILENAME_LINE) ,

	#define $if(...) \
				if (trace_out::detail::if_block trace_out_private__unify(trace_out_if_block) = trace_out::detail::make_if_block(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__, (__VA_ARGS__)))

	#define trace_out_private__loop(block_variable_name, loop, ...) \
				if (trace_out::detail::loop_block block_variable_name = trace_out::detail::make_loop_block(TRACE_OUT_FILENAME_LINE, #loop" ("#__VA_ARGS__")")) {} else \
					loop (__VA_ARGS__) \
						if (trace_out::detail::block trace_out_private__unify(trace_out_iteration_block) = trace_out::detail::iteration_block(TRACE_OUT_FILENAME_LINE, #loop, block_variable_name.iteration())) {} else

	#define $for(...) \
				trace_out_private__loop(trace_out_private__unify(trace_out_for_block), for, ##__VA_ARGS__)

	#define $while(...) \
				trace_out_private__loop(trace_out_private__unify(trace_out_for_block), while, ##__VA_ARGS__)

	#define $t(...) \
				trace_out::detail::out_stream stream(TRACE_OUT_FILENAME_LINE); \
				stream << #__VA_ARGS__ << trace_out::detail::FLUSH; \
				__VA_ARGS__ \
				stream << " // trace-out: statement passed" << trace_out::detail::ENDLINE;

	#define $p(format, ...) \
				{ \
					trace_out::detail::out_stream stream(TRACE_OUT_FILENAME_LINE); \
					stream.printf(format, ##__VA_ARGS__); \
					stream << trace_out::detail::ENDLINE; \
				}

	#define $thread(name) \
				trace_out::detail::set_current_thread_name(#name);

	#define trace_out_private__time(start_time, execution_time, label, ...) \
				trace_out::detail::standard::uint64_t start_time = trace_out::detail::system::time_in_milliseconds(); \
				__VA_ARGS__ \
				trace_out::detail::standard::uint64_t execution_time = trace_out::detail::system::time_in_milliseconds() - start_time; \
				trace_out::detail::print_execution_time_in_milliseconds(TRACE_OUT_FILENAME_LINE, label, execution_time);

	#define $time(label, ...) \
				trace_out_private__time(trace_out_private__unify(trace_out_start_time), trace_out_private__unify(trace_out_end_time), label, ##__VA_ARGS__)

	#define trace_out_private__clocks(start_clocks, execution_clocks, label, ...) \
				std::clock_t start_clocks = std::clock(); \
				__VA_ARGS__ \
				std::clock_t execution_clocks = std::clock() - start_clocks; \
				trace_out::detail::print_execution_time_in_clocks(TRACE_OUT_FILENAME_LINE, label, execution_clocks, static_cast<double>(execution_clocks) / CLOCKS_PER_SEC * 1000.0);

	#define $clocks(label, ...) \
				trace_out_private__clocks(trace_out_private__unify(trace_out_start_clocks), trace_out_private__unify(trace_out_execution_clocks), label, ##__VA_ARGS__)

	#define trace_out_private__time_stats(start_time, execution_time, results, measurements, label, passes, ...) \
				static std::vector<trace_out::detail::standard::uint64_t> results; \
				results.reserve(passes); \
				trace_out::detail::standard::uint64_t start_time = trace_out::detail::system::time_in_milliseconds(); \
				__VA_ARGS__ \
				trace_out::detail::standard::uint64_t execution_time = trace_out::detail::system::time_in_milliseconds() - start_time; \
				results.push_back(execution_time); \
				if (results.size() == passes) \
				{ \
					trace_out::detail::print_execution_statistics(TRACE_OUT_FILENAME_LINE, label, results, "ms"); \
					results.clear(); \
				}

	#define $time_stats(label, passes, ...) \
				trace_out_private__time_stats(trace_out_private__unify(trace_out_start_time), trace_out_private__unify(trace_out_execution_time), trace_out_private__unify(results), trace_out_private__unify(trace_out_measurements), label, passes, ##__VA_ARGS__)

	#define trace_out_private__clock_stats(start_time, execution_time, results, measurements, label, passes, ...) \
				static std::vector<trace_out::detail::standard::uint64_t> results; \
				results.reserve(passes); \
				trace_out::detail::standard::uint64_t start_time = trace_out::detail::system::time_in_milliseconds(); \
				__VA_ARGS__ \
				trace_out::detail::standard::uint64_t execution_time = trace_out::detail::system::time_in_milliseconds() - start_time; \
				results.push_back(execution_time); \
				if (results.size() == passes) \
				{ \
					trace_out::detail::print_execution_statistics(TRACE_OUT_FILENAME_LINE, label, results, "clocks"); \
					results.clear(); \
				}

	#define $clock_stats(label, passes, ...) \
				trace_out_private__clock_stats(trace_out_private__unify(trace_out_start_time), trace_out_private__unify(trace_out_execution_time), trace_out_private__unify(results), trace_out_private__unify(trace_out_measurements), label, passes, ##__VA_ARGS__)

#elif defined(NDEBUG) || defined(TRACE_OUT_OFF)

	#define $e(...) \
				__VA_ARGS__

	#define $w(...)

	#define $r(...)

	#define $m(pointer, ...)

	#define $f

	#define $return \
				return

	#define $if(...) \
				if (__VA_ARGS__)

	#define $for(...) \
				for (__VA_ARGS__)

	#define $while(...) \
				while (__VA_ARGS__)

	#define $p(format, ...)

	#define $t(...) \
				__VA_ARGS__

	#define $thread(name)

	#define $time(label, ...) \
				__VA_ARGS__

	#define $clocks(label, ...) \
				__VA_ARGS__

	#define $time_stats(label, how_much, ...)

	#define $clock_stats(label, how_much, ...)

#endif


#if defined(TRACE_OUT_CLANG)

	#pragma clang diagnostic pop

#elif defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)

	#pragma GCC diagnostic pop

#endif


namespace trace_out { namespace detail
{

	template <typename Type_t>
	struct valdist_t
	{
		Type_t value;
		unsigned int occurances;

		valdist_t(Type_t value, unsigned int occurances);
	};


	template <typename Type_t>
	struct compare_distributions
	{
		bool operator ()(const valdist_t<Type_t> &first, const valdist_t<Type_t> &second);
	};


	template <typename Type_t, typename Iterator_t>
	Type_t average_value(Iterator_t begin, Iterator_t end);

	template <typename Type_t, typename Iterator_t>
	Type_t median_value(Iterator_t begin, Iterator_t end);

	template <typename Type_t, typename Iterator_t>
	std::vector<valdist_t<Type_t> > values_distribution(Iterator_t begin, Iterator_t end);

	template <typename Type_t, typename Iterator_t>
	std::pair<std::vector<Type_t>, unsigned int> mode_values(Iterator_t begin, Iterator_t end);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	valdist_t<Type_t>::valdist_t(Type_t value, unsigned int occurances)
		:
		value(value),
		occurances(occurances)
	{
	}


	template <typename Type_t>
	bool compare_distributions<Type_t>::operator ()(const valdist_t<Type_t> &first, const valdist_t<Type_t> &second)
	{
		return first.occurances < second.occurances;
	}


	template <typename Type_t, typename Iterator_t>
	Type_t average_value(Iterator_t begin, Iterator_t end)
	{
		Type_t full_time = std::accumulate(begin, end, Type_t(0));
		return static_cast<Type_t>(full_time) / static_cast<Type_t>(std::distance(begin, end));
	}


	template <typename Type_t, typename Iterator_t>
	Type_t median_value(Iterator_t begin, Iterator_t end)
	{
		assert(begin != end);

		typename Iterator_t::difference_type size = std::distance(begin, end);
		assert(size > 0);

		std::size_t half_size = static_cast<std::size_t>(size / 2);
		if (size % 2 == 0)
		{
			Iterator_t next = begin;
			std::advance(begin, half_size - 1);
			std::advance(next, half_size);
			return static_cast<Type_t>(*begin + *next) / Type_t(2);
		}
		else
		{
			std::advance(begin, half_size);
			return static_cast<Type_t>(*begin);
		}
	}


	template <typename Type_t, typename Iterator_t>
	std::vector<valdist_t<Type_t> > values_distribution(Iterator_t begin, Iterator_t end)
	{
		if (begin == end)
		{
			return std::vector<valdist_t<Type_t> >();
		}

		std::vector<valdist_t<Type_t> > distributions;
		Type_t current_value = *begin;
		distributions.push_back(valdist_t<Type_t>(current_value, 1));

		for (++begin; begin != end; ++begin)
		{
			if (*begin != current_value)
			{
				current_value = *begin;
				distributions.push_back(valdist_t<Type_t>(current_value, 1));
				continue;
			}

			++(distributions.back().occurances);
		}

		return distributions;
	}


	template <typename Type_t, typename Iterator_t>
	std::pair<std::vector<Type_t>, unsigned int> mode_values(Iterator_t begin, Iterator_t end)
	{
		std::vector<valdist_t<standard::uint64_t> > distributions = values_distribution<standard::uint64_t>(begin, end);

		unsigned int max_occurances = std::max_element(distributions.begin(), distributions.end(), compare_distributions<Type_t>())->occurances;
		std::vector<Type_t> modes;
		for (typename std::vector<valdist_t<Type_t> >::const_iterator itr = distributions.cbegin(); itr != distributions.cend(); ++itr)
		{
			if (itr->occurances == max_occurances)
			{
				modes.push_back(itr->value);
			}
		}

		return std::pair<std::vector<Type_t>, unsigned int>(modes, max_occurances);
	}

}
}


namespace trace_out { namespace detail
{

#if defined(TRACE_OUT_INDENTATION)
	const char INDENTATION[] = TRACE_OUT_INDENTATION;
#else
	const char INDENTATION[] = "    ";
#endif

#if defined(TRACE_OUT_MARKER)
	const char MARKER[] = TRACE_OUT_MARKER " ";
#else
	const char MARKER[] = "";
#endif

	const char THREAD_HEADER_SEPARATOR = '~';
	const char FILENAME_FIELD_EXCESS_PADDING[] = "~";
	const standard::size_t FILENAME_FIELD_EXCESS_PADDING_SIZE = sizeof(FILENAME_FIELD_EXCESS_PADDING);
	const standard::size_t FILENAME_FIELD_WIDTH = 20;
	const standard::size_t LINE_FIELD_WIDTH = 4;
	const char DELIMITER[] = " |  ";
	const standard::size_t INDENTATION_WIDTH = sizeof(INDENTATION) - 1;

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	class resource
	{
	public:
		typedef void (*deleter_t)(Type_t);

		resource(Type_t handle, deleter_t deleter);
		~resource();

		const Type_t &get() const;

	private:
		resource();
		resource(const resource &);
		resource &operator =(const resource &);

#if TRACE_OUT_CPP_VERSION >= 201103L

		resource(resource &&another);
		resource &operator =(resource &&another);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

		Type_t _handle;
		deleter_t _deleter;
	};

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	resource<Type_t>::resource(Type_t handle, deleter_t deleter)
		:
		_handle(handle),
		_deleter(deleter)
	{
	}


	template <typename Type_t>
	resource<Type_t>::~resource()
	{
		_deleter(_handle);
	}


	template <typename Type_t>
	const Type_t &resource<Type_t>::get() const
	{
		return _handle;
	}

}
}


namespace trace_out { namespace detail { namespace standard
{

	size_t vsnprintf_string_length(const char *format, va_list arguments);
	int vsnprintf(char *buffer, size_t size, const char *format, va_list arguments);

}
}
}


namespace trace_out { namespace detail { namespace system
{

	typedef struct _tlskey *tlskey_t;

	tlskey_t tls_new_key();
	void tls_delete_key(tlskey_t key);
	void *tls_get(tlskey_t key);
	void tls_set(tlskey_t key, void *data);


	template <typename Type_t>
	class tls
	{
	public:
		tls();
		~tls();

		void set(const Type_t &value);
		const Type_t &get() const;

	private:
		tls(const tls &another);
		tls &operator =(const tls &another);

#if TRACE_OUT_CPP_VERSION >= 201103L

		tls(tls &&another);
		tls &operator =(tls &&another);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

		resource<tlskey_t> _key;
	};

}
}
}


namespace trace_out { namespace detail { namespace system
{

	template <typename Type_t>
	tls<Type_t>::tls()
		:
		_key(tls_new_key(), tls_delete_key)
	{
	}


	template <typename Type_t>
	tls<Type_t>::~tls()
	{
		Type_t *value = static_cast<Type_t *>(tls_get(_key.get()));
		delete value;
	}


	template <typename Type_t>
	void tls<Type_t>::set(const Type_t &value)
	{
		Type_t *new_value = new Type_t(value);

		Type_t *old_value = static_cast<Type_t *>(tls_get(_key.get()));
		delete old_value;

		tls_set(_key.get(), new_value);
	}


	template <typename Type_t>
	const Type_t &tls<Type_t>::get() const
	{
		Type_t *value = static_cast<Type_t *>(tls_get(_key.get()));
		if (value == NULL)
		{
			value = new Type_t;
			tls_set(_key.get(), value);
		}

		return *value;
	}

}
}
}


namespace trace_out { namespace detail { namespace system
{

	int console_width();

}
}
}


namespace trace_out { namespace detail { namespace system
{

	extern const char FILE_PATH_COMPONENT_DELIMITER;

}
}
}


namespace trace_out { namespace detail { namespace system
{

	typedef struct _mutex *mutex_t;

	mutex_t mutex_new();
	void mutex_delete(mutex_t mutex);
	void mutex_lock(mutex_t mutex);
	void mutex_unlock(mutex_t mutex);


	class mutex
	{
	public:
		mutex();

		void lock();
		void unlock();

	private:
		mutex(const mutex &another);
		mutex &operator =(const mutex &another);

#if TRACE_OUT_CPP_VERSION >= 201103L

		mutex(mutex &&another);
		mutex &operator =(mutex &&another);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

		resource<mutex_t> _handle;
	};

}
}
}


namespace trace_out { namespace detail { namespace system
{

	standard::uint64_t current_thread_id();

}
}
}

