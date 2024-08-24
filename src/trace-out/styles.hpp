#pragma once

#include "trace-out/macro-magic.hpp"

//
// Private

#define trace_out_style(...) "\033[" trace_out_private__quotize(__VA_ARGS__) "m"
#define trace_out_style_normal() "\033[0m"

#define trace_out__RED 31
#define trace_out__GREEN 32
#define trace_out__YELLOW 33
#define trace_out__BLUE 34
#define trace_out__MAGENTA 35
#define trace_out__CYAN 36
#define trace_out__WHITE 37

#define trace_out__REGULAR 0
#define trace_out__BOLD 1

//
// Public

namespace trace_out { namespace styles
{

#if TRACE_OUT_STYLE == 1
	static const char *const BOOLEAN = trace_out_style(trace_out__REGULAR;trace_out__MAGENTA);
	static const char *const CHARACTER = trace_out_style(trace_out__REGULAR;trace_out__YELLOW);
	static const char *const COMMENT = trace_out_style(trace_out__REGULAR;trace_out__WHITE);
	static const char *const COMMENT_BOLD = trace_out_style(trace_out__BOLD;trace_out__WHITE);
	static const char *const FUNCTION = trace_out_style(trace_out__BOLD;trace_out__BLUE);
	static const char *const KEYWORD = trace_out_style(trace_out__BOLD;trace_out__MAGENTA);
	static const char *const NORMAL = trace_out_style_normal();
	static const char *const NUMBER = trace_out_style(trace_out__REGULAR;trace_out__CYAN);
	static const char *const STRING = trace_out_style(trace_out__REGULAR;trace_out__GREEN);
	static const char *const SUBJECT = trace_out_style(trace_out__REGULAR;trace_out__BLUE);
	static const char *const THREAD_NAME = trace_out_style(trace_out__REGULAR;trace_out__BLUE);
	static const char *const THREAD_ID = trace_out_style(trace_out__REGULAR;trace_out__CYAN);

#elif TRACE_OUT_STYLE == 2
	static const char *const BOOLEAN = trace_out_style(trace_out__REGULAR;trace_out__BLUE);
	static const char *const CHARACTER = trace_out_style(trace_out__REGULAR;trace_out__GREEN);
	static const char *const COMMENT = trace_out_style(trace_out__REGULAR;trace_out__WHITE);
	static const char *const COMMENT_BOLD = trace_out_style(trace_out__BOLD;trace_out__WHITE);
	static const char *const FUNCTION = trace_out_style(trace_out__BOLD;trace_out__CYAN);
	static const char *const KEYWORD = trace_out_style(trace_out__BOLD;trace_out__BLUE);
	static const char *const NORMAL = trace_out_style_normal();
	static const char *const NUMBER = trace_out_style(trace_out__REGULAR;trace_out__MAGENTA);
	static const char *const STRING = trace_out_style(trace_out__REGULAR;trace_out__YELLOW);
	static const char *const SUBJECT = trace_out_style(trace_out__REGULAR;trace_out__CYAN);
	static const char *const THREAD_NAME = trace_out_style(trace_out__REGULAR;trace_out__CYAN);
	static const char *const THREAD_ID = trace_out_style(trace_out__REGULAR;trace_out__MAGENTA);

#elif TRACE_OUT_STYLE == 3
	static const char *const BOOLEAN = trace_out_style(trace_out__REGULAR;trace_out__RED);
	static const char *const CHARACTER = trace_out_style(trace_out__REGULAR;trace_out__CYAN);
	static const char *const COMMENT = trace_out_style(trace_out__REGULAR;trace_out__WHITE);
	static const char *const COMMENT_BOLD = trace_out_style(trace_out__BOLD;trace_out__WHITE);
	static const char *const FUNCTION = trace_out_style(trace_out__BOLD;trace_out__MAGENTA);
	static const char *const KEYWORD = trace_out_style(trace_out__BOLD;trace_out__RED);
	static const char *const NORMAL = trace_out_style_normal();
	static const char *const NUMBER = trace_out_style(trace_out__REGULAR;trace_out__BLUE);
	static const char *const STRING = trace_out_style(trace_out__REGULAR;trace_out__CYAN);
	static const char *const SUBJECT = trace_out_style(trace_out__REGULAR;trace_out__MAGENTA);
	static const char *const THREAD_NAME = trace_out_style(trace_out__REGULAR;trace_out__MAGENTA);
	static const char *const THREAD_ID = trace_out_style(trace_out__REGULAR;trace_out__BLUE);

#elif TRACE_OUT_STYLE == 4
	static const char *const BOOLEAN = trace_out_style(trace_out__REGULAR;trace_out__YELLOW);
	static const char *const CHARACTER = trace_out_style(trace_out__REGULAR;trace_out__BLUE);
	static const char *const COMMENT = trace_out_style(trace_out__REGULAR;trace_out__WHITE);
	static const char *const COMMENT_BOLD = trace_out_style(trace_out__BOLD;trace_out__WHITE);
	static const char *const FUNCTION = trace_out_style(trace_out__BOLD;trace_out__CYAN);
	static const char *const KEYWORD = trace_out_style(trace_out__BOLD;trace_out__YELLOW);
	static const char *const NORMAL = trace_out_style_normal();
	static const char *const NUMBER = trace_out_style(trace_out__REGULAR;trace_out__GREEN);
	static const char *const STRING = trace_out_style(trace_out__REGULAR;trace_out__BLUE);
	static const char *const SUBJECT = trace_out_style(trace_out__REGULAR;trace_out__CYAN);
	static const char *const THREAD_NAME = trace_out_style(trace_out__REGULAR;trace_out__CYAN);
	static const char *const THREAD_ID = trace_out_style(trace_out__REGULAR;trace_out__GREEN);

#else
	static const char *const BOOLEAN = "";
	static const char *const CHARACTER = "";
	static const char *const COMMENT = "";
	static const char *const COMMENT_BOLD = "";
	static const char *const FUNCTION = "";
	static const char *const KEYWORD = "";
	static const char *const NORMAL = "";
	static const char *const NUMBER = "";
	static const char *const STATEMENT = "";
	static const char *const STRING = "";
	static const char *const SUBJECT = "";
	static const char *const THREAD_NAME = "";
	static const char *const THREAD_ID = "";

#endif // TRACE_OUT_STYLE

}
}

#undef trace_out_style
#undef trace_out__CLEAN
#undef trace_out__RED
#undef trace_out__GREEN
#undef trace_out__YELLOW
#undef trace_out__BLUE
#undef trace_out__MAGENTA
#undef trace_out__CYAN
#undef trace_out__WHITE
#undef trace_out__BOLD

