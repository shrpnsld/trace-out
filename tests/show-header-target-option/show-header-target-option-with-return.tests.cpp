#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

int subject_func();

TEST_CASE("'TRACE_OUT_SHOW_HEADER_TARGET' with '$return'", "[TRACE_OUT_SHOW_HEADER_TARGET][return]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	subject_func();

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} show-header-target-option-with-return-tests \] ####\n)="
		R"=(\n)="
		R"=(return 456\n)="
	));
}

int subject_func()
{
	$return 456;
}

