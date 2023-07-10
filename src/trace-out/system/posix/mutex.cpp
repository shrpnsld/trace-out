//#include "trace-out/stuff/platform-detection.hpp" // [amalgamate:uncomment]
//#if defined(TRACE_OUT_POSIX) // [amalgamate:uncomment]

#include <cstddef>
#include <cassert> // [amalgamate:leave]
#include <pthread.h> // [amalgamate:leave]

#include "trace-out/system/mutex.hpp"


namespace trace_out { namespace detail { namespace system
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
}


//#endif // defined(TRACE_OUT_POSIX) // [amalgamate:uncomment]

