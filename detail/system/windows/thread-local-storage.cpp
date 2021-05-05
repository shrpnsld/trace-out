//#include "trace-out/detail/stuff/platform-detection.hpp" // [amalgamate:uncomment]
//#if defined(TRACE_OUT_WINDOWS) // [amalgamate:uncomment]

#include <cassert> // [amalgamate:leave]
#include <windows.h> // [amalgamate:leave]

#include "trace-out/detail/system/thread-local-storage.hpp"


namespace trace_out { namespace detail { namespace system
{

	struct _tlskey
	{
		DWORD value;
	};


	tlskey_t tls_new_key()
	{
		tlskey_t key = new _tlskey;
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
}


//#endif // defined(TRACE_OUT_WINDOWS) // [amalgamate:uncomment]

