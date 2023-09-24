#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <cstring>
#include <sstream>
#include <thread>

void subject_func1(const char *what) {$f $w(what) }
const char *subject_func2(const char *what) { $return what; }

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$w(...)'", "[TRACE_OUT_SHOW_THREAD][w]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		$w(what)
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	$w(what)

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(what = "wazzzup!"\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(what = "hellomoto!"\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$e(...)'", "[TRACE_OUT_SHOW_THREAD][e]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		$e(what);
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	$e(what);

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(what = "wazzzup!"\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(what = "hellomoto!"\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$r(...)'", "[TRACE_OUT_SHOW_THREAD][r]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		const char *end {what + std::strlen(what)};
		$r(what, end)
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	const char *end {what + std::strlen(what)};
	$r(what, end)

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(\[what, end\) = \['w', 'a', 'z', 'z', 'z', 'u', 'p', '!'\]\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(\[what, end\) = \['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!'\]\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$m(...)'", "[TRACE_OUT_SHOW_THREAD][m]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		std::size_t size {std::strlen(what)};

		$thread(two)
		$m(what, size)
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	std::size_t size {std::strlen(what)};
	$m(what, size)

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(what, 8 bytes of 1-byte hexadecimal\n)"
		R"(    0x[0-9a-f]+: 77 61 7a 7a 7a 75 70 21\n)"
		R"(    \n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(what, 10 bytes of 1-byte hexadecimal\n)"
		R"(    0x[0-9a-f]+: 68 65 6c 6c 6f 6d 6f 74 6f 21\n)"
		R"(    \n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$p(...)'", "[TRACE_OUT_SHOW_THREAD][p]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		$p(what)
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	$p(what)

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(// wazzzup!\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(// hellomoto!\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$t(...)'", "[TRACE_OUT_SHOW_THREAD][t]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$t(dummy("wazzzup!");)
	}}.join();

	$t(dummy("hellomoto!");)

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(dummy\("wazzzup!"\); // trace-out: statement passed\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(dummy\("hellomoto!"\); // trace-out: statement passed\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$f'", "[TRACE_OUT_SHOW_THREAD][f]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		subject_func1(what);
	}, "wazzzup!"}.join();

	subject_func1("hellomoto!");

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(void subject_func1\(const char \*\)\n)"
		R"(\{\n)"
		R"(    what = "wazzzup!"\n)"
		R"(\} // void subject_func1\(const char \*\)\n)"
		R"(\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(void subject_func1\(const char \*\)\n)"
		R"(\{\n)"
		R"(    what = "hellomoto!"\n)"
		R"(\} // void subject_func1\(const char \*\)\n)"
		R"(\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$return'", "[TRACE_OUT_SHOW_THREAD][return]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		subject_func2(what);
	}, "wazzzup!"}.join();

	subject_func2("hellomoto!");

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(return "wazzzup!"\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(return "hellomoto!"\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$if(...)'", "[TRACE_OUT_SHOW_THREAD][if]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		$if (what)
		{
		}
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	$if (what)
	{
	}

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(if \(what\) => true \("wazzzup!"\)\n)"
		R"(\{\n)"
		R"(\}\n)"
		R"(\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(if \(what\) => true \("hellomoto!"\)\n)"
		R"(\{\n)"
		R"(\}\n)"
		R"(\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$for(...)'", "[TRACE_OUT_SHOW_THREAD][for]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

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

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(for \(;;\)\n)"
		R"(\{\n)"
		R"(    // for: iteration #1\n)"
		R"(    \n)"
		R"(\} // for \(;;\)\n)"
		R"(\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(for \(;;\)\n)"
		R"(\{\n)"
		R"(    // for: iteration #1\n)"
		R"(    \n)"
		R"(\} // for \(;;\)\n)"
		R"(\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$while(...)'", "[TRACE_OUT_SHOW_THREAD][for]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

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

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(while \(true\)\n)"
		R"(\{\n)"
		R"(    // while: iteration #1\n)"
		R"(    \n)"
		R"(\} // while \(true\)\n)"
		R"(\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(while \(true\)\n)"
		R"(\{\n)"
		R"(    // while: iteration #1\n)"
		R"(    \n)"
		R"(\} // while \(true\)\n)"
		R"(\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$time(...)'", "[TRACE_OUT_SHOW_THREAD][time]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$time("dummy", dummy();)
	}}.join();

	$time("dummy", dummy();)

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(// execution time for "dummy": [0-9]+ ms\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(// execution time for "dummy": [0-9]+ ms\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$time_stats(...)'", "[TRACE_OUT_SHOW_THREAD][time_stats]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

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

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(// execution time statistics \(ms\) for "dummy":\n)"
		R"(//   avg/med: [0-9\.]+ / [0-9\.]+\n)"
		R"(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)"
		R"(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)"
		R"(\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(// execution time statistics \(ms\) for "dummy":\n)"
		R"(//   avg/med: [0-9\.]+ / [0-9\.]+\n)"
		R"(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)"
		R"(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)"
		R"(\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$clocks(...)'", "[TRACE_OUT_SHOW_THREAD][clocks]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$clocks("dummy", dummy();)
	}}.join();

	$clocks("dummy", dummy();)

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(// execution time for "dummy": [0-9]+ clocks \([0-9\.]+ ms\)\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(// execution time for "dummy": [0-9]+ clocks \([0-9\.]+ ms\)\n)"
	));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$clock_stats(...)'", "[TRACE_OUT_SHOW_THREAD][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

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

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(\[Thread\: 0x[0-9a-f]+ two\]~+\n)"
		R"(// execution time statistics \(clocks\) for "dummy":\n)"
		R"(//   avg/med: [0-9\.]+ / [0-9\.]+\n)"
		R"(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)"
		R"(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)"
		R"(\n)"
		R"(\[Thread\: 0x[0-9a-f]+ one\]~+\n)"
		R"(// execution time statistics \(clocks\) for "dummy":\n)"
		R"(//   avg/med: [0-9\.]+ / [0-9\.]+\n)"
		R"(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)"
		R"(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)"
		R"(\n)"
	));
}

