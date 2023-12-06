#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("$if(...)", "[if]")
{
	test::out_stream.str(std::string {});

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
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("false")
	{
		int value {789};

		$if (value == 456) {}

		const char *expected {
			"if (value == 456) => false\n"
			"{\n"
			"}\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("$if(...) nested", "[if]")
{
	test::out_stream.str(std::string {});

	SECTION("true, true")
	{
		$if (true)
		{
			$if (true)
			{
			}
		}

		const char *expected {
			"if (true) => true\n"
			"{\n"
			"    if (true) => true\n"
			"    {\n"
			"    }\n"
			"\n"
			"}\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("true, false")
	{
		$if (true)
		{
			$if (false)
			{
			}
		}

		const char *expected {
			"if (true) => true\n"
			"{\n"
			"    if (false) => false\n"
			"    {\n"
			"    }\n"
			"\n"
			"}\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("false, true")
	{
		$if (false)
		{
		}
		else
		{
			$if (true)
			{
			}
		}

		const char *expected {
			"if (false) => false\n"
			"{\n"
			"    if (true) => true\n"
			"    {\n"
			"    }\n"
			"\n"
			"}\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("false, false")
	{
		$if (false)
		{
		}
		else
		{
			$if (false)
			{
			}
		}

		const char *expected {
			"if (false) => false\n"
			"{\n"
			"    if (false) => false\n"
			"    {\n"
			"    }\n"
			"\n"
			"}\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

