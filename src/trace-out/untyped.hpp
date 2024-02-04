#pragma once

#include "trace-out/integer.hpp"
#include <cstring>

namespace trace_out
{

template <standard::size_t Size = sizeof(void *)>
class untyped
{
public:
	untyped();

	template <typename Type_t>
	untyped(Type_t value);

	untyped(const untyped &another);

	untyped &operator =(const untyped &another);

	template <typename Type_t>
	untyped &operator =(Type_t value);

	template <typename Type_t>
	operator Type_t() const;

	bool operator ==(const untyped &another) const;
	bool operator !=(const untyped &another) const;

private:
	unsigned char _storage[Size];
};


template <typename standard::size_t Size, typename Type_t>
bool operator ==(untyped<Size> something, const Type_t &value);

template <typename standard::size_t Size, typename Type_t>
bool operator ==(const Type_t &value, untyped<Size> something);

template <typename standard::size_t Size, typename Type_t>
bool operator !=(untyped<Size> something, const Type_t &value);

template <typename standard::size_t Size, typename Type_t>
bool operator !=(const Type_t &value, untyped<Size> something);

}


namespace trace_out
{

template <standard::size_t Size>
untyped<Size>::untyped()
{
	std::memset(_storage, 0, sizeof(_storage));
}


template <standard::size_t Size>
template <typename Type_t>
untyped<Size>::untyped(Type_t value)
{
	*reinterpret_cast<Type_t *>(_storage) = value;
}


template <standard::size_t Size>
untyped<Size>::untyped(const untyped &another)
{
	std::memcpy(_storage, another._storage, sizeof(_storage));
}


template <standard::size_t Size>
untyped<Size> &untyped<Size>::operator =(const untyped &another)
{
	std::memcpy(_storage, another._storage, sizeof(_storage));
	return *this;
}

template <standard::size_t Size>
template <typename Type_t>
untyped<Size> &untyped<Size>::operator =(Type_t value)
{
	*reinterpret_cast<Type_t *>(_storage) = value;
	return *this;
}


template <standard::size_t Size>
template <typename Type_t>
untyped<Size>::operator Type_t() const
{
	return *reinterpret_cast<const Type_t *>(_storage);
}


template <standard::size_t Size>
bool untyped<Size>::operator ==(const untyped &another) const
{
	return std::memcmp(_storage, another._storage, sizeof(_storage)) == 0;
}


template <standard::size_t Size>
bool untyped<Size>::operator !=(const untyped &another) const
{
	return std::memcmp(_storage, another._storage, sizeof(_storage)) != 0;
}


template <standard::size_t Size, typename Type_t>
bool operator ==(untyped<Size> something, const Type_t &value)
{
	return static_cast<Type_t>(something) == value;
}


template <standard::size_t Size, typename Type_t>
bool operator ==(const Type_t &value, untyped<Size> something)
{
	return static_cast<Type_t>(something) == value;
}

template <standard::size_t Size, typename Type_t>
bool operator !=(untyped<Size> something, const Type_t &value)
{
	return static_cast<Type_t>(something) != value;
}


template <standard::size_t Size, typename Type_t>
bool operator !=(const Type_t &value, untyped<Size> something)
{
	return static_cast<Type_t>(something) != value;
}

}

