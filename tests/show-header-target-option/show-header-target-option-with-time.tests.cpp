#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("'TRACE_OUT_SHOW_HEADER_TARGET' with '$time(...)'", "[TRACE_OUT_SHOW_HEADER_TARGET][time]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$time("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} show-header-target-option-with-time-tests \] ####\n)="
		R"=(\n)="
		R"=(Timing "dummy"...\n)="
		R"=("dummy" timed in [0-9]+ ms\n)="
	));
}

