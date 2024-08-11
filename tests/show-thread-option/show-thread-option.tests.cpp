#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <cstring>
#include <sstream>
#include <thread>

void subject_func1(const char *what) {$f $t(what); }
const char *subject_func2(const char *what) { $return what; }

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$t(...)'", "[TRACE_OUT_SHOW_THREAD][t]")
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
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(what = "wazuuup!"\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(what = "hellomoto!"\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$tbin(...)'", "[TRACE_OUT_SHOW_THREAD][tbin]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[](int what)
	{
		$thread(two)
		$tbin(what);
	}, 456}.join();

	int what {456};
	$tbin(what);

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(what = bin: 00000000 00000000 00000001 11001000\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(what = bin: 00000000 00000000 00000001 11001000\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$toct(...)'", "[TRACE_OUT_SHOW_THREAD][toct]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[](int what)
	{
		$thread(two)
		$toct(what);
	}, 456}.join();

	int what {456};
	$toct(what);

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(what = oct: 000000 001310\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(what = oct: 000000 001310\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thex(...)'", "[TRACE_OUT_SHOW_THREAD][thex]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[](int what)
	{
		$thread(two)
		$thex(what);
	}, 456}.join();

	int what {456};
	$thex(what);

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(what = hex: 000001c8\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(what = hex: 000001c8\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$tr(...)'", "[TRACE_OUT_SHOW_THREAD][tr]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	SECTION(".begin(), .end()")
	{
		$thread(one)

		std::thread {[](const char *what)
		{
			$thread(two)
			const char *end {what + std::strlen(what)};
			$tr(what, end)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		const char *end {what + std::strlen(what)};
		$tr(what, end)

		REQUIRE_THAT(test::out_stream.str(), Matches(
			R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
			R"=(\[what, end\) = \['w', 'a', 'z', 'u', 'u', 'u', 'p', '!'\]\n)="
			R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
			R"=(\[what, end\) = \['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!'\]\n)="
		));
	}

	SECTION(".begin(), how_much")
	{
		$thread(one)

		std::thread {[](const char *what)
		{
			$thread(two)
			$tr(what, 5)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		$tr(what, 5)

		REQUIRE_THAT(test::out_stream.str(), Matches(
			R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
			R"=(\[what: 5\] = \['w', 'a', 'z', 'u', 'u'\]\n)="
			R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
			R"=(\[what: 5\] = \['h', 'e', 'l', 'l', 'o'\]\n)="
		));
	}

	SECTION(".begin(), .end(), how_much")
	{
		$thread(one)

		std::thread {[](const char *what)
		{
			$thread(two)
			const char *end {what + std::strlen(what)};
			$tr(what, end, 5)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		const char *end {what + std::strlen(what)};
		$tr(what, end, 5)

		REQUIRE_THAT(test::out_stream.str(), Matches(
			R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
			R"=(\[what, end\):5 = \['w', 'a', 'z', 'u', 'u'\]\n)="
			R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
			R"=(\[what, end\):5 = \['h', 'e', 'l', 'l', 'o'\]\n)="
		));
	}
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$m(...)'", "[TRACE_OUT_SHOW_THREAD][m]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		std::size_t size {std::strlen(what) + 1};

		$thread(two)
		$m(what, size)
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	std::size_t size {std::strlen(what) + 1};
	$m(what, size)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(what, 9 bytes of 1-byte hexadecimal\n)="
		R"=(    [0-9a-f]+: 77 61 7a 75 75 75 70 21  wazuuup!\n)="
		R"=(    [0-9a-f]+: 00                       \.\n)="
		R"=(\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(what, 11 bytes of 1-byte hexadecimal\n)="
		R"=(    [0-9a-f]+: 68 65 6c 6c 6f 6d 6f 74  hellomot\n)="
		R"=(    [0-9a-f]+: 6f 21 00                 o!\.\n)="
		R"=(\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$s(...)'", "[TRACE_OUT_SHOW_THREAD][s]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$s(dummy("wazuuup!");)
	}}.join();

	$s(dummy("hellomoto!");)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(dummy\("wazuuup!"\); // running...\n)="
		R"=(dummy\("wazuuup!"\); // done.\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(dummy\("hellomoto!"\); // running...\n)="
		R"=(dummy\("hellomoto!"\); // done.\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$f'", "[TRACE_OUT_SHOW_THREAD][f]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		subject_func1(what);
	}, "wazuuup!"}.join();

	subject_func1("hellomoto!");

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(void subject_func1\(const char \*\)\n)="
		R"=(\{\n)="
		R"=(    what = "wazuuup!"\n)="
		R"=(\} // void subject_func1\(const char \*\)\n)="
		R"=(\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(void subject_func1\(const char \*\)\n)="
		R"=(\{\n)="
		R"=(    what = "hellomoto!"\n)="
		R"=(\} // void subject_func1\(const char \*\)\n)="
		R"=(\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$return'", "[TRACE_OUT_SHOW_THREAD][return]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		subject_func2(what);
	}, "wazuuup!"}.join();

	subject_func2("hellomoto!");

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(return "wazuuup!"\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(return "hellomoto!"\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$if(...)'", "[TRACE_OUT_SHOW_THREAD][if]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		$if (what)
		{
		}
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	$if (what)
	{
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(if \(what\) => true \("wazuuup!"\)\n)="
		R"=(\{\n)="
		R"=(\}\n)="
		R"=(\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(if \(what\) => true \("hellomoto!"\)\n)="
		R"=(\{\n)="
		R"=(\}\n)="
		R"=(\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$for(...)'", "[TRACE_OUT_SHOW_THREAD][for]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$for (;;)
		{
			break;
		}
	}}.join();

	$for (;;)
	{
		break;
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(for \(;;\)\n)="
		R"=(\{\n)="
		R"=(    // for: iteration #1\n)="
		R"=(\n)="
		R"=(\} // for \(;;\)\n)="
		R"=(\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(for \(;;\)\n)="
		R"=(\{\n)="
		R"=(    // for: iteration #1\n)="
		R"=(\n)="
		R"=(\} // for \(;;\)\n)="
		R"=(\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$while(...)'", "[TRACE_OUT_SHOW_THREAD][for]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$while (true)
		{
			break;
		}
	}}.join();

	$while (true)
	{
		break;
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(while \(true\)\n)="
		R"=(\{\n)="
		R"=(    // while: iteration #1\n)="
		R"=(\n)="
		R"=(\} // while \(true\)\n)="
		R"=(\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(while \(true\)\n)="
		R"=(\{\n)="
		R"=(    // while: iteration #1\n)="
		R"=(\n)="
		R"=(\} // while \(true\)\n)="
		R"=(\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$time(...)'", "[TRACE_OUT_SHOW_THREAD][time]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$time("dummy", dummy();)
	}}.join();

	$time("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(Timing "dummy"...\n)="
		R"=("dummy" timed in [0-9]+ ms\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(Timing "dummy"...\n)="
		R"=("dummy" timed in [0-9]+ ms\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$time_stats(...)'", "[TRACE_OUT_SHOW_THREAD][time_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$time_stats("dummy", 10, dummy();)
		}
	}}.join();

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(// Execution time statistics \(ms\) for "dummy":\n)="
		R"=(//   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(// Execution time statistics \(ms\) for "dummy":\n)="
		R"=(//   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$clocks(...)'", "[TRACE_OUT_SHOW_THREAD][clocks]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$clocks("dummy", dummy();)
	}}.join();

	$clocks("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(Clocking "dummy"...\n)="
		R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\)\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(Clocking "dummy"...\n)="
		R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\)\n)="
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$clock_stats(...)'", "[TRACE_OUT_SHOW_THREAD][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$clock_stats("dummy", 10, dummy();)
		}
	}}.join();

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(~~~~\[Thread\: [0-9a-f]+ two\]~~~~\n)="
		R"=(// Execution time statistics \(clocks\) for "dummy":\n)="
		R"=(//   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(\n)="
		R"=(~~~~\[Thread\: [0-9a-f]+ one\]~~~~\n)="
		R"=(// Execution time statistics \(clocks\) for "dummy":\n)="
		R"=(//   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(\n)="
	));
}

