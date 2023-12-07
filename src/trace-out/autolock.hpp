#pragma once

//
// Public

namespace trace_out
{

template <typename Lockable_t>
class autolock
{
public:
	autolock(Lockable_t &lockable);
	~autolock();

private:
	Lockable_t &_lockable;
};

}

//
// Implementation

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

