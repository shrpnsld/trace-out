#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

void subject_func();

TEST_CASE("'TRACE_OUT_SHOW_HEADER' with '$f'", "[TRACE_OUT_SHOW_HEADER][f]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	subject_func();

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \] #########################################\n)="
		R"=(\n)="
		R"=(void subject_func\(\)\n)="
		R"=(\{\n)="
		R"=(\} // void subject_func\(\)\n)="
		R"=(\n)="
	));
}

void subject_func()
{$f
}

