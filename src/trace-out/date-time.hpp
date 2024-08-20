#pragma once

#include "autolock.hpp"
#include "mutex.hpp"
#include <string>

//
// Public

namespace trace_out
{

inline std::string date_time_now();

}

//
// Implementation

namespace trace_out
{

std::string date_time_now()
{
#if defined(TRACE_OUT_SHOW_DATE_TIME)
	static system::mutex localtime_lock;

	char buffer[20];
	standard::size_t buffer_size = sizeof(buffer) / sizeof(buffer[0]);

	std::time_t now = std::time(NULL);

	{
		autolock<system::mutex> lock(localtime_lock);
		const std::tm *local_time = std::localtime(&now);
		std::strftime(buffer, buffer_size, "%Y-%m-%0d %H:%M:%S", local_time);
	}

	return std::string(buffer);
#else
	return std::string();
#endif // defined(TRACE_OUT_SHOW_DATE_TIME)
}

}

