#pragma once

#include <cstdarg>
#include <cstring>
#include <string>
#include <ios>
#include <sstream>

#include "trace-out/detail/standard/integer.hpp"
#include "trace-out/detail/stuff/platform-detection.hpp"


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
	struct is_fundamental
	{
		enum
		{
			value = false
		};
	};


#define trace_out__define_is_fundamental(type) \
			template <> \
			struct is_fundamental<type> \
			{ \
				enum \
				{ \
					value = true \
				}; \
			}


	trace_out__define_is_fundamental(bool);
	trace_out__define_is_fundamental(char);
	trace_out__define_is_fundamental(signed char);
	trace_out__define_is_fundamental(unsigned char);
	trace_out__define_is_fundamental(signed short int);
	trace_out__define_is_fundamental(unsigned short int);
	trace_out__define_is_fundamental(signed int);
	trace_out__define_is_fundamental(unsigned int);
	trace_out__define_is_fundamental(signed long int);
	trace_out__define_is_fundamental(unsigned long int);

#if TRACE_OUT_CPP_VERSION >= 201103L

	trace_out__define_is_fundamental(signed long long);
	trace_out__define_is_fundamental(unsigned long long);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	trace_out__define_is_fundamental(float);
	trace_out__define_is_fundamental(double);
	trace_out__define_is_fundamental(long double);

#undef trace_out__define_is_fundamental


	template <typename Type_t>
	struct is_pointer
	{
		enum
		{
			value = false
		};
	};


	template <typename Type_t>
	struct is_pointer<Type_t *>
	{
		enum
		{
			value = true
		};
	};



	template <typename Type_t>
	struct is_primitive
	{
		enum
		{
			value = is_fundamental<Type_t>::value || is_pointer<Type_t>::value
		};
	};



	template <typename Type_t>
	struct is_array;


	template <typename Type_t>
	struct is_array<Type_t[]>
	{
		enum
		{
			value = true
		};
	};


	template <typename Type_t, standard::size_t Size>
	struct is_array<Type_t[Size]>
	{
		enum
		{
			value = true
		};
	};


	template <typename Type_t>
	struct is_array
	{
		enum
		{
			value = false
		};
	};



	template <typename Type_t>
	struct is_structural
	{
		enum
		{
			value = !(is_primitive<Type_t>::value || is_array<Type_t>::value)
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
				struct check; \
				\
				template <typename Type_t> \
				static char (&function(check<int fallback::*, &Type_t::name> *))[1]; \
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
	trace_out_private__define_has_member(BoxExtent);
	trace_out_private__define_has_member(SphereRadius);

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
		has_member_begin<Type_t>::value && has_member_end<Type_t>::value);


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

	// FBox/FBox2D
	trace_out_private__define_has_members(Min_Max_bIsValid, Type_t,
		has_member_Min<Type_t>::value && has_member_Max<Type_t>::value && has_member_bIsValid<Type_t>::value);

	// FSphere
	trace_out_private__define_has_members(Center_W, Type_t,
		has_member_Center<Type_t>::value && has_member_W<Type_t>::value);

	// FCapsuleSphere
	trace_out_private__define_has_members(Center_Radius_Orientation_Length, Type_t,
		has_member_Center<Type_t>::value && has_member_Radius<Type_t>::value && has_member_Orientation<Type_t>::value && has_member_Length<Type_t>::value);

	// FOrientedBox
	trace_out_private__define_has_members(Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ, Type_t,
		has_member_Center<Type_t>::value && has_member_AxisX<Type_t>::value && has_member_AxisY<Type_t>::value && has_member_AxisZ<Type_t>::value && has_member_ExtentX<Type_t>::value && has_member_ExtentY<Type_t>::value && has_member_ExtentZ<Type_t>::value);

	// FBoxSphereBounds
	trace_out_private__define_has_members(Origin_BoxExtent_SphereRadius, Type_t,
		has_member_Origin<Type_t>::value && has_member_BoxExtent<Type_t>::value && has_member_SphereRadius<Type_t>::value);

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
				has_members_Center_W<Type_t>::value ||
				has_members_Center_Radius_Orientation_Length<Type_t>::value ||
				has_members_Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ<Type_t>::value ||
				has_members_Origin_BoxExtent_SphereRadius<Type_t>::value
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

