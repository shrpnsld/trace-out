#pragma once

#include "trace-out/platform-detection.hpp"

//
// Public

namespace trace_out
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

