#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("$if(...)", "[if]")
{
	test::stream.str(std::string {});

	SECTION("true")
	{
		int value {456};

		$if (value == 456) {}

		const char *expected {
			"if (value == 456) => true\n"
			"{\n"
			"}\n"
			"\n"
		};
		REQUIRE(test::stream.str() == expected);
	}

	SECTION("true")
	{
		int value {789};

		$if (value == 456) {}

		const char *expected {
			"if (value == 456) => false\n"
			"{\n"
			"}\n"
			"\n"
		};
		REQUIRE(test::stream.str() == expected);
	}
}

