#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <thread>

TEST_CASE("'TRACE_OUT_STYLE=1' and 'TRACE_OUT_SHOW_THREAD'", "[TRACE_OUT_STYLE][TRACE_OUT_SHOW_THREAD]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$start("some")

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ \[0;33m[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2}\[0m \[0;36msome\[0m \] ####################################\n)="
		R"=(\n)="
	));
}

