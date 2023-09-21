#pragma once

#include "trace-out/platform-detection.hpp"

//
// Public

#define trace_out_private__concat_impl(a, b) \
			a##b

#define trace_out_private__concat(a, b) \
			trace_out_private__concat_impl(a, b)

#define trace_out_private__unify(identifier_base) \
			trace_out_private__concat(identifier_base, __COUNTER__)

#define trace_out_private__id \
			trace_out_private__concat(id, __COUNTER__)


#define trace_out_private__dereference_macro_impl(name) \
			name

#define trace_out_private__dereference_macro(name) \
			trace_out_private__dereference_macro_impl(name)


#define trace_out_private__quotize_impl(something) \
			#something

#define trace_out_private__quotize(something) \
			trace_out_private__quotize_impl(something)


#if defined(TRACE_OUT_CLANG) || defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)
	#define TRACE_OUT_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(TRACE_OUT_MVS)
	#define TRACE_OUT_FUNCTION_SIGNATURE __FUNCSIG__
#else
	#error Cannot find function signature macro for current compiler. Try to add one manualy to this block.
#endif

