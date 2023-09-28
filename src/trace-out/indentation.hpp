#pragma once

#include "trace-out/integer.hpp"
#include "trace-out/thread-local-storage.hpp"
#include <string>

//
// Public

namespace trace_out
{

inline system::tls<std::string> &private_tls_indentation();
inline const std::string &indentation();
inline void indentation_add();
inline void indentation_remove();

}

//
// Private

namespace trace_out
{

#if defined(TRACE_OUT_INDENTATION)
	static const char INDENTATION_UNIT[] = TRACE_OUT_INDENTATION;
#else
	static const char INDENTATION_UNIT[] = "    ";
#endif

static const standard::size_t INDENTATION_UNIT_WIDTH = sizeof(INDENTATION_UNIT) - 1;

}

//
// Implementation

namespace trace_out
{

system::tls<std::string> &private_tls_indentation()
{
	static system::tls<std::string> _indentation;

	return _indentation;
}

const std::string &indentation()
{
	return private_tls_indentation().get();
}

void indentation_add()
{
	private_tls_indentation().set(private_tls_indentation().get() + INDENTATION_UNIT);
}

void indentation_remove()
{
	const std::string &old_indentation = private_tls_indentation().get();
	private_tls_indentation().set(old_indentation.substr(0, old_indentation.length() - INDENTATION_UNIT_WIDTH));
}

}
