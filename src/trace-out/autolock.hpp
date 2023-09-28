#pragma once

//
// Public

namespace trace_out
{

	template <typename Lockable_t>
	class autolock
	{
	public:
		inline autolock(Lockable_t &lockable);
		inline ~autolock();
	
	private:
		Lockable_t &_lockable;
	};

}

namespace trace_out
{

	template <typename Lockable_t>
	autolock<Lockable_t>::autolock(Lockable_t &lockable)
		:
		_lockable(lockable)
	{
		_lockable.lock();
	}

	template <typename Lockable_t>
	autolock<Lockable_t>::~autolock()
	{
		_lockable.unlock();
	}

}

