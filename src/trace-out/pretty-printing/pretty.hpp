#pragma once

#include <string>

#include "trace-out/stuff/platform-detection.hpp"
#include "trace-out/stuff/stuff.hpp"


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

