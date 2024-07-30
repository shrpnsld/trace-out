#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <thread>

TEST_CASE("'TRACE_OUT_STYLE=1' and 'TRACE_OUT_SHOW_THREAD'", "[TRACE_OUT_STYLE][TRACE_OUT_SHOW_THREAD]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		$t(what);
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	$t(what);

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(\[1;34m~~~~\[Thread\: [0-9a-f]+ two\]~~~~\[0m\n)="
		R"=(\[0;34mwhat\[0m = \[0;32m"wazuuup!"\[0m\n)="
		R"=(\[1;34m~~~~\[Thread\: [0-9a-f]+ one\]~~~~\[0m\n)="
		R"=(\[0;34mwhat\[0m = \[0;32m"hellomoto!"\[0m\n)="
	));
}

