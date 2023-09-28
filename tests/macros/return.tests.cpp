#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>

int int_func(int what);

TEST_CASE("$return(...)", "[return]")
{
	test::out_stream.str(std::string {});

	int value {int_func(456)};
	const char *expected {"return 456\n"};
	REQUIRE(test::out_stream.str() == expected);
	REQUIRE(value == 456);
}

int int_func(int what)
{
	$return what;
}

