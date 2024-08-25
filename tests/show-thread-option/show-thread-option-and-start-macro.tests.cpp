#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

using trace_out::RESET_FLAGS;

TEST_CASE("'TRACE_OUT_SHOW_THREAD' and '$start' with '$t(...)'", "[TRACE_OUT_SHOW_THREAD][start][t]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string thread_id {(std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str()};

	$start();

	const char *what {"hellomoto!"};
	$t(what);

	std::stringstream expected;
	expected
		<< R"=(\n)="
		<< R"=(\n)="
		<< R"=(####\[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \]###########################################\n)="
		<< R"=(\n)="
		<< R"=(~~~~\[ Thread: )=" << thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - thread_id.size()) << "" << RESET_FLAGS << R"=(\n)="
		<< R"=(what = "hellomoto!"\n)=";

	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

