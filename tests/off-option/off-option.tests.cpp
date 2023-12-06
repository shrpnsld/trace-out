#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

void subject_func11() {$f }
int subject_func12() { $return 789; }

TEST_CASE("'TRACE_OUT_OFF' with '$t(...)'", "[TRACE_OUT_OFF][t]")
{
	test::out_stream.str(std::string {});

	const char *str {"hellomoto!"};
	dummy($t(str));

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$t<base>(...)'", "[TRACE_OUT_OFF][tbase]")
{
	test::out_stream.str(std::string {});

	int some {456};
	dummy($tbin(some));
	dummy($toct(some));
	dummy($thex(some));

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$tr(...)'", "[TRACE_OUT_OFF][tr]")
{
	test::out_stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};
	dummy(str, length);

	$tr(str, str + length)

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$m(...)'", "[TRACE_OUT_OFF][m]")
{
	test::out_stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};
	dummy(str, length);

	$m(str, length)

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$s(...)'", "[TRACE_OUT_OFF][t]")
{
	test::out_stream.str(std::string {});

	$s(dummy();)

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$f'", "[TRACE_OUT_OFF][f]")
{
	test::out_stream.str(std::string {});

	subject_func11();

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$return'", "[TRACE_OUT_OFF][return]")
{
	test::out_stream.str(std::string {});

	subject_func12();

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$if(...)'", "[TRACE_OUT_OFF][if]")
{
	test::out_stream.str(std::string {});

	$if (true)
	{
	}

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$for(...)'", "[TRACE_OUT_OFF][for]")
{
	test::out_stream.str(std::string {});

	$for ( ; true; )
	{
		break;
	}

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$while(...)'", "[TRACE_OUT_OFF][while]")
{
	test::out_stream.str(std::string {});

	$while (true)
	{
		break;
	}

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$time(...)'", "[TRACE_OUT_OFF][time]")
{
	test::out_stream.str(std::string {});

	$time("dummy", dummy();)

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$time_stats(...)'", "[TRACE_OUT_OFF][time_stats]")
{
	test::out_stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$clocks(...)'", "[TRACE_OUT_OFF][clocks]")
{
	test::out_stream.str(std::string {});

	$clocks("dummy", dummy();)

	REQUIRE(test::out_stream.str() == "");
}

TEST_CASE("'TRACE_OUT_OFF' with '$clock_stats(...)'", "[TRACE_OUT_OFF][clock_stats]")
{
	test::out_stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	REQUIRE(test::out_stream.str() == "");
}

