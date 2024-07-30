#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("$clocks(...)", "[clocks]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$clocks("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(Clocking "dummy"\.\.\.\n)="
		R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\)\n)="
	));
}

