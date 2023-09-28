#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <chrono>
#include <vector>

TEST_CASE("$time_stats(...)", "[time_stats]")
{
	using namespace std::chrono_literals;
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"(// execution time statistics \(ms\) for "dummy":\n)"
		R"(//   avg/med: [0-9\.]+ / [0-9\.]+\n)"
		R"(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)"
		R"(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)"
		R"(\n)"
	));
}

