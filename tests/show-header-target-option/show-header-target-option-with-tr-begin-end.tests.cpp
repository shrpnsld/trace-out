#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("'TRACE_OUT_SHOW_HEADER_TARGET' with '$tr(<begin>, <end>)'", "[TRACE_OUT_SHOW_HEADER_TARGET][tr]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	const char *what {"hellomoto!"};
	const char *end {what + std::strlen(what)};
	$tr(what, end)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} show-header-target-option-with-tr-begin-end-tests \] ####\n)="
		R"=(\n)="
		R"=(\[what, end\) = \['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!'\]\n)="
	));
}

