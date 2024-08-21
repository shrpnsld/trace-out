#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <cstdint>
#include <iomanip>
#include <sstream>

using trace_out::RESET_FLAGS;

void some_func() { $f $f }

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$t(...)'", "[TRACE_OUT_SYNC_STREAM][t]")
{
	test::out_stream.str(std::string {});

	int some {456};

	$t(some);
	$t(some);

	const char *expected {
		"some = 456\n"
		"some = 456\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$tbin(...)'", "[TRACE_OUT_SYNC_STREAM][tbin]")
{
	test::out_stream.str(std::string {});

	int some {456};

	$tbin(some);
	$tbin(some);

	const char *expected {
		"some = bin: 00000000 00000000 00000001 11001000\n"
		"some = bin: 00000000 00000000 00000001 11001000\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$toct(...)'", "[TRACE_OUT_SYNC_STREAM][toct]")
{
	test::out_stream.str(std::string {});

	int some {456};

	$toct(some);
	$toct(some);

	const char *expected {
		"some = oct: 000000 001310\n"
		"some = oct: 000000 001310\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$thex(...)'", "[TRACE_OUT_SYNC_STREAM][thex]")
{
	test::out_stream.str(std::string {});

	int some {456};

	$thex(some);
	$thex(some);

	const char *expected {
		"some = hex: 000001c8\n"
		"some = hex: 000001c8\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$tr(...)'", "[TRACE_OUT_SYNC_STREAM][tr]")
{
	test::out_stream.str(std::string {});

	std::vector<int> subject {1, 2, 3, 4, 5};

	SECTION(".begin(), .end()")
	{
		$tr(subject.begin(), subject.end())
		$tr(subject.begin(), subject.end())

		const char *expected {
			"[subject.begin(), subject.end()) = [1, 2, 3, 4, 5]\n"
			"[subject.begin(), subject.end()) = [1, 2, 3, 4, 5]\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION(".begin(), how_much")
	{
		$tr(subject.begin(), 5)
		$tr(subject.begin(), 5)

		const char *expected {
			"[subject.begin(): 5] = [1, 2, 3, 4, 5]\n"
			"[subject.begin(): 5] = [1, 2, 3, 4, 5]\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION(".begin(), .end(), how_much")
	{
		$tr(subject.begin(), subject.end(), 5)
		$tr(subject.begin(), subject.end(), 5)

		const char *expected {
			"[subject.begin(), subject.end()):5 = [1, 2, 3, 4, 5]\n"
			"[subject.begin(), subject.end()):5 = [1, 2, 3, 4, 5]\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$m(...)'", "[TRACE_OUT_SYNC_STREAM][m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40
	};

	$m(subject.data(), subject.size())
	$m(subject.data(), subject.size())

	std::stringstream expected;
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};
	expected << "subject.data(), 16 bytes of 1-byte hexadecimal\n";
	expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" "  .dl....." "\n"; address += 8;
	expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad 40" "  J.x(=H.@" "\n";
	expected << "\n";

	address = reinterpret_cast<std::uintptr_t>(subject.data());
	expected << "subject.data(), 16 bytes of 1-byte hexadecimal\n";
	expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" "  .dl....." "\n"; address += 8;
	expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad 40" "  J.x(=H.@" "\n";
	expected << "\n";

	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$s(...)'", "[TRACE_OUT_SYNC_STREAM][s]")
{
	test::out_stream.str(std::string {});

	$s(dummy("hellomoto!");)
	$s(dummy("wazzzup!");)

	const char *expected {
		"dummy(\"hellomoto!\"); // running...\n"
		"dummy(\"hellomoto!\"); // done.\n"
		"dummy(\"wazzzup!\"); // running...\n"
		"dummy(\"wazzzup!\"); // done.\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$f(...)'", "[TRACE_OUT_SYNC_STREAM][f]")
{
	test::out_stream.str(std::string {});

	some_func();

	const char *expected {
		"void some_func()\n"
		"{\n"
		"    void some_func()\n"
		"    {\n"
		"    } // void some_func()\n"
		"\n"
		"} // void some_func()\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$if(...)'", "[TRACE_OUT_SYNC_STREAM][if]")
{
	test::out_stream.str(std::string {});

	$if (true)
	{
		$if (true)
		{
		}
	}

	const char *expected {
		"if (true) => true\n"
		"{\n"
		"    if (true) => true\n"
		"    {\n"
		"    }\n"
		"\n"
		"}\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$for(...)'", "[TRACE_OUT_SYNC_STREAM][for]")
{
	test::out_stream.str(std::string {});

	$for (; true;)
	{
		$for (; true;)
		{
			break;
		}

		break;
	}

	const char *expected {
		"for (; true;)\n"
		"{\n"
		"    // for: iteration #1\n"
		"    for (; true;)\n"
		"    {\n"
		"        // for: iteration #1\n"
		"\n"
		"    } // for (; true;)\n"
		"\n"
		"} // for (; true;)\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$while(...)'", "[TRACE_OUT_SYNC_STREAM][while]")
{
	test::out_stream.str(std::string {});

	$while (true)
	{
		$while (true)
		{
			break;
		}

		break;
	}

	const char *expected {
		"while (true)\n"
		"{\n"
		"    // while: iteration #1\n"
		"    while (true)\n"
		"    {\n"
		"        // while: iteration #1\n"
		"\n"
		"    } // while (true)\n"
		"\n"
		"} // while (true)\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$time(...)'", "[TRACE_OUT_SYNC_STREAM][time]")
{
	test::out_stream.str(std::string {});

	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$time("dummy", dummy();)
	$time("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(Timing "dummy"...\n)="
		R"=("dummy" timed in [0-9]+ ms\n)="
		R"=(Timing "dummy"...\n)="
		R"=("dummy" timed in [0-9]+ ms\n)="
	));
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$time_stats(...)'", "[TRACE_OUT_SYNC_STREAM][time_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	$thread(two)
	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(// Execution time statistics \(ms\) for "dummy":\n)="
		R"=(//   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(\n)="
		R"=(// Execution time statistics \(ms\) for "dummy":\n)="
		R"=(//   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(\n)="
	));
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$clocks(...)'", "[TRACE_OUT_SYNC_STREAM][clocks]")
{
	test::out_stream.str(std::string {});

	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$clocks("dummy", dummy();)
	$clocks("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(Clocking "dummy"...\n)="
		R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\)\n)="
		R"=(Clocking "dummy"...\n)="
		R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\)\n)="
	));
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$clock_stats(...)'", "[TRACE_OUT_SYNC_STREAM][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$thread(one)

	$thread(two)
	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(// Execution time statistics \(clocks\) for "dummy":\n)="
		R"=(//   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(\n)="
		R"=(// Execution time statistics \(clocks\) for "dummy":\n)="
		R"=(//   avg/med: [0-9\.]+ / [0-9\.]+\n)="
		R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\)\n)="
		R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\]\n)="
		R"=(\n)="
	));
}

