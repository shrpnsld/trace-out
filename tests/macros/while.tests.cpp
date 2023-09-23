#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("$while(...) - 5 iterations", "[while]")
{
	test::stream.str(std::string {});

	unsigned int i {0};

	$while (i < 5)
	{
		++i;
	}

	const char *expected {
		"while (i < 5)\n"
		"{\n"
		"    // while: iteration #1\n"
		"    \n"
		"    // while: iteration #2\n"
		"    \n"
		"    // while: iteration #3\n"
		"    \n"
		"    // while: iteration #4\n"
		"    \n"
		"    // while: iteration #5\n"
		"    \n"
		"} // while (i < 5)\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("$while(...) - 0 iterations", "[while]")
{
	test::stream.str(std::string {});

	unsigned int i {5};

	$while (i < 5)
	{
		++i;
	}

	const char *expected {
		"while (i < 5)\n"
		"{\n"
		"} // while (i < 5)\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

