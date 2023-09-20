#pragma once

#include <cstring>

#include "trace-out/standard/integer.hpp"


namespace trace_out { namespace detail
{

	struct nothing {};

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

