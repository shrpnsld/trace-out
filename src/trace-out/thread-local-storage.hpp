#pragma once

#include "trace-out/platform-detection.hpp"
#include "trace-out/resource.hpp"

//
// Public

namespace trace_out { namespace system
{

typedef struct _tlskey_t *tlskey_t;

inline tlskey_t tls_new_key();
inline void tls_delete_key(tlskey_t key);
inline void *tls_get(tlskey_t key);
inline void tls_set(tlskey_t key, void *data);

template <typename Type_t>
class tls
{
public:
	tls();
	~tls();

	void set(const Type_t &value);
	const Type_t &get(const Type_t &default_value = Type_t()) const;

private:
	tls(const tls &another);
	tls &operator =(const tls &another);

#if TRACE_OUT_CPP_VERSION >= 201103L

	tls(tls &&another);
	tls &operator =(tls &&another);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	resource<tlskey_t> _key;
};

}
}

//
// Implementation

namespace trace_out { namespace system
{

template <typename Type_t>
tls<Type_t>::tls()
	:
	_key(tls_new_key(), tls_delete_key)
{
}

template <typename Type_t>
tls<Type_t>::~tls()
{
	Type_t *value = static_cast<Type_t *>(tls_get(_key.get()));
	delete value;
}

template <typename Type_t>
void tls<Type_t>::set(const Type_t &value)
{
	Type_t *new_value = new Type_t(value);

	Type_t *old_value = static_cast<Type_t *>(tls_get(_key.get()));
	delete old_value;

	tls_set(_key.get(), new_value);
}

template <typename Type_t>
const Type_t &tls<Type_t>::get(const Type_t &default_value) const
{
	Type_t *value = static_cast<Type_t *>(tls_get(_key.get()));
	if (value == NULL)
	{
		value = new Type_t(default_value);
		tls_set(_key.get(), value);
	}

	return *value;
}

}
}

#if defined(TRACE_OUT_POSIX)

//
// POSIX implementation

#include <cassert> // [amalgamate:leave]
#include <cstddef>
#include <pthread.h> // [amalgamate:leave]

namespace trace_out { namespace system
{

struct _tlskey_t
{
	pthread_key_t value;
};

tlskey_t tls_new_key()
{
	tlskey_t key = new _tlskey_t;
	int retval = pthread_key_create(&key->value, NULL);
	assert(retval == 0);

	return key;
}

void tls_delete_key(tlskey_t key)
{
	int retval = pthread_key_delete(key->value);
	assert(retval == 0);

	delete key;
}

void *tls_get(tlskey_t key)
{
	return pthread_getspecific(key->value);
}

void tls_set(tlskey_t key, void *data)
{
	int retval = pthread_setspecific(key->value, data);
	assert(retval == 0);
}

}
}

#elif defined(TRACE_OUT_WINDOWS)

//
// WinAPI implementation

#include "trace-out/windows-headers.hpp"
#include <cassert> // [amalgamate:leave]

namespace trace_out { namespace system
{

struct _tlskey_t
{
	DWORD value;
};

tlskey_t tls_new_key()
{
	tlskey_t key = new _tlskey_t;
	DWORD retval = TlsAlloc();
	assert(retval != TLS_OUT_OF_INDEXES);

	key->value = retval;
	return key;
}

void tls_delete_key(tlskey_t key)
{
	int retval = TlsFree(key->value);
	assert(retval != 0);

	delete key;
}

void *tls_get(tlskey_t key)
{
	return TlsGetValue(key->value);
}

void tls_set(tlskey_t key, void *data)
{
	BOOL retval = TlsSetValue(key->value, data);
	assert(retval != 0);
}

}
}

#endif

