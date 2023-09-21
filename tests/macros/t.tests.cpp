#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("$t(...)", "[t]")
{
	test::stream.str(std::string {});

	int value {456};
	$t(value = 789;)
	const char *expected {"value = 789; // trace-out: statement passed\n"};
	REQUIRE(test::stream.str() == expected);
	REQUIRE(value == 789);
}

