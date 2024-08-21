#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("'TRACE_OUT_SHOW_HEADER_TARGET' with '$t(...)'", "[TRACE_OUT_SHOW_HEADER_TARGET][t]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	const char *what {"hellomoto!"};
	$t(what);

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} show-header-target-option-with-t-tests \] ##\n)="
		R"=(\n)="
		R"=(what = "hellomoto!"\n)="
	));
}

