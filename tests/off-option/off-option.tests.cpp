#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

void subject_func11() {$f }
int subject_func12() { $return 789; }

TEST_CASE("TRACE_OUT_MARKER with '$w(...)'", "[TRACE_OUT_MARKER][w]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};

	$w(str)
	REQUIRE(test::stream.str() == "");
}

TEST_CASE("TRACE_OUT_MARKER with '$e(...)'", "[TRACE_OUT_MARKER][e]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	char character = $e(str[0]);
	REQUIRE(test::stream.str() == "");
}

TEST_CASE("TRACE_OUT_MARKER with '$r(...)'", "[TRACE_OUT_MARKER][r]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};

	$r(str, str + length)
	REQUIRE(test::stream.str() == "");
}

TEST_CASE("TRACE_OUT_MARKER with '$m(...)'", "[TRACE_OUT_MARKER][m]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};

	$m(str, length)
	REQUIRE(test::stream.str() == "");
}

TEST_CASE("TRACE_OUT_MARKER with '$p(...)'", "[TRACE_OUT_MARKER][p]")
{
	test::stream.str(std::string {});

	$p("wazzzup!")
	REQUIRE(test::stream.str() == "");
}

TEST_CASE("TRACE_OUT_MARKER with '$t(...)'", "[TRACE_OUT_MARKER][t]")
{
	test::stream.str(std::string {});

	$t(char character {'h'};)
	REQUIRE(test::stream.str() == "");
}

TEST_CASE("TRACE_OUT_MARKER with '$f'", "[TRACE_OUT_MARKER][f]")
{
	test::stream.str(std::string {});

	subject_func11();
	REQUIRE(test::stream.str() == "");
}

TEST_CASE("TRACE_OUT_MARKER with '$return'", "[TRACE_OUT_MARKER][return]")
{
	test::stream.str(std::string {});

	subject_func12();
	REQUIRE(test::stream.str() == "");
}

TEST_CASE("TRACE_OUT_MARKER with '$if(...)'", "[TRACE_OUT_MARKER][if]")
{
	test::stream.str(std::string {});

	$if (true)
	{
	}
	REQUIRE(test::stream.str() == "");
}

TEST_CASE("TRACE_OUT_MARKER with '$for(...)'", "[TRACE_OUT_MARKER][for]")
{
	test::stream.str(std::string {});

	$for ( ; true; )
	{
		break;
	}
	REQUIRE(test::stream.str() == "");
}

TEST_CASE("TRACE_OUT_MARKER with '$while(...)'", "[TRACE_OUT_MARKER][while]")
{
	test::stream.str(std::string {});

	$while (true)
	{
		break;
	}
	REQUIRE(test::stream.str() == "");
}

