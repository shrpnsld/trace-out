#pragma once


#if defined(__clang__)
	#define TRACE_OUT_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
	#define TRACE_OUT_GCC
#elif defined(_MSC_VER)
	#define TRACE_OUT_MVS
#else
	#error Failed to detect compiler
#endif

#if defined(__MINGW32__)
	#define TRACE_OUT_MINGW
#endif

#if defined(__unix__) || defined(__APPLE__)
	#define TRACE_OUT_POSIX
#elif defined(_WIN32)
	#define TRACE_OUT_WINDOWS
#else
	#error Failed to detect platform
#endif


// Visual Studio was defining '__cplusplus' macro as '199711L', and now they have '/Zc:__cplusplus' to fix this.
// If, for some reason, you don't want to use this option, you can define macro 'TRACE_OUT_CPP_VERSION' with a valid '__cplusplus' macro value
#if !defined(TRACE_OUT_CPP_VERSION)
	#define TRACE_OUT_CPP_VERSION __cplusplus
#endif

