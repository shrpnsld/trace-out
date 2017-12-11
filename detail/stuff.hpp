#pragma once

#include <cstdarg>
#include <cstring>
#include <string>
#include <ios>
#include <sstream>

#include "standard/integer.hpp"
#include "platform_defines.hpp"


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

#if defined(TRACE_OUT_CPP11)

	trace_out__define_is_fundamental(signed long long);
	trace_out__define_is_fundamental(unsigned long long);

#endif // defined(TRACE_OUT_CPP11)

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


#if defined(TRACE_OUT_CPP11)

	// need this to fix printing of std::tuple
	template <typename ...Types_t>
	struct sizeof_pack
	{
		enum
		{
			value = sizeof...(Types_t)
		};
	};

#endif // defined(TRACE_OUT_CPP11)


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

	trace_out_private__define_has_member(WIDTH);
	trace_out_private__define_has_member(HEIGHT);

	trace_out_private__define_has_member(origin);
	trace_out_private__define_has_member(size);

	trace_out_private__define_has_member(Origin);
	trace_out_private__define_has_member(Size);

	trace_out_private__define_has_member(ORIGIN);
	trace_out_private__define_has_member(SIZE);

	trace_out_private__define_has_member(real);
	trace_out_private__define_has_member(imag);

	trace_out_private__define_has_member(Real);
	trace_out_private__define_has_member(Imag);

	trace_out_private__define_has_member(REAL);
	trace_out_private__define_has_member(IMAG);

	trace_out_private__define_has_member(begin);
	trace_out_private__define_has_member(end);

#undef trace_out_private__define_has_member


	template <typename Type_t>
	struct is_dimensional
	{
		enum
		{
			value = has_member_x<Type_t>::value || has_member_X<Type_t>::value || has_member_width<Type_t>::value || has_member_Width<Type_t>::value || has_member_WIDTH<Type_t>::value || has_member_origin<Type_t>::value || has_member_Origin<Type_t>::value || has_member_ORIGIN<Type_t>::value || has_member_real<Type_t>::value || has_member_Real<Type_t>::value || has_member_REAL<Type_t>::value
		};
	};


	template <typename Type_t>
	struct is_iterable
	{
		enum
		{
			value = has_member_begin<Type_t>::value && has_member_end<Type_t>::value && !is_same<Type_t, std::string>::value
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

