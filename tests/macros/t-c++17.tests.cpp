#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <optional>
#include <variant>

TEST_CASE("$t(value), C++17", "[t]")
{
	test::out_stream.str(std::string {});

	SECTION("std::optional")
	{
		SECTION("!has_value()")
		{
			std::optional<std::string> subject;

			dummy($t(subject));

			const char *expected {"subject = <empty>\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("has_value()")
		{
			std::optional<std::string> subject {"hellomoto!"};

			dummy($t(subject));

			const char *expected {"subject = \"hellomoto!\"\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}

	SECTION("std::variant")
	{
		SECTION("std::string")
		{
			std::variant<std::string, int, float> subject {"hellomoto!"};

			dummy($t(subject));

			const char *expected {"subject = \"hellomoto!\"\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("int")
		{
			std::variant<std::string, int, float> subject {456};

			dummy($t(subject));

			const char *expected {"subject = 456\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("float")
		{
			std::variant<std::string, int, float> subject {456.789f};

			dummy($t(subject));

			const char *expected {"subject = 456.789\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}
}

