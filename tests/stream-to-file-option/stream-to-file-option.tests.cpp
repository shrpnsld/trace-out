#include "dummy.hpp"
#include "trace-out/trace-out.hpp"
#include <fstream>
#include <iterator>
#include <sstream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

int subject_func();

TEST_CASE("'TRACE_OUT_STREAM_TO_FILE' option", "[TRACE_OUT_STREAM_TO_FILE]")
{
	using Catch::Matchers::Matches;

	subject_func();

	std::ifstream file(TRACE_OUT_STREAM_TO_FILE);
	REQUIRE(file.is_open());

	std::stringstream expected;
	expected
		<< R"(@@ ~~~~\[Thread: [0-9a-f]+ main\]~~~~)" << std::endl
		<< R"(@@  stream-to-file-opt~:83   \| int subject_func\(\))" << std::endl
		<< R"(@@                           \| \{)" << std::endl
		<< R"(@@  stream-to-file-opt~:88   \|   // hellomoto!)" << std::endl
		<< R"(@@  stream-to-file-opt~:89   \|   subject1 = 456)" << std::endl
		<< R"(@@  stream-to-file-opt~:90   \|   subject2 = 789.123)" << std::endl
		<< R"(@@  stream-to-file-opt~:91   \|   subject3 = "hellomoto!")" << std::endl
		<< R"(@@  stream-to-file-opt~:92   \|   \[subject3\.begin\(\), subject3\.end\(\)\) = \['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!'\])" << std::endl
		<< R"(@@  stream-to-file-opt~:93   \|   subject3.c_str\(\), 10 bytes of 1-byte hexadecimal)" << std::endl
		<< R"(@@                           \|     [0-9a-f]+: 68 65 6c 6c 6f 6d 6f 74)" << std::endl
		<< R"(@@                           \|     [0-9a-f]+: 6f 21)" << std::endl
		<< R"(@@                           \| )" << std::endl
		<< R"(@@  stream-to-file-opt~:94   \|   subject3 = "wazuuup!"; // running\.\.\.)" << std::endl
		<< R"(@@  stream-to-file-opt~:94   \|   subject3 = "wazuuup!"; // done\.)" << std::endl
		<< R"(@@  stream-to-file-opt~:96   \|   if \(true\) => true)" << std::endl
		<< R"(@@                           \|   \{)" << std::endl
		<< R"(@@                           \|   \})" << std::endl
		<< R"(@@                           \| )" << std::endl
		<< R"(@@  stream-to-file-opt~:100  \|   for \(;;\))" << std::endl
		<< R"(@@                           \|   \{)" << std::endl
		<< R"(@@  stream-to-file-opt~:100  \|     // for: iteration #1)" << std::endl
		<< R"(@@                           \| )" << std::endl
		<< R"(@@                           \|   \} // for \(;;\))" << std::endl
		<< R"(@@                           \| )" << std::endl
		<< R"(@@  stream-to-file-opt~:105  \|   while \(true\))" << std::endl
		<< R"(@@                           \|   \{)" << std::endl
		<< R"(@@  stream-to-file-opt~:105  \|     // while: iteration #1)" << std::endl
		<< R"(@@                           \| )" << std::endl
		<< R"(@@                           \|   \} // while \(true\))" << std::endl
		<< R"(@@                           \| )" << std::endl
		<< R"(@@  stream-to-file-opt~:110  \|   timing "dummy"\.\.\.)" << std::endl
		<< R"(@@  stream-to-file-opt~:110  \|   "dummy" timed in [0-9]+ ms)" << std::endl
		<< R"(@@  stream-to-file-opt~:111  \|   clocking "dummy"\.\.\.)" << std::endl
		<< R"(@@  stream-to-file-opt~:111  \|   "dummy" clocked in [0-9]+ clocks \([0-9\.]+ ms\))" << std::endl
		<< R"(@@  stream-to-file-opt~:112  \|   // execution time statistics \(ms\) for "dummy":)" << std::endl
		<< R"(@@                           \|   //   avg/med: [0-9]+ / [0-9]+)" << std::endl
		<< R"(@@                           \|   //      mode: [0-9]+ \(100% of all values\))" << std::endl
		<< R"(@@                           \|   //     range: [0-9]+ \[[0-9]+\.\.\.[0-9]+\])" << std::endl
		<< R"(@@                           \| )" << std::endl
		<< R"(@@  stream-to-file-opt~:113  \|   // execution time statistics \(clocks\) for "dummy":)" << std::endl
		<< R"(@@                           \|   //   avg/med: [0-9]+ / [0-9]+)" << std::endl
		<< R"(@@                           \|   //      mode: [0-9]+ \([0-9]+% of all values\))" << std::endl
		<< R"(@@                           \|   //     range: [0-9]+ \[[0-9]+\.\.\.[0-9]+\])" << std::endl
		<< R"(@@                           \| )" << std::endl
		<< R"(@@  stream-to-file-opt~:115  \|   return 789)" << std::endl
		<< R"(@@  stream-to-file-opt~:83   \| \} // int subject_func\(\))" << std::endl
		<< R"(@@                           \| )" << std::endl;

	while (!file.eof() && !expected.eof())
	{
		std::string line;
		std::getline(file, line);

		std::string regex;
		std::getline(expected, regex);

		REQUIRE_THAT(line, Matches(regex.c_str()));
	}
}

int subject_func()
{$thread(main) $f
	int subject1 = 456;
	float subject2 = 789.123f;
	std::string subject3 = "hellomoto!";

	$t("hellomoto!");
	$t(subject1);
	$t(subject2);
	$t(subject3);
	$r(subject3.begin(), subject3.end())
	$m(subject3.c_str(), subject3.size(), $hex(1), $col(8))
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

