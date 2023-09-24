#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <sstream>

void subject_func11() {$f }
int subject_func12() { $return 789; }

TEST_CASE("'TRACE_OUT_MARKER' with '$w(...)'", "[TRACE_OUT_MARKER][w]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	dummy(str);

	$w(str)

	const char *expected {"@@ str = \"hellomoto!\"\n"};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_MARKER' with '$e(...)'", "[TRACE_OUT_MARKER][e]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	dummy(str);

	$e(str);

	const char *expected {"@@ str = \"hellomoto!\"\n"};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_MARKER' with '$r(...)'", "[TRACE_OUT_MARKER][r]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};
	dummy(str, length);

	$r(str, str + length)

	const char *expected {"@@ [str, str + length) = ['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!', '']\n"};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_MARKER' with '$m(...)'", "[TRACE_OUT_MARKER][m]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};
	dummy(str, length);

	$m(str, length)

	std::stringstream expected;
	expected <<
		"@@ str, 11 bytes of 1-byte hexadecimal\n"
		"@@     " << static_cast<const void *>(str) << ": 68 65 6c 6c 6f 6d 6f 74 6f 21 00\n"
		"@@     \n";

	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_MARKER' with '$p(...)'", "[TRACE_OUT_MARKER][p]")
{
	test::stream.str(std::string {});

	$p("wazzzup!")

	const char *expected {"@@ // wazzzup!\n"};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_MARKER' with '$t(...)'", "[TRACE_OUT_MARKER][t]")
{
	test::stream.str(std::string {});

	$t(dummy();)

	const char *expected {"@@ dummy(); // trace-out: statement passed\n"};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_MARKER' with '$f'", "[TRACE_OUT_MARKER][f]")
{
	test::stream.str(std::string {});

	subject_func11();

	const char *expected {
		"@@ void subject_func11()\n"
		"@@ {\n"
		"@@ } // void subject_func11()\n"
		"@@ \n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_MARKER' with '$return'", "[TRACE_OUT_MARKER][return]")
{
	test::stream.str(std::string {});

	subject_func12();

	const char *expected {
		"@@ return 789\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_MARKER' with '$if(...)'", "[TRACE_OUT_MARKER][if]")
{
	test::stream.str(std::string {});

	$if (true)
	{
	}

	const char *expected {
		"@@ if (true) => true\n"
		"@@ {\n"
		"@@ }\n"
		"@@ \n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_MARKER' with '$for(...)'", "[TRACE_OUT_MARKER][for]")
{
	test::stream.str(std::string {});

	$for ( ; true; )
	{
		break;
	}

	const char *expected {
		"@@ for (; true;)\n"
		"@@ {\n"
		"@@     // for: iteration #1\n"
		"@@     \n"
		"@@ } // for (; true;)\n"
		"@@ \n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_MARKER' with '$while(...)'", "[TRACE_OUT_MARKER][while]")
{
	test::stream.str(std::string {});

	$while (true)
	{
		break;
	}

	const char *expected {
		"@@ while (true)\n"
		"@@ {\n"
		"@@     // while: iteration #1\n"
		"@@     \n"
		"@@ } // while (true)\n"
		"@@ \n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_MARKER' with '$time(...)'", "[TRACE_OUT_MARKER][time]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$time("dummy", dummy();)

	REQUIRE_THAT(test::stream.str(), Matches(R"(@@ // execution time "dummy": [0-9]+ ms\n)"));
}

TEST_CASE("'TRACE_OUT_MARKER' with '$time_stats(...)'", "[TRACE_OUT_MARKER][time_stats]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::stream.str(), Matches(
R"(@@ // execution time statistics \(ms\) for "dummy":
@@ //   avg/med: [0-9\.]+ / [0-9\.]+
@@ //     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)
@@ //     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]
@@ 
)"));
}

TEST_CASE("'TRACE_OUT_MARKER' with '$clocks(...)'", "[TRACE_OUT_MARKER][clocks]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$clocks("dummy", dummy();)

	REQUIRE_THAT(test::stream.str(), Matches(R"(@@ // execution time "dummy": [0-9]+ clocks \([0-9\.]+ ms\)\n)"));
}

TEST_CASE("'TRACE_OUT_MARKER' with '$clock_stats(...)'", "[TRACE_OUT_MARKER][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::stream.str(), Matches(
R"(@@ // execution time statistics \(clocks\) for "dummy":
@@ //   avg/med: [0-9\.]+ / [0-9\.]+
@@ //     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)
@@ //     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]
@@ 
)"));
}

