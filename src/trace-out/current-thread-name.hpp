#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/thread.hpp"
#include "trace-out/thread-local-storage.hpp"
#include <string>

//
// Public

namespace trace_out
{

inline bool is_running_same_thread();
inline const std::string &current_thread_name();
inline void set_current_thread_name(const std::string &name);

}

//
// Private

namespace trace_out
{

inline system::tls<std::string> &private_tls_thread_name();
inline standard::uint64_t &private_current_thread_id();

}

//
// Implementation

namespace trace_out
{

bool is_running_same_thread()
{
	if (private_current_thread_id() != system::current_thread_id())
	{
		private_current_thread_id() = system::current_thread_id();
		return false;
	}

	return true;
}

const std::string &current_thread_name()
{
	return private_tls_thread_name().get();
}

void set_current_thread_name(const std::string &name)
{
	private_tls_thread_name().set(name);
}

system::tls<std::string> &private_tls_thread_name()
{
	static system::tls<std::string> _thread_name;

	return _thread_name;
}

standard::uint64_t &private_current_thread_id()
{
	static standard::uint64_t _current_thread_id;

	return _current_thread_id;
}

}

