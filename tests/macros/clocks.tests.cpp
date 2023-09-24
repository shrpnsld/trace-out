#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <chrono>
#include <thread>

TEST_CASE("$clocks(...)", "[clocks]")
{
	using namespace std::chrono_literals;
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$clocks("sleeping", std::this_thread::sleep_for(2000ms);)

	REQUIRE_THAT(test::stream.str(), Matches(R"(// execution time for "sleeping": [0-9]+ clocks \([0-9\.]+ ms\)\n)"));
}

