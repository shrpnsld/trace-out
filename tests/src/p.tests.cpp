#include "trace-out/trace-out.hpp"
#include "helpers/test-stream.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("$p(...)", "[p]")
{
	test::stream.str(std::string {});

	$p("hellomoto! %s %d", "wazzzup!", 456)
	const char *expected {"// hellomoto! wazzzup! 456\n"};
	REQUIRE(test::stream.str() == expected);
}

