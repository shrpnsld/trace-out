#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("$s(...)", "[s]")
{
	test::out_stream.str(std::string {});

	int value {456};

	$s(value = 789;)

	const char *expected {
		"value = 789; // running...\n"
		"value = 789; // done.\n"
	};
	REQUIRE(test::out_stream.str() == expected);
	REQUIRE(value == 789);
}

