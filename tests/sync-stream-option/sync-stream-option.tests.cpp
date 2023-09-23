#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

void some_func() { $f $f }

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$w(...)'", "[TRACE_OUT_SYNC_STREAM][w]")
{
	test::stream.str(std::string {});

	int some {456};

	$w(some)
	$w(some)

	const char *expected {
		"some = 456\n"
		"some = 456\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$e(...)'", "[TRACE_OUT_SYNC_STREAM][e]")
{
	test::stream.str(std::string {});

	int some {456};

	$e(some);
	$e(some);

	const char *expected {
		"some = 456\n"
		"some = 456\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$r(...)'", "[TRACE_OUT_SYNC_STREAM][r]")
{
	test::stream.str(std::string {});

	std::vector<int> subject {1, 2, 3, 4, 5};

	$r(subject.begin(), subject.end())
	$r(subject.begin(), subject.end())

	const char *expected {
		"[subject.begin(), subject.end()) = [1, 2, 3, 4, 5]\n"
		"[subject.begin(), subject.end()) = [1, 2, 3, 4, 5]\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$m(...)'", "[TRACE_OUT_SYNC_STREAM][m]")
{
	test::stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40
	};

	$m(subject.data(), subject.size())
	$m(subject.data(), subject.size())

	std::stringstream expected;
	expected <<
		"subject.data(), 16 bytes of 1-byte hexadecimal\n"
		"    " << static_cast<const void *>(subject.data()) << ":"
		" df 64 6c cf f9 cb ed 11 4a 83 78 28 3d 48 ad 40" "\n"
		"    \n"
		"subject.data(), 16 bytes of 1-byte hexadecimal\n"
		"    " << static_cast<const void *>(subject.data()) << ":"
		" df 64 6c cf f9 cb ed 11 4a 83 78 28 3d 48 ad 40" "\n"
		"    \n";

	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$p(...)'", "[TRACE_OUT_SYNC_STREAM][p]")
{
	test::stream.str(std::string {});

	$p("hellomoto!")
	$p("wazzzup!")

	const char *expected {
		"// hellomoto!\n"
		"// wazzzup!\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$t(...)'", "[TRACE_OUT_SYNC_STREAM][t]")
{
	test::stream.str(std::string {});

	$t(const char *one {"hellomoto!"};)
	$t(const char *two {"wazzzup!"};)

	const char *expected {
		"const char *one {\"hellomoto!\"}; // trace-out: statement passed\n"
		"const char *two {\"wazzzup!\"}; // trace-out: statement passed\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$f(...)'", "[TRACE_OUT_SYNC_STREAM][f]")
{
	test::stream.str(std::string {});

	some_func();

	const char *expected {
		"void some_func()\n"
		"{\n"
		"    void some_func()\n"
		"    {\n"
		"    } // void some_func()\n"
		"    \n"
		"} // void some_func()\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$if(...)'", "[TRACE_OUT_SYNC_STREAM][if]")
{
	test::stream.str(std::string {});

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
		"    \n"
		"}\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$for(...)'", "[TRACE_OUT_SYNC_STREAM][for]")
{
	test::stream.str(std::string {});

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
		"        \n"
		"    } // for (; true;)\n"
		"    \n"
		"    \n"
		"} // for (; true;)\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$while(...)'", "[TRACE_OUT_SYNC_STREAM][while]")
{
	test::stream.str(std::string {});

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
		"        \n"
		"    } // while (true)\n"
		"    \n"
		"    \n"
		"} // while (true)\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

