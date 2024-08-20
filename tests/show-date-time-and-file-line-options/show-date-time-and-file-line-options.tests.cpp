#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

using trace_out::RESET_FLAGS;

TEST_CASE("'TRACE_OUT_SHOW_DATE_TIME' with 'TRACE_OUT_SHOW_FILE_LINE'", "[TRACE_OUT_SHOW_DATE_TIME][TRACE_OUT_SHOW_FILE_LINE]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	const char *str {"hellomoto!"};

	long int line {__LINE__ + 1};
	$t(str);

	std::stringstream expected;
	expected << "[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2}  show-date-time-and~:" << std::setw(4) << std::left << line << RESET_FLAGS << R"=( \| str = "hellomoto!"\n)=";
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

