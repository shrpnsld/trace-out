#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <cstdint>
#include <iomanip>
#include <vector>

using trace_out::RESET_FLAGS;

TEST_CASE("'TRACE_OUT_INDENTATION' inside '$if(...)'", "[indentation][TRACE_OUT_INDENTATION][if]")
{
	test::out_stream.str(std::string {});

	int some {456};

	$if (some == 456)
	{
		$t(some);
	}

	const char *expected {
		"if (some == 456) => true\n"
		"{\n"
		"  some = 456\n"
		"} // if (some == 456) => true\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' inside '$for(...)'", "[indentation][TRACE_OUT_INDENTATION][for]")
{
	test::out_stream.str(std::string {});

	$for (unsigned int i {0}; i < 5; ++i)
	{
		$t(i);
	}

	const char *expected {
		"for (unsigned int i {0}; i < 5; ++i)\n"
		"{\n"
		"  // for: iteration #1\n"
		"  i = 0\n"
		"\n"
		"  // for: iteration #2\n"
		"  i = 1\n"
		"\n"
		"  // for: iteration #3\n"
		"  i = 2\n"
		"\n"
		"  // for: iteration #4\n"
		"  i = 3\n"
		"\n"
		"  // for: iteration #5\n"
		"  i = 4\n"
		"\n"
		"} // for (unsigned int i {0}; i < 5; ++i)\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' inside '$while(...)'", "[indentation][TRACE_OUT_INDENTATION][while]")
{
	test::out_stream.str(std::string {});

	unsigned int i {0};

	$while (i < 5)
	{
		$t(i);
		++i;
	}

	const char *expected {
		"while (i < 5)\n"
		"{\n"
		"  // while: iteration #1\n"
		"  i = 0\n"
		"\n"
		"  // while: iteration #2\n"
		"  i = 1\n"
		"\n"
		"  // while: iteration #3\n"
		"  i = 2\n"
		"\n"
		"  // while: iteration #4\n"
		"  i = 3\n"
		"\n"
		"  // while: iteration #5\n"
		"  i = 4\n"
		"\n"
		"} // while (i < 5)\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

void subject_func9() {$f $t("hellomoto!"); }
int subject_func10() {$f $return 789; }

TEST_CASE("'TRACE_OUT_INDENTATION' inside '$f'", "[indentation][TRACE_OUT_INDENTATION][f]")
{
	test::out_stream.str(std::string {});

	subject_func9();

	const char *expected {
		"void subject_func9()\n"
		"{\n"
		"  // hellomoto!\n"
		"} // void subject_func9()\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$if(...)'", "[indentation][TRACE_OUT_INDENTATION][if]")
{
	test::out_stream.str(std::string {});

	int first {456};
	int second {789};

	$if (first > 400)
	{
		$t(first);
		$if (second > 700)
		{
			$t(second);
		}
	}

	const char *expected {
		"if (first > 400) => true\n"
		"{\n"
		"  first = 456\n"
		"  if (second > 700) => true\n"
		"  {\n"
		"    second = 789\n"
		"  } // if (second > 700) => true\n"
		"\n"
		"} // if (first > 400) => true\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$for(...)'", "[indentation][TRACE_OUT_INDENTATION][for]")
{
	test::out_stream.str(std::string {});

	int first {456};

	$if (first > 400)
	{
		$t(first);
		$for (unsigned int i {0}; i < 1; ++i)
		{
			$t(i);
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
		"\n"
		"  } // for (unsigned int i {0}; i < 1; ++i)\n"
		"\n"
		"} // if (first > 400) => true\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$while(...)'", "[indentation][TRACE_OUT_INDENTATION][while]")
{
	test::out_stream.str(std::string {});

	int first {456};

	$if (first > 400)
	{
		$t(first);
		unsigned int i {0};
		$while (i < 1)
		{
			$t(i);
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
		"\n"
		"  } // while (i < 1)\n"
		"\n"
		"} // if (first > 400) => true\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}


TEST_CASE("'TRACE_OUT_INDENTATION' outside '$f'", "[indentation][TRACE_OUT_INDENTATION][f]")
{
	test::out_stream.str(std::string {});

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
		"\n"
		"} // if (first > 400) => true\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$return'", "[indentation][TRACE_OUT_INDENTATION][return]")
{
	test::out_stream.str(std::string {});

	subject_func10();

	const char *expected {
		"int subject_func10()\n"
		"{\n"
		"  return 789\n"
		"} // int subject_func10()\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$t(...)'", "[indentation][TRACE_OUT_INDENTATION][t]")
{
	test::out_stream.str(std::string {});

	int some {456};

	SECTION("single arguments")
	{
		$if (some == 456)
		{
			$t(some);
		}

		const char *expected {
			"if (some == 456) => true\n"
			"{\n"
			"  some = 456\n"
			"} // if (some == 456) => true\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("multiple arguments")
	{
		$if (some == 456)
		{
			const char *str {"hellomoto!"};
			int number {456};
			$t(str, number);
		}

		const char *expected {
			"if (some == 456) => true\n"
			"{\n"
			"  str = \"hellomoto!\"\n"
			"  number = 456\n"
			"\n"
			"} // if (some == 456) => true\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("nested structure")
	{
		$if (some == 456)
		{
			std::vector<std::vector<int>> nested {
				{1, 2, 3},
				{4, 5, 6},
				{7, 8, 9}
			};
			$t(nested);
		}

		const char *expected {
			"if (some == 456) => true\n"
			"{\n"
			"  nested = [\n"
			"    [1, 2, 3],\n"
			"    [4, 5, 6],\n"
			"    [7, 8, 9]\n"
			"  ]\n"
			"} // if (some == 456) => true\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$t<base>(...)'", "[indentation][TRACE_OUT_INDENTATION][tbase]")
{
	test::out_stream.str(std::string {});

	int some {456};

	$if (some == 456)
	{
		$tbin(some);
		$toct(some);
		$thex(some);
	}

	const char *expected {
		"if (some == 456) => true\n"
		"{\n"
		"  some = bin: 00000000 00000000 00000001 11001000\n"
		"  some = oct: 000000 001310\n"
		"  some = hex: 000001c8\n"
		"} // if (some == 456) => true\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$tr(...)'", "[indentation][TRACE_OUT_INDENTATION][tr]")
{
	test::out_stream.str(std::string {});

	int some {456};

	SECTION("simple structure")
	{
		$if (some == 456)
		{
			std::vector<int> arr {1, 2, 3, 4, 5};
			$tr(arr.begin(), arr.end());
		}

		const char *expected {
			"if (some == 456) => true\n"
			"{\n"
			"  [arr.begin(), arr.end()) = [1, 2, 3, 4, 5]\n"
			"} // if (some == 456) => true\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("nested structures")
	{
		SECTION(".begin(), .end()")
		{
			$if (some == 456)
			{
				std::vector<std::vector<int>> nested {
					{1, 2, 3},
					{4, 5, 6},
					{7, 8, 9}
				};
				$tr(nested.begin(), nested.end());
			}

			const char *expected {
				"if (some == 456) => true\n"
				"{\n"
				"  [nested.begin(), nested.end()) = [\n"
				"    [1, 2, 3],\n"
				"    [4, 5, 6],\n"
				"    [7, 8, 9]\n"
				"  ]\n"
				"} // if (some == 456) => true\n"
				"\n"
			};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".begin(), how_much)")
		{
			$if (some == 456)
			{
				std::vector<std::vector<int>> nested {
					{1, 2, 3},
					{4, 5, 6},
					{7, 8, 9}
				};
				$tr(nested.begin(), 2);
			}

			const char *expected {
				"if (some == 456) => true\n"
				"{\n"
				"  [nested.begin(): 2] = [\n"
				"    [1, 2, 3],\n"
				"    [4, 5, 6]\n"
				"  ]\n"
				"} // if (some == 456) => true\n"
				"\n"
			};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".begin(), .end(), how_much)")
		{
			$if (some == 456)
			{
				std::vector<std::vector<int>> nested {
					{1, 2, 3},
					{4, 5, 6},
					{7, 8, 9}
				};
				$tr(nested.begin(), nested.end(), 2);
			}

			const char *expected {
				"if (some == 456) => true\n"
				"{\n"
				"  [nested.begin(), nested.end()):2 = [\n"
				"    [1, 2, 3],\n"
				"    [4, 5, 6]\n"
				"  ]\n"
				"} // if (some == 456) => true\n"
				"\n"
			};
			REQUIRE(test::out_stream.str() == expected);
		}
	}
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$m(...)'", "[indentation][TRACE_OUT_INDENTATION][m]")
{
	test::out_stream.str(std::string {});

	int some {456};
	char str[11] {"hellomoto!"};

	$if (some == 456)
	{
		$m(str, sizeof(str))
	}

	std::stringstream expected;
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(str)};
	expected << "if (some == 456) => true\n";
	expected << "{\n";
	expected << "  str, 11 bytes of 1-byte hexadecimal\n";
	expected << "    " << std::hex << address << RESET_FLAGS << ": 68 65 6c 6c 6f 6d 6f 74" "  hellomot" "\n"; address += 8;
	expected << "    " << std::hex << address << RESET_FLAGS << ": 6f 21 00               " "  o!." "\n";
	expected << "\n";
	expected << "} // if (some == 456) => true\n";
	expected << "\n";

	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$s(...)'", "[indentation][TRACE_OUT_INDENTATION][s]")
{
	test::out_stream.str(std::string {});

	int some {456};

	$if (some == 456)
	{
		$s(some = 789;)
	}

	const char *expected {
		"if (some == 456) => true\n"
		"{\n"
		"  some = 789; // running...\n"
		"  some = 789; // done.\n"
		"} // if (some == 456) => true\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$time(...)'", "[indentation][TRACE_OUT_INDENTATION][time]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$if (true)
	{
		$time("dummy", dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(if \(true\) => true\n)="
		R"=(\{\n)="
		R"=(  Timing "dummy"...\n)="
		R"=(  "dummy" timed in [0-9]+ ms\n)="
		R"=(\} // if \(true\) => true\n)="
		R"=(\n)="
	));
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$time_stats(...)'", "[indentation][TRACE_OUT_INDENTATION][time_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$if (true)
	{
		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$time_stats("dummy", 10, dummy();)
		}
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(if \(true\) => true\n)="
		R"=(\{\n)="
		R"=(  // Execution time statistics \(ms\) for "dummy":\n)="
		R"=(  //   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(  //     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(  //     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(\n)="
		R"=(\} // if \(true\) => true\n)="
		R"=(\n)="
	));
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$clocks(...)'", "[indentation][TRACE_OUT_INDENTATION][clocks]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$if (true)
	{
		$clocks("dummy", dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(if \(true\) => true\n)="
		R"=(\{\n)="
		R"=(  Clocking "dummy"...\n)="
		R"=(  "dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\)\n)="
		R"=(\} // if \(true\) => true\n)="
		R"=(\n)="
	));
}

TEST_CASE("'TRACE_OUT_INDENTATION' outside '$clock_stats(...)'", "[indentation][TRACE_OUT_INDENTATION][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$if (true)
	{
		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$clock_stats("dummy", 10, dummy();)
		}
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(if \(true\) => true\n)="
		R"=(\{\n)="
		R"=(  // Execution time statistics \(clocks\) for "dummy":\n)="
		R"=(  //   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(  //     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(  //     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(\n)="
		R"=(\} // if \(true\) => true\n)="
		R"=(\n)="
	));
}

