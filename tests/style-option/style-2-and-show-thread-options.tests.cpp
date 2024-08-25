#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <thread>

using trace_out::RESET_FLAGS;

TEST_CASE("'TRACE_OUT_STYLE=2' and 'TRACE_OUT_SHOW_THREAD'", "[TRACE_OUT_STYLE][TRACE_OUT_SHOW_THREAD]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	$thread("one")
	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id](const char *what)
	{
		$thread("two")
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$t(what);
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	$t(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: [0;36mtwo[0m [0;35m)=" << two_thread_id << R"=([0m ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=([0;36mwhat[0m = [0;33m"wazuuup!"[0m)=" << std::endl
		<< R"=(~~~~[ Thread: [0;36mone[0m [0;35m)=" << one_thread_id << R"=([0m ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=([0;36mwhat[0m = [0;33m"hellomoto!"[0m)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

