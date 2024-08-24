#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <thread>


TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$t(...)'", "[TRACE_OUT_SHOW_THREAD][thread][t]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	const char *what {"hellomoto!"};
	$t(what);

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(@@ ~~~~\[ Thread\: [0-9a-f]+ \]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n)="
		R"=(@@ what = "hellomoto!"\n)="
	));
}
