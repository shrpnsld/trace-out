#pragma once

#include "trace-out/platform-detection.hpp"

//
// Public

namespace trace_out
{

struct move_tag
{
} MOVE_RESOURCE;


template <typename Type_t>
class resource
{
public:
	typedef void (*deleter_t)(Type_t);

	resource(Type_t handle, deleter_t deleter);
	resource(const resource &); // no implementation, so linker throws error if copy constructor is being called
	resource(const resource &another, move_tag);
	~resource();

	const Type_t &get() const;

private:
	resource();
	resource &operator =(const resource &);

#if TRACE_OUT_CPP_VERSION >= 201103L

	resource(resource &&another);
	resource &operator =(resource &&another);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	Type_t _handle;
	deleter_t _deleter;
};

}

//
// Private

namespace trace_out
{

template <typename Type_t>
Type_t move_fundamental(Type_t &from, Type_t zero = Type_t());

}

//
// Implementation

namespace trace_out
{

template <typename Type_t>
resource<Type_t>::resource(Type_t handle, deleter_t deleter)
	:
	_handle(handle),
	_deleter(deleter)
{
}

template <typename Type_t>
resource<Type_t>::resource(const resource &another, move_tag)
	:
	_handle(move_fundamental(const_cast<resource<Type_t> &>(another)._handle)),
	_deleter(move_fundamental(const_cast<resource<Type_t> &>(another)._deleter))
{
}

template <typename Type_t>
resource<Type_t>::~resource()
{
	if (_deleter != NULL)
	{
		_deleter(_handle);
	}
}

template <typename Type_t>
const Type_t &resource<Type_t>::get() const
{
	return _handle;
}

template <typename Type_t>
Type_t move_fundamental(Type_t &from, Type_t zero)
{
	Type_t value = from;
	from = zero;
	return value;
}

}

