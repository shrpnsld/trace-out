#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <cstdint>
#include <iomanip>
#include <sstream>

using trace_out::RESET_FLAGS;

const long int subject_func11_line {__LINE__ + 2};
void subject_func11()
{$f
}

const long int subject_func12_line {__LINE__ + 3};
int subject_func12()
{
	$return 789;
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$t(...)'", "[TRACE_OUT_SHOW_FILE_LINE][t]")
{
	test::out_stream.str(std::string {});

	const char *str {"hellomoto!"};

	long int line {__LINE__ + 1};
	$t(str);

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "   | str = \"hellomoto!\"\n";
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$t<base>(...)'", "[TRACE_OUT_SHOW_FILE_LINE][tbase]")
{
	test::out_stream.str(std::string {});

	int some {456};

	long int line {__LINE__ + 1};
	$tbin(some);
	$toct(some);
	$thex(some);

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line     << "   | some = bin: 00000000 00000000 00000001 11001000\n";
	expected << " show-file-line-opt~:" << line + 1 << "   | some = oct: 000000 001310\n";
	expected << " show-file-line-opt~:" << line + 2 << "   | some = hex: 000001c8\n";
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$tr(...)'", "[TRACE_OUT_SHOW_FILE_LINE][tr]")
{
	test::out_stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {10};

	long int line {__LINE__ + 1};
	$tr(str, str + length)

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "   | [str, str + length) = ['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!']\n";
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$m(...)'", "[TRACE_OUT_SHOW_FILE_LINE][m]")
{
	test::out_stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};

	long int line {__LINE__ + 1};
	$m(str, length)

	std::stringstream expected;
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(str)};
	expected << " show-file-line-opt~:" << line << "   | str, 11 bytes of 1-byte hexadecimal\n";
	expected << "                          |     " << std::hex << address << RESET_FLAGS << ": 68 65 6c 6c 6f 6d 6f 74" "  hellomot" "\n"; address += 8;
	expected << "                          |     " << std::hex << address << RESET_FLAGS << ": 6f 21 00               " "  o!."      "\n";
	expected << "                          | \n";
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$s(...)'", "[TRACE_OUT_SHOW_FILE_LINE][s]")
{
	test::out_stream.str(std::string {});

	long int line {__LINE__ + 1};
	$s(dummy();)

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "   | dummy(); // running...\n";
	expected << " show-file-line-opt~:" << line << "   | dummy(); // done.\n";
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$f'", "[TRACE_OUT_SHOW_FILE_LINE][f]")
{
	test::out_stream.str(std::string {});

	subject_func11();

	std::stringstream expected;
	expected <<
		" show-file-line-opt~:" << subject_func11_line << "   | void subject_func11()\n"
		"                          | {\n"
		" show-file-line-opt~:" << subject_func11_line << "   | } // void subject_func11()\n"
		"                          | \n";
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$return'", "[TRACE_OUT_SHOW_FILE_LINE][return]")
{
	test::out_stream.str(std::string {});

	subject_func12();

	std::stringstream expected;
	expected << " show-file-line-opt~:" << subject_func12_line << "   | return 789\n";
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$if(...)'", "[TRACE_OUT_SHOW_FILE_LINE][if]")
{
	test::out_stream.str(std::string {});

	long int line {__LINE__ + 1};
	$if (true)
	{
	}

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "  | if (true) => true\n"
		"                          | {\n"
		"                          | }\n"
		"                          | \n";
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$for(...)'", "[TRACE_OUT_SHOW_FILE_LINE][for]")
{
	test::out_stream.str(std::string {});

	long int line {__LINE__ + 1};
	$for ( ; true; )
	{
		break;
	}

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "  | for (; true;)\n"
		"                          | {\n"
		" show-file-line-opt~:" << line << "  |     // for: iteration #1\n"
		"                          | \n"
		"                          | } // for (; true;)\n"
		"                          | \n";
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$while(...)'", "[TRACE_OUT_SHOW_FILE_LINE][while]")
{
	test::out_stream.str(std::string {});

	long int line {__LINE__ + 1};
	$while (true)
	{
		break;
	}

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "  | while (true)\n"
		"                          | {\n"
		" show-file-line-opt~:" << line << "  |     // while: iteration #1\n"
		"                          | \n"
		"                          | } // while (true)\n"
		"                          | \n";
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$time(...)'", "[TRACE_OUT_SHOW_FILE_LINE][time]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	long int line {__LINE__ + 1};
	$time("dummy", dummy();)

	std::stringstream expected;
	expected <<
		" show-file-line-opt~:" << line << "  \\| Timing \"dummy\"...\n"
		" show-file-line-opt~:" << line << "  \\| \"dummy\" timed in [0-9]+ ms\n";
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$time_stats(...)'", "[TRACE_OUT_SHOW_FILE_LINE][time_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	long int line {__LINE__ + 3};
	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line <<
							"  \\| // Execution time statistics \\(ms\\) for \"dummy\":\n"
		"                          \\| //   avg/med: [0-9\\.]+ / [0-9\\.]+\n"
		"                          \\| //     ( mode|modes): [0-9\\.]+(, [0-9\\.]+)* \\((each = [0-9\\.]+%, all = )?[0-9\\.]+% of all values\\)\n"
		"                          \\| //     range: [0-9\\.]+ \\[[0-9\\.]+\\.\\.\\.[0-9\\.]+\\]\n"
		"                          \\| \n";

	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$clocks(...)'", "[TRACE_OUT_SHOW_FILE_LINE][clocks]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	long int line {__LINE__ + 1};
	$clocks("dummy", dummy();)

	std::stringstream expected;
	expected <<
		" show-file-line-opt~:" << line << "  \\| Clocking \"dummy\"...\n"
		" show-file-line-opt~:" << line << "  \\| \"dummy\" clocked in [0-9]+ clocks \\([0-9\\.]+ ms\\)\n";
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$clock_stats(...)'", "[TRACE_OUT_SHOW_FILE_LINE][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	long int line {__LINE__ + 3};
	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line <<
							"  \\| // Execution time statistics \\(clocks\\) for \"dummy\":\n"
		"                          \\| //   avg/med: [0-9\\.]+ / [0-9\\.]+\n"
		"                          \\| //     ( mode|modes): [0-9\\.]+(, [0-9\\.]+)* \\((each = [0-9\\.]+%, all = )?[0-9\\.]+% of all values\\)\n"
		"                          \\| //     range: [0-9\\.]+ \\[[0-9\\.]+\\.\\.\\.[0-9\\.]+\\]\n"
		"                          \\| \n";

	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

