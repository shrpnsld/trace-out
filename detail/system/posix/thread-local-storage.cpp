//#include "trace-out/detail/stuff/platform-detection.hpp" // [amalgamate:uncomment]
//#if defined(TRACE_OUT_POSIX) // [amalgamate:uncomment]

#include <cstddef>
#include <cassert> // [amalgamate:leave]
#include <pthread.h> // [amalgamate:leave]

#include "trace-out/detail/system/thread-local-storage.hpp"


namespace trace_out { namespace detail { namespace system
{

	struct _tlskey
	{
		pthread_key_t value;
	};


	tlskey_t tls_new_key()
	{
		tlskey_t key = new _tlskey;
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
}


//#endif // defined(TRACE_OUT_POSIX) // [amalgamate:uncomment]

