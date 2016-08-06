#pragma once

#include <string>

#include "platform_defines.hpp"
#include "stuff.hpp"


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

#if defined(TRACE_OUT_CPP11)

		pretty &operator =(pretty &&another); // = delete

#endif // defined(TRACE_OUT_CPP11)

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

#if defined(TRACE_OUT_CPP11)

		pretty_condition &operator =(pretty_condition &&another); // = delete

#endif // defined(TRACE_OUT_CPP11)

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

#if defined(TRACE_OUT_CPP11)

		pretty_structural &operator =(pretty_structural &&another); // = delete

#endif // defined(TRACE_OUT_CPP11)

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

#if defined(TRACE_OUT_CPP11)

		pretty_iterable &operator =(pretty_iterable &&another); // = delete

#endif // defined(TRACE_OUT_CPP11)

		const Type_t &_data;
	};



	template <typename Type_t>
	typename enable_if<!is_iterable<Type_t>::value && is_dimensional<Type_t>::value, pretty_structural<Type_t> >::type make_pretty(const Type_t &value)
	{
		return pretty_structural<Type_t>(value);
	}


	template <typename Type_t>
	typename enable_if<is_iterable<Type_t>::value && !is_same<Type_t, std::string>::value, pretty_iterable<Type_t> >::type make_pretty(const Type_t &value)
	{
		return pretty_iterable<Type_t>(value);
	}


	template <typename Type_t>
	typename enable_if<!is_iterable<Type_t>::value && !is_dimensional<Type_t>::value, pretty<Type_t> >::type make_pretty(const Type_t &value)
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

}
}

