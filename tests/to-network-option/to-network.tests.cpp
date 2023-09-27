#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>

// $ nc -lk 127.0.0.1 45678

TEST_CASE("'TRACE_OUT_TO_NETWORK' manual test helper", "[TRACE_OUT_TO_NETWORK]")
{$f
	$p("hellomoto!")
}

