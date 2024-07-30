#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("$time(...)", "[time]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$time("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(Timing "dummy"\.\.\.\n)="
		R"=("dummy" timed in [0-9]+ ms\n)="
	));
}

