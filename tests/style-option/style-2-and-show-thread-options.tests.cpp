#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <thread>

TEST_CASE("'TRACE_OUT_STYLE=2' and 'TRACE_OUT_SHOW_THREAD'", "[TRACE_OUT_STYLE][TRACE_OUT_SHOW_THREAD]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread("one")

	std::thread {[](const char *what)
	{
		$thread("two")
		$t(what);
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	$t(what);

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[ Thread: \[0;36mtwo\[0m \[0;35m[0-9a-f]+\[0m \]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n)="
		R"=(\[0;36mwhat\[0m = \[0;33m"wazuuup!"\[0m\n)="
		R"=(~~~~\[ Thread: \[0;36mone\[0m \[0;35m[0-9a-f]+\[0m \]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n)="
		R"=(\[0;36mwhat\[0m = \[0;33m"hellomoto!"\[0m\n)="
	));
}

