#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("$for(...) - 5 iterations", "[for]")
{
	test::out_stream.str(std::string {});

	$for (unsigned int i {0}; i < 5; ++i)
	{
	}

	const char *expected {
		"for (unsigned int i {0}; i < 5; ++i)\n"
		"{\n"
		"    // for: iteration #1\n"
		"\n"
		"    // for: iteration #2\n"
		"\n"
		"    // for: iteration #3\n"
		"\n"
		"    // for: iteration #4\n"
		"\n"
		"    // for: iteration #5\n"
		"\n"
		"} // for (unsigned int i {0}; i < 5; ++i)\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("$for(...) - 0 iterations", "[for]")
{
	test::out_stream.str(std::string {});

	$for (unsigned int i {5}; i < 5; ++i)
	{
	}

	const char *expected {
		"for (unsigned int i {5}; i < 5; ++i)\n"
		"{\n"
		"} // for (unsigned int i {5}; i < 5; ++i)\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

