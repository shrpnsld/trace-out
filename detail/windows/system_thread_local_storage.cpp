#include "../platform_defines.hpp"
#if defined(TRACE_OUT_WINDOWS)

#include <cassert> // [amalgamate: leave]
#include <windows.h>

#include "../system_thread_local_storage.hpp"


namespace trace_out { namespace detail
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


#endif // defined(TRACE_OUT_WINDOWS)

