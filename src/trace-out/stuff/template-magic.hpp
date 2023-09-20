#pragma once

namespace trace_out { namespace detail
{

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
		struct yes
		{
			unsigned char field[2];
		};

		struct no
		{
			unsigned char field[1];
		};

		template <typename Some_t>
		static yes do_check(int Some_t::*);

		template <typename Some_t>
		static no do_check(...);

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

