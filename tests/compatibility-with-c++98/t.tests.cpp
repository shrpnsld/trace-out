#include "dollar-store-catch2.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"

TEST_CASE("$t(<value>)")
{
	SECTION("$t(<const-value>)")
	{
		test::out_stream.str("");

		const trace_out::standard::uint32_t subject1 = 456;
		const trace_out::standard::uint32_t &subject2 = $t(subject1);

		const char *expected = "subject1 = 456" "\n";
		REQUIRE(test::out_stream.str() == expected);
		REQUIRE(&subject2 == &subject1);
	}

	SECTION("$t(<value>)")
	{
		test::out_stream.str("");

		trace_out::standard::uint32_t subject1 = 456;
		trace_out::standard::uint32_t &subject2 = $t(subject1);

		const char *expected = "subject1 = 456" "\n";
		REQUIRE(test::out_stream.str() == expected);
		REQUIRE(&subject2 == &subject1);
	}
}

