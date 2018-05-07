#include "trace-out/detail/system/mutex.hpp"


namespace trace_out { namespace detail { namespace system
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
}

