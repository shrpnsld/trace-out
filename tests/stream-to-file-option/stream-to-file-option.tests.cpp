#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include <fstream>
#include <iterator>
#include <sstream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

int subject_func()
{
	$start("some")
	$thread("main")
	$f

	int subject1 = 456;
	float subject2 = 789.123f;
	std::string subject3 = "hellomoto!";

	$t("hellomoto!");
	$t(subject1);
	$t(subject2);
	$t(subject3);
	$tbin(subject1);
	$toct(subject1);
	$thex(subject1);
	$tbin(subject2);
	$toct(subject2);
	$thex(subject2);
	$tr(subject3.begin(), subject3.end())
	$m(subject3.c_str(), subject3.size() + 1, $hex, $grp(1), $col(8))
	$s(subject3 = "wazuuup!";)

	$if (true)
	{
	}

	$for (;;)
	{
		break;
	}

	$while(true)
	{
		break;
	}

	$time("dummy", dummy();)
	$clocks("dummy", dummy();)
	$time_stats("dummy", 1, dummy();)
	$clock_stats("dummy", 1, dummy();)

	$return 789;
}

TEST_CASE("'TRACE_OUT_STREAM_TO_FILE' option", "[TRACE_OUT_STREAM_TO_FILE]")
{
	using Catch::Matchers::Matches;

	subject_func();

	std::ifstream file(TRACE_OUT_STREAM_TO_FILE);
	REQUIRE(file.is_open());

	std::stringstream expected;
	expected
		<< R"=(@@ )=" << std::endl
		<< R"=(@@ )=" << std::endl
		<< R"=(@@ ################################\[ some [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \]#####################################)=" << std::endl
		<< R"=(@@ )=" << std::endl
		<< R"=(@@ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\[ Thread: main [0-9a-f]+ \]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:13   \| int subject_func\(\))=" << std::endl
		<< R"=(@@                           \| \{)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:19   \|   // hellomoto!)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:20   \|   subject1 = 456)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:21   \|   subject2 = 789.123)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:22   \|   subject3 = "hellomoto!")=" << std::endl
		<< R"=(@@ stream-to-file-opti~:23   \|   subject1 = bin: 00000000 00000000 00000001 11001000)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:24   \|   subject1 = oct: 000000 001310)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:25   \|   subject1 = hex: 000001c8)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:26   \|   subject2 = bin: 0  10001000  1000101 01000111 11011111)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:27   \|   subject2 = oct: 104105 107337)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:28   \|   subject2 = hex: 444547df)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:29   \|   \[subject3\.begin\(\), subject3\.end\(\)\) = \['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!'\])=" << std::endl
		<< R"=(@@ stream-to-file-opti~:30   \|   subject3.c_str\(\), 11 bytes of 1-byte hexadecimal)=" << std::endl
		<< R"=(@@                           \|     [0-9a-f]+: 68 65 6c 6c 6f 6d 6f 74  hellomot)=" << std::endl
		<< R"=(@@                           \|     [0-9a-f]+: 6f 21 00                 o!\.)=" << std::endl
		<< R"=(@@                           \| )=" << std::endl
		<< R"=(@@ stream-to-file-opti~:31   \|   subject3 = "wazuuup!"; // running\.\.\.)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:31   \|   subject3 = "wazuuup!"; // done\.)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:33   \|   if \(true\) => true)=" << std::endl
		<< R"=(@@                           \|   \{)=" << std::endl
		<< R"=(@@                           \|   \} // if \(true\) => true)=" << std::endl
		<< R"=(@@                           \| )=" << std::endl
		<< R"=(@@ stream-to-file-opti~:37   \|   for \(;;\))=" << std::endl
		<< R"=(@@                           \|   \{)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:37   \|     // for: iteration #1)=" << std::endl
		<< R"=(@@                           \| )=" << std::endl
		<< R"=(@@                           \|   \} // for \(;;\))=" << std::endl
		<< R"=(@@                           \| )=" << std::endl
		<< R"=(@@ stream-to-file-opti~:42   \|   while \(true\))=" << std::endl
		<< R"=(@@                           \|   \{)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:42   \|     // while: iteration #1)=" << std::endl
		<< R"=(@@                           \| )=" << std::endl
		<< R"=(@@                           \|   \} // while \(true\))=" << std::endl
		<< R"=(@@                           \| )=" << std::endl
		<< R"=(@@ stream-to-file-opti~:47   \|   Timing "dummy"\.\.\.)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:47   \|   "dummy" timed in [0-9]+ ms)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:48   \|   Clocking "dummy"\.\.\.)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:48   \|   "dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\))=" << std::endl
		<< R"=(@@ stream-to-file-opti~:49   \|   // Execution time statistics \(ms\) for "dummy":)=" << std::endl
		<< R"=(@@                           \|   //   avg/med: [0-9]+ / [0-9]+)=" << std::endl
		<< R"=(@@                           \|   //      mode: [0-9]+ \(100% of all values\))=" << std::endl
		<< R"=(@@                           \|   //     range: [0-9]+ \[[0-9]+\.\.\.[0-9]+\])=" << std::endl
		<< R"=(@@                           \| )=" << std::endl
		<< R"=(@@ stream-to-file-opti~:50   \|   // Execution time statistics \(clocks\) for "dummy":)=" << std::endl
		<< R"=(@@                           \|   //   avg/med: [0-9]+ / [0-9]+)=" << std::endl
		<< R"=(@@                           \|   //      mode: [0-9]+ \([0-9]+% of all values\))=" << std::endl
		<< R"=(@@                           \|   //     range: [0-9]+ \[[0-9]+\.\.\.[0-9]+\])=" << std::endl
		<< R"=(@@                           \| )=" << std::endl
		<< R"=(@@ stream-to-file-opti~:52   \|   return 789)=" << std::endl
		<< R"=(@@ stream-to-file-opti~:13   \| \} // int subject_func\(\))=" << std::endl
		<< R"=(@@                           \| )=" << std::endl;

	while (!file.eof() && !expected.eof())
	{
		std::string line;
		std::getline(file, line);

		std::string regex;
		std::getline(expected, regex);

		REQUIRE_THAT(line, Matches(regex.c_str()));
	}
}

