#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("'TRACE_OUT_SHOW_HEADER_TARGET' with '$while(...)'", "[TRACE_OUT_SHOW_HEADER_TARGET][while]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$while (true)
	{
		break;
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} show-header-target-option-with-while-tests \] ####\n)="
		R"=(\n)="
		R"=(while \(true\)\n)="
		R"=(\{\n)="
		R"=(    // while: iteration #1\n)="
		R"=(\n)="
		R"=(\} // while \(true\)\n)="
		R"=(\n)="
	));
}

