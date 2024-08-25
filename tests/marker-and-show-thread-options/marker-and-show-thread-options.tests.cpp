#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <thread>

using trace_out::RESET_FLAGS;

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$t(...)'", "[TRACE_OUT_SHOW_THREAD][thread][t]")
{
	test::out_stream.str(std::string {});

	std::string thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	const char *what {"hellomoto!"};
	$t(what);

	std::stringstream expected;
	expected
		<< R"=(@@ ~~~~[ Thread: )=" << thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 19 - thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(@@ what = "hellomoto!")=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}
