#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("'$start' with 'TRACE_OUT_START_MESSAGE=\"two\"'", "[start][TRACE_OUT_START_MESSAGE]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$start();

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} two \] #####################################\n)="
		R"=(\n)="
	));
}

