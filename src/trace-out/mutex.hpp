#pragma once

#include "trace-out/platform-detection.hpp"
#include "trace-out/resource.hpp"

//
// Public

namespace trace_out { namespace system
{

typedef struct _mutex_t *mutex_t;

inline mutex_t mutex_new();
inline void mutex_delete(mutex_t mutex);
inline void mutex_lock(mutex_t mutex);
inline void mutex_unlock(mutex_t mutex);

class mutex
{
public:
	inline mutex();

	inline void lock();
	inline void unlock();

private:
	inline mutex(const mutex &another);
	inline mutex &operator =(const mutex &another);

#if TRACE_OUT_CPP_VERSION >= 201103L

	inline mutex(mutex &&another);
	inline mutex &operator =(mutex &&another);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	resource<mutex_t> _handle;
};

}
}

//
// Implementation

namespace trace_out { namespace system
{

mutex::mutex()
	:
	_handle(mutex_new(), mutex_delete)
{
}

void mutex::lock()
{
	mutex_lock(_handle.get());
}

void mutex::unlock()
{
	mutex_unlock(_handle.get());
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

struct _mutex_t
{
	pthread_mutex_t value;
};

mutex_t mutex_new()
{
	mutex_t mutex = new _mutex_t;
	int retval = pthread_mutex_init(&mutex->value, NULL);
	assert(retval == 0);

	return mutex;
}

void mutex_delete(mutex_t mutex)
{
	int retval = pthread_mutex_destroy(&mutex->value);
	assert(retval == 0);

	delete mutex;
}

void mutex_lock(mutex_t mutex)
{
	int retval = pthread_mutex_lock(&mutex->value);
	assert(retval == 0);
}

void mutex_unlock(mutex_t mutex)
{
	int retval = pthread_mutex_unlock(&mutex->value);
	assert(retval == 0);
}

}
}

#elif defined(TRACE_OUT_WINDOWS)

//
// WinAPI implementation

#include <windows.h> // [amalgamate:leave]

namespace trace_out { namespace system
{

struct _mutex_t
{
	CRITICAL_SECTION value;
};

mutex_t mutex_new()
{
	mutex_t mutex = new _mutex_t;
	InitializeCriticalSection(&mutex->value);

	return mutex;
}

void mutex_delete(mutex_t mutex)
{
	DeleteCriticalSection(&mutex->value);
}

void mutex_lock(mutex_t mutex)
{
	EnterCriticalSection(&mutex->value);
}

void mutex_unlock(mutex_t mutex)
{
	LeaveCriticalSection(&mutex->value);
}

}
}

#endif

