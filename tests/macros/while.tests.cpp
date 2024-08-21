#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("$while(...) - 5 iterations", "[while]")
{
	test::out_stream.str(std::string {});

	unsigned int i {0};

	$while (i < 5)
	{
		++i;
	}

	const char *expected {
		"while (i < 5)\n"
		"{\n"
		"    // while: iteration #1\n"
		"\n"
		"    // while: iteration #2\n"
		"\n"
		"    // while: iteration #3\n"
		"\n"
		"    // while: iteration #4\n"
		"\n"
		"    // while: iteration #5\n"
		"\n"
		"} // while (i < 5)\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("$while(...) - 0 iterations", "[while]")
{
	test::out_stream.str(std::string {});

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
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("$while(...) nested", "[while]")
{
	test::out_stream.str(std::string {});

	unsigned int i {0};

	$while (i < 1)
	{
		unsigned int j {0};

		$while (j < 1)
		{
			++j;
		}

		++i;
	}

	const char *expected {
		"while (i < 1)\n"
		"{\n"
		"    // while: iteration #1\n"
		"    while (j < 1)\n"
		"    {\n"
		"        // while: iteration #1\n"
		"\n"
		"    } // while (j < 1)\n"
		"\n"
		"} // while (i < 1)\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

