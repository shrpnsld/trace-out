#pragma once


#if defined(__clang__)
	#define TRACE_OUT_CLANG
#elif defined(__MINGW32__)
	#define TRACE_OUT_MINGW
#elif defined(__GNUC__) || defined(__GNUG__)
	#define TRACE_OUT_GCC
#elif defined(_MSC_VER)
	#define TRACE_OUT_MVS
#else
	#error Failed to detect compiler
#endif


#if defined(__unix__) || defined(__APPLE__)
	#define TRACE_OUT_POSIX
#elif defined(_WIN32)
	#define TRACE_OUT_WINDOWS
#else
	#error Failed to detect platform
#endif


#if __cplusplus >= 201103L || _MSC_VER >= 1800
	#define TRACE_OUT_CPP11
#endif

