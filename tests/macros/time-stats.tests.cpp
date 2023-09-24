#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <chrono>
#include <thread>
#include <vector>

TEST_CASE("$time_stats(...)", "[time_stats]")
{
	using namespace std::chrono_literals;
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	std::vector<std::chrono::milliseconds> durations {10ms, 20ms, 10ms, 15ms, 10ms, 17ms, 9ms, 10ms, 7ms, 10ms};

	for (std::chrono::milliseconds duration : durations)
	{
		$time_stats("sleeping", 10,
			std::this_thread::sleep_for(duration);
		)
	}

	REQUIRE_THAT(test::stream.str(), Matches(
R"(// execution time statistics \(ms\) for "sleeping":
//   avg/med: [0-9\.]+ / [0-9\.]+
//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)
//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]

)"));
}

