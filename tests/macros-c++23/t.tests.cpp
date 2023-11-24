#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <expected>

TEST_CASE("$t(value), C++23", "[t]")
{
	test::out_stream.str(std::string {});

	SECTION("std::expected")
	{
		SECTION("!has_value()")
		{
			std::expected<int, std::string> subject {std::unexpected<std::string> {"you smell!"}};

			dummy($t(subject));

			const char *expected {"subject = \"you smell!\" // error\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("has_value()")
		{
			std::expected<int, std::string> subject {456};

			dummy($t(subject));

			const char *expected {"subject = 456\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}
}

