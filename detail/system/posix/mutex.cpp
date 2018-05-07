#include "trace-out/detail/stuff/platform-detection.hpp"
#if defined(TRACE_OUT_POSIX)

#include <cstddef>
#include <cassert> // [amalgamate: leave]
#include <pthread.h>

#include "trace-out/detail/system/mutex.hpp"


namespace trace_out { namespace detail
{

	struct _mutex
	{
		pthread_mutex_t value;
	};


	mutex_t mutex_new()
	{
		mutex_t mutex = new _mutex;
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


#endif // defined(TRACE_OUT_POSIX)

