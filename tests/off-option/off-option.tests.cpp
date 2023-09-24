#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

void subject_func11() {$f }
int subject_func12() { $return 789; }

TEST_CASE("'TRACE_OUT_OFF' with '$w(...)'", "[TRACE_OUT_OFF][w]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};

	$w(str)

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$e(...)'", "[TRACE_OUT_OFF][e]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};

	char character = $e(str[0]);

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$r(...)'", "[TRACE_OUT_OFF][r]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};

	$r(str, str + length)

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$m(...)'", "[TRACE_OUT_OFF][m]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};

	$m(str, length)

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$p(...)'", "[TRACE_OUT_OFF][p]")
{
	test::stream.str(std::string {});

	$p("wazzzup!")

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$t(...)'", "[TRACE_OUT_OFF][t]")
{
	test::stream.str(std::string {});

	$t(char character {'h'};)

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$f'", "[TRACE_OUT_OFF][f]")
{
	test::stream.str(std::string {});

	subject_func11();

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$return'", "[TRACE_OUT_OFF][return]")
{
	test::stream.str(std::string {});

	subject_func12();

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$if(...)'", "[TRACE_OUT_OFF][if]")
{
	test::stream.str(std::string {});

	$if (true)
	{
	}

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$for(...)'", "[TRACE_OUT_OFF][for]")
{
	test::stream.str(std::string {});

	$for ( ; true; )
	{
		break;
	}

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$while(...)'", "[TRACE_OUT_OFF][while]")
{
	test::stream.str(std::string {});

	$while (true)
	{
		break;
	}

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$time(...)'", "[TRACE_OUT_OFF][time]")
{
	test::stream.str(std::string {});

	$time("dummy", dummy();)

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$time_stats(...)'", "[TRACE_OUT_OFF][time_stats]")
{
	test::stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$clocks(...)'", "[TRACE_OUT_OFF][clocks]")
{
	test::stream.str(std::string {});

	$clocks("dummy", dummy();)

	REQUIRE(test::stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$clock_stats(...)'", "[TRACE_OUT_OFF][clock_stats]")
{
	test::stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	REQUIRE(test::stream.str() == "");
}

