#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("'TRACE_OUT_SHOW_HEADER' with '$tbin(...)'", "[TRACE_OUT_SHOW_HEADER][tbin]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	int what {456};
	$tbin(what);

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \] #########################################\n)="
		R"=(\n)="
		R"=(what = bin: 00000000 00000000 00000001 11001000\n)="
	));
}

