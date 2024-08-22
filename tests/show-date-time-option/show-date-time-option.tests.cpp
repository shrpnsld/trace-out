#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

using trace_out::RESET_FLAGS;

void subject_func11()
{$f
}

int subject_func12()
{
	$return 789;
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$t(...)'", "[TRACE_OUT_SHOW_DATE_TIME][t]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	SECTION("single argument")
	{
		const char *str {"hellomoto!"};

		$t(str);

		REQUIRE_THAT(test::out_stream.str(), Matches(
			R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| str = "hellomoto!"\n)="
		));
	}

	SECTION("multiple arguments")
	{
		const char *str {"hellomoto!"};
		int number {456};

		$t(str, number);

		REQUIRE_THAT(test::out_stream.str(), Matches(
			R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| str = "hellomoto!"\n)="
			R"=(                    \| number = 456\n)="
			R"=(                    \| \n)="
			));
	}

	SECTION("nested structure")
	{
		std::vector<std::vector<int>> nested {
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
		};

		$t(nested);

		REQUIRE_THAT(test::out_stream.str(), Matches(
			R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| nested = \[\n)="
			R"=(                    \|     \[1, 2, 3\],\n)="
			R"=(                    \|     \[4, 5, 6\],\n)="
			R"=(                    \|     \[7, 8, 9\]\n)="
			R"=(                    \| \]\n)="
		));
	}
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$t<base>(...)'", "[TRACE_OUT_SHOW_DATE_TIME][tbase]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	int some {456};

	$tbin(some);
	$toct(some);
	$thex(some);

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| some = bin: 00000000 00000000 00000001 11001000\n)="
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| some = oct: 000000 001310\n)="
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| some = hex: 000001c8\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$tr(...)'", "[TRACE_OUT_SHOW_DATE_TIME][tr]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {10};

	$tr(str, str + length)

	std::stringstream expected;
	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| \[str, str \+ length\) = \['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!'\]\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$m(...)'", "[TRACE_OUT_SHOW_DATE_TIME][m]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};

	$m(str, length)

	std::stringstream expected;
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(str)};
	expected << R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| str, 11 bytes of 1-byte hexadecimal\n)=";
	expected << R"=(                    \|     )=" << std::hex << address << RESET_FLAGS << R"=(: 68 65 6c 6c 6f 6d 6f 74  hellomot\n)="; address += 8;
	expected << R"=(                    \|     )=" << std::hex << address << RESET_FLAGS << R"=(: 6f 21 00                 o!\.\n)=";
	expected << R"=(                    \| \n)=";
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$s(...)'", "[TRACE_OUT_SHOW_DATE_TIME][s]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$s(dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| dummy\(\); // running\.\.\.\n)="
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| dummy\(\); // done\.\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$f'", "[TRACE_OUT_SHOW_DATE_TIME][f]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	subject_func11();

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| void subject_func11\(\)\n)="
		R"=(                    \| \{\n)="
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| \} // void subject_func11\(\)\n)="
		R"=(                    \| \n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$return'", "[TRACE_OUT_SHOW_DATE_TIME][return]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	subject_func12();

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| return 789\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$if(...)'", "[TRACE_OUT_SHOW_DATE_TIME][if]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$if (true)
	{
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| if \(true\) => true\n)="
		R"=(                    \| \{\n)="
		R"=(                    \| \} // if \(true\) => true\n)="
		R"=(                    \| \n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$for(...)'", "[TRACE_OUT_SHOW_DATE_TIME][for]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$for ( ; true; )
	{
		break;
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| for \(; true;\)\n)="
		R"=(                    \| \{\n)="
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \|     // for: iteration #1\n)="
		R"=(                    \| \n)="
		R"=(                    \| \} // for \(; true;\)\n)="
		R"=(                    \| \n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$while(...)'", "[TRACE_OUT_SHOW_DATE_TIME][while]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$while (true)
	{
		break;
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| while \(true\)\n)="
		R"=(                    \| \{\n)="
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \|     // while: iteration #1\n)="
		R"=(                    \| \n)="
		R"=(                    \| \} // while \(true\)\n)="
		R"=(                    \| \n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$time(...)'", "[TRACE_OUT_SHOW_DATE_TIME][time]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$time("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| Timing "dummy"\.\.\.\n)="
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| "dummy" timed in [0-9]+ ms\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$time_stats(...)'", "[TRACE_OUT_SHOW_DATE_TIME][time_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| // Execution time statistics \(ms\) for "dummy":\n)="
		R"=(                    \| //   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(                    \| //     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(                    \| //     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(                    \| \n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$clocks(...)'", "[TRACE_OUT_SHOW_DATE_TIME][clocks]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$clocks("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| Clocking "dummy"\.\.\.\n)="
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| "dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\)\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with '$clock_stats(...)'", "[TRACE_OUT_SHOW_DATE_TIME][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \| // Execution time statistics \(clocks\) for "dummy":\n)="
		R"=(                    \| //   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(                    \| //     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(                    \| //     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(                    \| \n)="
	));
}

