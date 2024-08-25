#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <cstring>
#include <sstream>
#include <thread>

using trace_out::RESET_FLAGS;

void subject_func1(const char *what) {$f $t(what); }
const char *subject_func2(const char *what) { $return what; }

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$t(...)'", "[TRACE_OUT_SHOW_THREAD][thread][t]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$t(what);
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	$t(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = "wazuuup!")=" << std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = "hellomoto!")=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$tbin(...)'", "[TRACE_OUT_SHOW_THREAD][thread][tbin]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id](int what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$tbin(what);
	}, 456}.join();

	int what {456};
	$tbin(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = bin: 00000000 00000000 00000001 11001000)=" << std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = bin: 00000000 00000000 00000001 11001000)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$toct(...)'", "[TRACE_OUT_SHOW_THREAD][thread][toct]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id](int what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$toct(what);
	}, 456}.join();

	int what {456};
	$toct(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = oct: 000000 001310)=" << std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = oct: 000000 001310)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thex(...)'", "[TRACE_OUT_SHOW_THREAD][thread][thex]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id](int what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thex(what);
	}, 456}.join();

	int what {456};
	$thex(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = hex: 000001c8)=" << std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = hex: 000001c8)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$tr(...)'", "[TRACE_OUT_SHOW_THREAD][thread][tr]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	SECTION(".begin(), .end()")
	{
		one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		std::thread {[&two_thread_id](const char *what)
		{
			two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
			const char *end {what + std::strlen(what)};
			$tr(what, end)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		const char *end {what + std::strlen(what)};
		$tr(what, end)

		std::stringstream expected;
		expected
			<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end) = ['w', 'a', 'z', 'u', 'u', 'u', 'p', '!'])=" << std::endl
			<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end) = ['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!'])=" << std::endl;
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION(".begin(), how_much")
	{
		one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		std::thread {[&two_thread_id](const char *what)
		{
			two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
			$tr(what, 5)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		$tr(what, 5)

		std::stringstream expected;
		expected
			<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what: 5] = ['w', 'a', 'z', 'u', 'u'])=" << std::endl
			<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what: 5] = ['h', 'e', 'l', 'l', 'o'])=" << std::endl;
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION(".begin(), .end(), how_much")
	{
		one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		std::thread {[&two_thread_id](const char *what)
		{
			two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
			const char *end {what + std::strlen(what)};
			$tr(what, end, 5)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		const char *end {what + std::strlen(what)};
		$tr(what, end, 5)

		std::stringstream expected;
		expected
			<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end):5 = ['w', 'a', 'z', 'u', 'u'])=" << std::endl
			<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end):5 = ['h', 'e', 'l', 'l', 'o'])=" << std::endl;
		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$m(...)'", "[TRACE_OUT_SHOW_THREAD][thread][m]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	const char *str {"wazuuup!"};
	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		std::size_t size {std::strlen(what) + 1};

		$m(what, size)
	}, str}.join();

	const char *what {"hellomoto!"};
	std::size_t size {std::strlen(what) + 1};
	$m(what, size)

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what, 9 bytes of 1-byte hexadecimal)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(str) << RESET_FLAGS << R"=(: 77 61 7a 75 75 75 70 21  wazuuup!)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(reinterpret_cast<const std::uint8_t*>(str) + 8) << RESET_FLAGS << R"=(: 00                       .)=" << std::endl
		<< std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what, 11 bytes of 1-byte hexadecimal)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(what) << RESET_FLAGS << R"=(: 68 65 6c 6c 6f 6d 6f 74  hellomot)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(reinterpret_cast<const std::uint8_t*>(what) + 8) << RESET_FLAGS << R"=(: 6f 21 00                 o!.)=" << std::endl
		<< std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$s(...)'", "[TRACE_OUT_SHOW_THREAD][thread][s]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$s(dummy("wazuuup!");)
	}}.join();

	$s(dummy("hellomoto!");)

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(dummy("wazuuup!"); // running...)=" << std::endl
		<< R"=(dummy("wazuuup!"); // done.)=" << std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(dummy("hellomoto!"); // running...)=" << std::endl
		<< R"=(dummy("hellomoto!"); // done.)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$f'", "[TRACE_OUT_SHOW_THREAD][thread][f]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		subject_func1(what);
	}, "wazuuup!"}.join();

	subject_func1("hellomoto!");

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(void subject_func1(const char *))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    what = "wazuuup!")=" << std::endl
		<< R"=(} // void subject_func1(const char *))=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(void subject_func1(const char *))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    what = "hellomoto!")=" << std::endl
		<< R"=(} // void subject_func1(const char *))=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$return'", "[TRACE_OUT_SHOW_THREAD][thread][return]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		subject_func2(what);
	}, "wazuuup!"}.join();

	subject_func2("hellomoto!");

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(return "wazuuup!")=" << std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(return "hellomoto!")=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$if(...)'", "[TRACE_OUT_SHOW_THREAD][thread][if]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$if (what)
		{
		}
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	$if (what)
	{
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(if (what) => true ("wazuuup!"))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(} // if (what) => true)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(if (what) => true ("hellomoto!"))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(} // if (what) => true)=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$for(...)'", "[TRACE_OUT_SHOW_THREAD][thread][for]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$for (;;)
		{
			break;
		}
	}}.join();

	$for (;;)
	{
		break;
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(for (;;))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // for: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // for (;;))=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(for (;;))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // for: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // for (;;))=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$while(...)'", "[TRACE_OUT_SHOW_THREAD][thread][for]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$while (true)
		{
			break;
		}
	}}.join();

	$while (true)
	{
		break;
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(while (true))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // while: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // while (true))=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(while (true))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // while: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // while (true))=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$time(...)'", "[TRACE_OUT_SHOW_THREAD][thread][time]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$time("dummy", dummy();)
	}}.join();

	$time("dummy", dummy();)

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Timing "dummy"...)=" << std::endl
		<< R"=("dummy" timed in [0-9]+ ms)=" << std::endl
		<< R"=(~~~~\[ Thread: )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Timing "dummy"...)=" << std::endl
		<< R"=("dummy" timed in [0-9]+ ms)=" << std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$time_stats(...)'", "[TRACE_OUT_SHOW_THREAD][thread][time_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$time_stats("dummy", 10, dummy();)
		}
	}}.join();

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(ms\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl
		<< R"=(~~~~\[ Thread: )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(ms\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$clocks(...)'", "[TRACE_OUT_SHOW_THREAD][thread][clocks]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$clocks("dummy", dummy();)
	}}.join();

	$clocks("dummy", dummy();)

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Clocking "dummy"...)=" << std::endl
		<< R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\))=" << std::endl
		<< R"=(~~~~\[ Thread: )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Clocking "dummy"...)=" << std::endl
		<< R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\))=" << std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$clock_stats(...)'", "[TRACE_OUT_SHOW_THREAD][thread][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$clock_stats("dummy", 10, dummy();)
		}
	}}.join();

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread\: )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(clocks\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl
		<< R"=(~~~~\[ Thread\: )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(clocks\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$t(...)'", "[TRACE_OUT_SHOW_THREAD][thread][t]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		$t(what);
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	$t(what);
	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = "wazuuup!")=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = "hellomoto!")=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$tbin(...)'", "[TRACE_OUT_SHOW_THREAD][thread][tbin]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](int what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		$tbin(what);
	}, 456}.join();

	int what {456};
	$tbin(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = bin: 00000000 00000000 00000001 11001000)=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = bin: 00000000 00000000 00000001 11001000)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$toct(...)'", "[TRACE_OUT_SHOW_THREAD][thread][toct]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](int what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		$toct(what);
	}, 456}.join();

	int what {456};
	$toct(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = oct: 000000 001310)=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = oct: 000000 001310)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$thex(...)'", "[TRACE_OUT_SHOW_THREAD][thread][thex]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](int what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		$thex(what);
	}, 456}.join();

	int what {456};
	$thex(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = hex: 000001c8)=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = hex: 000001c8)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$tr(...)'", "[TRACE_OUT_SHOW_THREAD][thread][tr]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	SECTION(".begin(), .end()")
	{
		one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("one")

		std::thread {[&two_thread_id](const char *what)
		{
			two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
			$thread("two")

			const char *end {what + std::strlen(what)};
			$tr(what, end)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		const char *end {what + std::strlen(what)};
		$tr(what, end)

		std::stringstream expected;
		expected
			<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end) = ['w', 'a', 'z', 'u', 'u', 'u', 'p', '!'])=" << std::endl
			<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end) = ['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!'])=" << std::endl;
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION(".begin(), how_much")
	{
		one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("one")

		std::thread {[&two_thread_id](const char *what)
		{
			two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
			$thread("two")

			$tr(what, 5)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		$tr(what, 5)

		std::stringstream expected;
		expected
			<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what: 5] = ['w', 'a', 'z', 'u', 'u'])=" << std::endl
			<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what: 5] = ['h', 'e', 'l', 'l', 'o'])=" << std::endl;
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION(".begin(), .end(), how_much")
	{
		one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("one")

		std::thread {[&two_thread_id](const char *what)
		{
			two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
			$thread("two")

			const char *end {what + std::strlen(what)};
			$tr(what, end, 5)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		const char *end {what + std::strlen(what)};
		$tr(what, end, 5)

		std::stringstream expected;
		expected
			<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end):5 = ['w', 'a', 'z', 'u', 'u'])=" << std::endl
			<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end):5 = ['h', 'e', 'l', 'l', 'o'])=" << std::endl;
		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$m(...)'", "[TRACE_OUT_SHOW_THREAD][thread][m]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	const char *str {"wazuuup!"};
	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		std::size_t size {std::strlen(what) + 1};
		$m(what, size)
	}, str}.join();

	const char *what {"hellomoto!"};
	std::size_t size {std::strlen(what) + 1};
	$m(what, size)

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what, 9 bytes of 1-byte hexadecimal)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(str) << RESET_FLAGS << R"=(: 77 61 7a 75 75 75 70 21  wazuuup!)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(reinterpret_cast<const std::uint8_t*>(str) + 8) << RESET_FLAGS << R"=(: 00                       .)=" << std::endl
		<< std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what, 11 bytes of 1-byte hexadecimal)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(what) << RESET_FLAGS << R"=(: 68 65 6c 6c 6f 6d 6f 74  hellomot)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(reinterpret_cast<const std::uint8_t*>(what) + 8) << RESET_FLAGS << R"=(: 6f 21 00                 o!.)=" << std::endl
		<< std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$s(...)'", "[TRACE_OUT_SHOW_THREAD][thread][s]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		$s(dummy("wazuuup!");)
	}}.join();

	$s(dummy("hellomoto!");)

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(dummy("wazuuup!"); // running...)=" << std::endl
		<< R"=(dummy("wazuuup!"); // done.)=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(dummy("hellomoto!"); // running...)=" << std::endl
		<< R"=(dummy("hellomoto!"); // done.)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$f'", "[TRACE_OUT_SHOW_THREAD][thread][f]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		subject_func1(what);
	}, "wazuuup!"}.join();

	subject_func1("hellomoto!");

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(void subject_func1(const char *))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    what = "wazuuup!")=" << std::endl
		<< R"=(} // void subject_func1(const char *))=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(void subject_func1(const char *))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    what = "hellomoto!")=" << std::endl
		<< R"=(} // void subject_func1(const char *))=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$return'", "[TRACE_OUT_SHOW_THREAD][thread][return]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		subject_func2(what);
	}, "wazuuup!"}.join();

	subject_func2("hellomoto!");

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(return "wazuuup!")=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(return "hellomoto!")=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$if(...)'", "[TRACE_OUT_SHOW_THREAD][thread][if]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		$if (what)
		{
		}
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	$if (what)
	{
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(if (what) => true ("wazuuup!"))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(} // if (what) => true)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(if (what) => true ("hellomoto!"))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(} // if (what) => true)=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$for(...)'", "[TRACE_OUT_SHOW_THREAD][thread][for]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		$for (;;)
		{
			break;
		}
	}}.join();

	$for (;;)
	{
		break;
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(for (;;))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // for: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // for (;;))=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(for (;;))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // for: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // for (;;))=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$while(...)'", "[TRACE_OUT_SHOW_THREAD][thread][for]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		$while (true)
		{
			break;
		}
	}}.join();

	$while (true)
	{
		break;
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: two )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(while (true))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // while: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // while (true))=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(while (true))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // while: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // while (true))=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$time(...)'", "[TRACE_OUT_SHOW_THREAD][thread][time]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		$time("dummy", dummy();)
	}}.join();

	$time("dummy", dummy();)

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: two )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Timing "dummy"...)=" << std::endl
		<< R"=("dummy" timed in [0-9]+ ms)=" << std::endl
		<< R"=(~~~~\[ Thread: one )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Timing "dummy"...)=" << std::endl
		<< R"=("dummy" timed in [0-9]+ ms)=" << std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$time_stats(...)'", "[TRACE_OUT_SHOW_THREAD][thread][time_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$time_stats("dummy", 10, dummy();)
		}
	}}.join();

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: two )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(ms\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl
		<< R"=(~~~~\[ Thread: one )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(ms\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$clocks(...)'", "[TRACE_OUT_SHOW_THREAD][thread][clocks]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		$clocks("dummy", dummy();)
	}}.join();

	$clocks("dummy", dummy();)

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: two )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Clocking "dummy"...)=" << std::endl
		<< R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\))=" << std::endl
		<< R"=(~~~~\[ Thread: one )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Clocking "dummy"...)=" << std::endl
		<< R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\))=" << std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(...)' and '$clock_stats(...)'", "[TRACE_OUT_SHOW_THREAD][thread][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("two")

		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$clock_stats("dummy", 10, dummy();)
		}
	}}.join();

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: two )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(clocks\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl
		<< R"=(~~~~\[ Thread: one )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(clocks\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$t(...)'", "[TRACE_OUT_SHOW_THREAD][thread][t]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		$t(what);
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	$t(what);
	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = "wazuuup!")=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = "hellomoto!")=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$tbin(...)'", "[TRACE_OUT_SHOW_THREAD][thread][tbin]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](int what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		$tbin(what);
	}, 456}.join();

	int what {456};
	$tbin(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = bin: 00000000 00000000 00000001 11001000)=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = bin: 00000000 00000000 00000001 11001000)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$toct(...)'", "[TRACE_OUT_SHOW_THREAD][thread][toct]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](int what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		$toct(what);
	}, 456}.join();

	int what {456};
	$toct(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = oct: 000000 001310)=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = oct: 000000 001310)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$thex(...)'", "[TRACE_OUT_SHOW_THREAD][thread][thex]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](int what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		$thex(what);
	}, 456}.join();

	int what {456};
	$thex(what);

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = hex: 000001c8)=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what = hex: 000001c8)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$tr(...)'", "[TRACE_OUT_SHOW_THREAD][thread][tr]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	SECTION(".begin(), .end()")
	{
		one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("one")

		std::thread {[&two_thread_id](const char *what)
		{
			two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

			const char *end {what + std::strlen(what)};
			$tr(what, end)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		const char *end {what + std::strlen(what)};
		$tr(what, end)

		std::stringstream expected;
		expected
			<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end) = ['w', 'a', 'z', 'u', 'u', 'u', 'p', '!'])=" << std::endl
			<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end) = ['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!'])=" << std::endl;
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION(".begin(), how_much")
	{
		one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("one")

		std::thread {[&two_thread_id](const char *what)
		{
			two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

			$tr(what, 5)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		$tr(what, 5)

		std::stringstream expected;
		expected
			<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what: 5] = ['w', 'a', 'z', 'u', 'u'])=" << std::endl
			<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what: 5] = ['h', 'e', 'l', 'l', 'o'])=" << std::endl;
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION(".begin(), .end(), how_much")
	{
		one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
		$thread("one")

		std::thread {[&two_thread_id](const char *what)
		{
			two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

			const char *end {what + std::strlen(what)};
			$tr(what, end, 5)
		}, "wazuuup!"}.join();

		const char *what {"hellomoto!"};
		const char *end {what + std::strlen(what)};
		$tr(what, end, 5)

		std::stringstream expected;
		expected
			<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end):5 = ['w', 'a', 'z', 'u', 'u'])=" << std::endl
			<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
			<< R"=([what, end):5 = ['h', 'e', 'l', 'l', 'o'])=" << std::endl;
		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$m(...)'", "[TRACE_OUT_SHOW_THREAD][thread][m]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	const char *str {"wazuuup!"};
	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		std::size_t size {std::strlen(what) + 1};
		$m(what, size)
	}, str}.join();

	const char *what {"hellomoto!"};
	std::size_t size {std::strlen(what) + 1};
	$m(what, size)

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what, 9 bytes of 1-byte hexadecimal)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(str) << RESET_FLAGS << R"=(: 77 61 7a 75 75 75 70 21  wazuuup!)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(reinterpret_cast<const std::uint8_t*>(str) + 8) << RESET_FLAGS << R"=(: 00                       .)=" << std::endl
		<< std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(what, 11 bytes of 1-byte hexadecimal)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(what) << RESET_FLAGS << R"=(: 68 65 6c 6c 6f 6d 6f 74  hellomot)=" << std::endl
		<< R"=(    )=" << std::setbase(16) << reinterpret_cast<std::size_t>(reinterpret_cast<const std::uint8_t*>(what) + 8) << RESET_FLAGS << R"=(: 6f 21 00                 o!.)=" << std::endl
		<< std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$s(...)'", "[TRACE_OUT_SHOW_THREAD][thread][s]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		$s(dummy("wazuuup!");)
	}}.join();

	$s(dummy("hellomoto!");)

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(dummy("wazuuup!"); // running...)=" << std::endl
		<< R"=(dummy("wazuuup!"); // done.)=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(dummy("hellomoto!"); // running...)=" << std::endl
		<< R"=(dummy("hellomoto!"); // done.)=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$f'", "[TRACE_OUT_SHOW_THREAD][thread][f]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		subject_func1(what);
	}, "wazuuup!"}.join();

	subject_func1("hellomoto!");

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(void subject_func1(const char *))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    what = "wazuuup!")=" << std::endl
		<< R"=(} // void subject_func1(const char *))=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(void subject_func1(const char *))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    what = "hellomoto!")=" << std::endl
		<< R"=(} // void subject_func1(const char *))=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$return'", "[TRACE_OUT_SHOW_THREAD][thread][return]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		subject_func2(what);
	}, "wazuuup!"}.join();

	subject_func2("hellomoto!");

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(return "wazuuup!")=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(return "hellomoto!")=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$if(...)'", "[TRACE_OUT_SHOW_THREAD][thread][if]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id](const char *what)
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		$if (what)
		{
		}
	}, "wazuuup!"}.join();

	const char *what {"hellomoto!"};
	$if (what)
	{
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(if (what) => true ("wazuuup!"))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(} // if (what) => true)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(if (what) => true ("hellomoto!"))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(} // if (what) => true)=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$for(...)'", "[TRACE_OUT_SHOW_THREAD][thread][for]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		$for (;;)
		{
			break;
		}
	}}.join();

	$for (;;)
	{
		break;
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(for (;;))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // for: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // for (;;))=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(for (;;))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // for: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // for (;;))=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$while(...)'", "[TRACE_OUT_SHOW_THREAD][thread][for]")
{
	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		$while (true)
		{
			break;
		}
	}}.join();

	$while (true)
	{
		break;
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~[ Thread: )=" << two_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(while (true))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // while: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // while (true))=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(~~~~[ Thread: one )=" << one_thread_id << R"=( ])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(while (true))=" << std::endl
		<< R"=({)=" << std::endl
		<< R"=(    // while: iteration #1)=" << std::endl
		<< R"=()=" << std::endl
		<< R"=(} // while (true))=" << std::endl
		<< R"=()=" << std::endl;
	REQUIRE(test::out_stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$time(...)'", "[TRACE_OUT_SHOW_THREAD][thread][time]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		$time("dummy", dummy();)
	}}.join();

	$time("dummy", dummy();)

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Timing "dummy"...)=" << std::endl
		<< R"=("dummy" timed in [0-9]+ ms)=" << std::endl
		<< R"=(~~~~\[ Thread: one )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Timing "dummy"...)=" << std::endl
		<< R"=("dummy" timed in [0-9]+ ms)=" << std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$time_stats(...)'", "[TRACE_OUT_SHOW_THREAD][thread][time_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$time_stats("dummy", 10, dummy();)
		}
	}}.join();

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(ms\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl
		<< R"=(~~~~\[ Thread: one )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(ms\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$clocks(...)'", "[TRACE_OUT_SHOW_THREAD][thread][clocks]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		$clocks("dummy", dummy();)
	}}.join();

	$clocks("dummy", dummy();)

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Clocking "dummy"...)=" << std::endl
		<< R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\))=" << std::endl
		<< R"=(~~~~\[ Thread: one )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(Clocking "dummy"...)=" << std::endl
		<< R"=("dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\))=" << std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$thread(\"one\")' and '$clock_stats(...)'", "[TRACE_OUT_SHOW_THREAD][thread][clock_stats]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	std::string one_thread_id;
	std::string two_thread_id;

	one_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();
	$thread("one")

	std::thread {[&two_thread_id]()
	{
		two_thread_id = (std::stringstream {} << std::setbase(16) << trace_out::system::current_thread_id()).str();

		for (std::size_t passes {10}; passes > 0; --passes)
		{
			$clock_stats("dummy", 10, dummy();)
		}
	}}.join();

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	std::stringstream expected;
	expected
		<< R"=(~~~~\[ Thread: )=" << two_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 16 - two_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(clocks\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl
		<< R"=(~~~~\[ Thread: one )=" << one_thread_id << R"=( \])=" << std::setfill('~') << std::setw(TRACE_OUT_STREAM_WIDTH - 20 - one_thread_id.size()) << "" << RESET_FLAGS << std::endl
		<< R"=(// Execution time statistics \(clocks\) for "dummy":)=" << std::endl
		<< R"=(//   avg/med: [0-9\.]+ / [0-9\.]+)=" << std::endl
		<< R"=(//     ( mode|modes): [0-9\.]+(, [0-9\.]+)* \((each = [0-9\.]+%, all = )?[0-9\.]+% of all values\))=" << std::endl
		<< R"=(//     range: [0-9\.]+ \[[0-9\.]+\.\.\.[0-9\.]+\])=" << std::endl
		<< std::endl;
	REQUIRE_THAT(test::out_stream.str(), Matches(expected.str()));
}

