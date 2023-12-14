#include "dollar-store-catch2.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"

TEST_CASE("$t<base>(<value>)")
{
	SECTION("$tbin(<const-value>)")
	{
		test::out_stream.str("");

		const trace_out::standard::uint32_t subject1 = 456;
		const trace_out::standard::uint32_t &subject2 = $tbin(subject1);

		const char *expected = "subject1 = bin: 00000000 00000000 00000001 11001000" "\n";
		REQUIRE(test::out_stream.str() == expected);
		REQUIRE(&subject2 == &subject1);
	}

	SECTION("$tbin(<value>)")
	{
		test::out_stream.str("");

		trace_out::standard::uint32_t subject1 = 456;
		trace_out::standard::uint32_t &subject2 = $tbin(subject1);

		const char *expected = "subject1 = bin: 00000000 00000000 00000001 11001000" "\n";
		REQUIRE(test::out_stream.str() == expected);
		REQUIRE(&subject2 == &subject1);
	}

	SECTION("$toct(<const-value>)")
	{
		test::out_stream.str("");

		const trace_out::standard::uint32_t subject1 = 456;
		const trace_out::standard::uint32_t &subject2 = $toct(subject1);

		const char *expected = "subject1 = oct: 000000 001310" "\n";
		std::cerr << test::out_stream.str() << std::endl;
		REQUIRE(test::out_stream.str() == expected);
		REQUIRE(&subject2 == &subject1);
	}

	SECTION("$toct(<value>)")
	{
		test::out_stream.str("");

		trace_out::standard::uint32_t subject1 = 456;
		trace_out::standard::uint32_t &subject2 = $toct(subject1);

		const char *expected = "subject1 = oct: 000000 001310" "\n";
		std::cerr << test::out_stream.str() << std::endl;
		REQUIRE(test::out_stream.str() == expected);
		REQUIRE(&subject2 == &subject1);
	}

	SECTION("$thex(<const-value>)")
	{
		test::out_stream.str("");

		const trace_out::standard::uint32_t subject1 = 456;
		const trace_out::standard::uint32_t &subject2 = $thex(subject1);

		const char *expected = "subject1 = hex: 000001c8" "\n";
		REQUIRE(test::out_stream.str() == expected);
		REQUIRE(&subject2 == &subject1);
	}

	SECTION("$thex(<value>)")
	{
		test::out_stream.str("");

		trace_out::standard::uint32_t subject1 = 456;
		trace_out::standard::uint32_t &subject2 = $thex(subject1);

		const char *expected = "subject1 = hex: 000001c8" "\n";
		REQUIRE(test::out_stream.str() == expected);
		REQUIRE(&subject2 == &subject1);
	}
}

