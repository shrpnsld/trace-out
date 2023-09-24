#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <vector>

TEST_CASE("'TRACE_OUT_INDENTATION' inside '$if(...)'", "[indentation][TRACE_OUT_INDENTATION][if]")
{
	test::stream.str(std::string {});

	int some {456};

	$if (some == 456)
	{
		$w(some)
	}

	const char *expected {
		"if (some == 456) => true\n"
		"{\n"
		"  some = 456\n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' inside '$for(...)'", "[indentation][TRACE_OUT_INDENTATION][for]")
{
	test::stream.str(std::string {});

	$for (unsigned int i {0}; i < 5; ++i)
	{
		$w(i)
	}

	const char *expected {
		"for (unsigned int i {0}; i < 5; ++i)\n"
		"{\n"
		"  // for: iteration #1\n"
		"  i = 0\n"
		"  \n"
		"  // for: iteration #2\n"
		"  i = 1\n"
		"  \n"
		"  // for: iteration #3\n"
		"  i = 2\n"
		"  \n"
		"  // for: iteration #4\n"
		"  i = 3\n"
		"  \n"
		"  // for: iteration #5\n"
		"  i = 4\n"
		"  \n"
		"} // for (unsigned int i {0}; i < 5; ++i)\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' inside '$while(...)'", "[indentation][TRACE_OUT_INDENTATION][while]")
{
	test::stream.str(std::string {});

	unsigned int i {0};

	$while (i < 5)
	{
		$w(i)
		++i;
	}

	const char *expected {
		"while (i < 5)\n"
		"{\n"
		"  // while: iteration #1\n"
		"  i = 0\n"
		"  \n"
		"  // while: iteration #2\n"
		"  i = 1\n"
		"  \n"
		"  // while: iteration #3\n"
		"  i = 2\n"
		"  \n"
		"  // while: iteration #4\n"
		"  i = 3\n"
		"  \n"
		"  // while: iteration #5\n"
		"  i = 4\n"
		"  \n"
		"} // while (i < 5)\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

void subject_func9() {$f $p("hellomoto!") }
int subject_func10() {$f $return 789; }

TEST_CASE("'TRACE_OUT_INDENTATION' inside '$f'", "[indentation][TRACE_OUT_INDENTATION][f]")
{
	test::stream.str(std::string {});

	subject_func9();

	const char *expected {
		"void subject_func9()\n"
		"{\n"
		"  // hellomoto!\n"
		"} // void subject_func9()\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$if(...)'", "[indentation][TRACE_OUT_INDENTATION][if]")
{
	test::stream.str(std::string {});

	int first {456};
	int second {789};

	$if (first > 400)
	{
		$w(first)
		$if (second > 700)
		{
			$w(second)
		}
	}

	const char *expected {
		"if (first > 400) => true\n"
		"{\n"
		"  first = 456\n"
		"  if (second > 700) => true\n"
		"  {\n"
		"    second = 789\n"
		"  }\n"
		"  \n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$for(...)'", "[indentation][TRACE_OUT_INDENTATION][for]")
{
	test::stream.str(std::string {});

	int first {456};

	$if (first > 400)
	{
		$w(first)
		$for (unsigned int i {0}; i < 1; ++i)
		{
			$w(i)
		}
	}

	const char *expected {
		"if (first > 400) => true\n"
		"{\n"
		"  first = 456\n"
		"  for (unsigned int i {0}; i < 1; ++i)\n"
		"  {\n"
		"    // for: iteration #1\n"
		"    i = 0\n"
		"    \n"
		"  } // for (unsigned int i {0}; i < 1; ++i)\n"
		"  \n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$while(...)'", "[indentation][TRACE_OUT_INDENTATION][while]")
{
	test::stream.str(std::string {});

	int first {456};

	$if (first > 400)
	{
		$w(first)
		unsigned int i {0};
		$while (i < 1)
		{
			$w(i)
			++i;
		}
	}

	const char *expected {
		"if (first > 400) => true\n"
		"{\n"
		"  first = 456\n"
		"  while (i < 1)\n"
		"  {\n"
		"    // while: iteration #1\n"
		"    i = 0\n"
		"    \n"
		"  } // while (i < 1)\n"
		"  \n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}


TEST_CASE("'TRACE_OUT_INDENTATION' outside '$f'", "[indentation][TRACE_OUT_INDENTATION][f]")
{
	test::stream.str(std::string {});

	int first {456};

	$if (first > 400)
	{
		subject_func9();
	}

	const char *expected {
		"if (first > 400) => true\n"
		"{\n"
		"  void subject_func9()\n"
		"  {\n"
		"    // hellomoto!\n"
		"  } // void subject_func9()\n"
		"  \n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$return'", "[indentation][TRACE_OUT_INDENTATION][return]")
{
	test::stream.str(std::string {});

	subject_func10();

	const char *expected {
		"int subject_func10()\n"
		"{\n"
		"  return 789\n"
		"} // int subject_func10()\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$w(...)'", "[indentation][TRACE_OUT_INDENTATION][w]")
{
	test::stream.str(std::string {});

	int some {456};

	$if (some == 456)
	{
		$w(some)
	}

	const char *expected {
		"if (some == 456) => true\n"
		"{\n"
		"  some = 456\n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$e(...)'", "[indentation][TRACE_OUT_INDENTATION][e]")
{
	test::stream.str(std::string {});

	int some {456};

	$if (some == 456)
	{
		$e(some);
	}

	const char *expected {
		"if (some == 456) => true\n"
		"{\n"
		"  some = 456\n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$r(...)'", "[indentation][TRACE_OUT_INDENTATION][r]")
{
	test::stream.str(std::string {});

	int some {456};

	$if (some == 456)
	{
		std::vector arr {1, 2, 3, 4, 5};
		$r(arr.begin(), arr.end());
	}

	const char *expected {
		"if (some == 456) => true\n"
		"{\n"
		"  [arr.begin(), arr.end()) = [1, 2, 3, 4, 5]\n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$m(...)'", "[indentation][TRACE_OUT_INDENTATION][m]")
{
	test::stream.str(std::string {});

	int some {456};
	char str[11] {"hellomoto!"};

	$if (some == 456)
	{
		$m(str, sizeof(str))
	}

	std::stringstream expected;
	expected <<
		"if (some == 456) => true\n"
		"{\n"
		"  str, 11 bytes of 1-byte hexadecimal\n"
		"    " << static_cast<const void *>(str + 0) << ": 68 65 6c 6c 6f 6d 6f 74 6f 21 00\n"
		"    \n"
		"}\n"
		"\n";

	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$t(...)'", "[indentation][TRACE_OUT_INDENTATION][t]")
{
	test::stream.str(std::string {});

	int some {456};

	$if (some == 456)
	{
		$t(some = 789;)
	}

	const char *expected {
		"if (some == 456) => true\n"
		"{\n"
		"  some = 789; // trace-out: statement passed\n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$p(...)'", "[indentation][TRACE_OUT_INDENTATION][p]")
{
	test::stream.str(std::string {});

	int some {456};

	$if (some == 456)
	{
		$p("%s", "hellomoto!")
	}

	const char *expected {
		"if (some == 456) => true\n"
		"{\n"
		"  // hellomoto!\n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$time(...)'", "[indentation][TRACE_OUT_INDENTATION][time]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$if (true)
	{
		$time("dummy", dummy();)
	}

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(if \(true\) => true\n)"
		R"(\{\n)"
		R"(  // execution time for "dummy": [0-9]+ ms\n)"
		R"(\}\n)"
		R"(\n)"
	));
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$time_stats(...)'", "[indentation][TRACE_OUT_INDENTATION][time_stats]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$if (true)
	{
		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$time_stats("dummy", 10, dummy();)
		}
	}

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(if \(true\) => true\n)"
		R"(\{\n)"
		R"(  // execution time statistics \(ms\) for "dummy":\n)"
		R"(  //   avg/med: [0-9\.]+ / [0-9\.]+\n)"
		R"(  //     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)"
		R"(  //     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)"
		R"(  \n)"
		R"(\}\n)"
		R"(\n)"
	));
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$clocks(...)'", "[indentation][TRACE_OUT_INDENTATION][clocks]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$if (true)
	{
		$clocks("dummy", dummy();)
	}

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(if \(true\) => true\n)"
		R"(\{\n)"
		R"(  // execution time for "dummy": [0-9]+ clocks \([0-9\.]+ ms\)\n)"
		R"(\}\n)"
		R"(\n)"
	));
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$clock_stats(...)'", "[indentation][TRACE_OUT_INDENTATION][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$if (true)
	{
		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$clock_stats("dummy", 10, dummy();)
		}
	}

	REQUIRE_THAT(test::stream.str(), Matches(
		R"(if \(true\) => true\n)"
		R"(\{\n)"
		R"(  // execution time statistics \(clocks\) for "dummy":\n)"
		R"(  //   avg/med: [0-9\.]+ / [0-9\.]+\n)"
		R"(  //     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)"
		R"(  //     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)"
		R"(  \n)"
		R"(\}\n)"
		R"(\n)"
	));
}

