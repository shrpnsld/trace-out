#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("'TRACE_OUT_SHOW_HEADER_TARGET' with '$toct(...)'", "[TRACE_OUT_SHOW_HEADER_TARGET][toct]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	int what {456};
	$toct(what);

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} show-header-target-option-with-toct-tests \] ####\n)="
		R"=(\n)="
		R"=(what = oct: 000000 001310\n)="
	));
}

