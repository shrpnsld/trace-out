#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("'TRACE_OUT_OFF' with '$start'", "[TRACE_OUT_OFF][start]")
{
	test::out_stream.str(std::string {});

	$start();

	REQUIRE(test::out_stream.str() == "");
}
