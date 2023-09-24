#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <chrono>

TEST_CASE("$time(...)", "[time]")
{
	using namespace std::chrono_literals;
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$time("dummy", dummy();)

	REQUIRE_THAT(test::stream.str(), Matches(R"=(// execution time for "dummy()": [0-9]+ ms\n)="));
}

