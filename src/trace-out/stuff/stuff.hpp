#pragma once

#include <cstdarg>
#include <cstring>
#include <string>
#include <ios>
#include <sstream>

#include "trace-out/standard/integer.hpp"
#include "trace-out/stuff/platform-detection.hpp"


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

	struct nothing {};

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

}
}

