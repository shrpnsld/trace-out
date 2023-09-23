#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <cstring>
#include <sstream>
#include <thread>

void subject_func1(const char *what) {$f $w(what) }
const char *subject_func2(const char *what) { $return what; }

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$w(...)'", "[TRACE_OUT_SHOW_THREAD][w]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		$w(what)
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	$w(what)

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
what = "wazzzup!"
\[Thread\: 0x[0-9a-f]+ one\]~+
what = "hellomoto!"
)"));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$e(...)'", "[TRACE_OUT_SHOW_THREAD][e]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		$e(what);
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	$e(what);

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
what = "wazzzup!"
\[Thread\: 0x[0-9a-f]+ one\]~+
what = "hellomoto!"
)"));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$r(...)'", "[TRACE_OUT_SHOW_THREAD][r]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		const char *end {what + std::strlen(what)};
		$r(what, end)
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	const char *end {what + std::strlen(what)};
	$r(what, end)

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
\[what, end\) = \['w', 'a', 'z', 'z', 'z', 'u', 'p', '!'\]
\[Thread\: 0x[0-9a-f]+ one\]~+
\[what, end\) = \['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!'\]
)"));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$m(...)'", "[TRACE_OUT_SHOW_THREAD][m]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		std::size_t size {std::strlen(what)};

		$thread(two)
		$m(what, size)
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	std::size_t size {std::strlen(what)};
	$m(what, size)

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
what, 8 bytes of 1-byte hexadecimal
    0x[0-9a-f]+: 77 61 7a 7a 7a 75 70 21
    
\[Thread\: 0x[0-9a-f]+ one\]~+
what, 10 bytes of 1-byte hexadecimal
    0x[0-9a-f]+: 68 65 6c 6c 6f 6d 6f 74 6f 21
    
)"));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$p(...)'", "[TRACE_OUT_SHOW_THREAD][p]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		$p(what)
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	$p(what)

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
// wazzzup!
\[Thread\: 0x[0-9a-f]+ one\]~+
// hellomoto!
)"));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$t(...)'", "[TRACE_OUT_SHOW_THREAD][t]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$t(const char *what {"wazzzup!"};)
	}}.join();

	$t(const char *what {"hellomoto!"};)

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
const char \*what \{"wazzzup!"\}; // trace-out: statement passed
\[Thread\: 0x[0-9a-f]+ one\]~+
const char \*what \{"hellomoto!"\}; // trace-out: statement passed
)"));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$f'", "[TRACE_OUT_SHOW_THREAD][f]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		subject_func1(what);
	}, "wazzzup!"}.join();

	subject_func1("hellomoto!");

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
void subject_func1\(const char \*\)
\{
    what = "wazzzup!"
\} // void subject_func1\(const char \*\)

\[Thread\: 0x[0-9a-f]+ one\]~+
void subject_func1\(const char \*\)
\{
    what = "hellomoto!"
\} // void subject_func1\(const char \*\)

)"));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$return'", "[TRACE_OUT_SHOW_THREAD][return]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		subject_func2(what);
	}, "wazzzup!"}.join();

	subject_func2("hellomoto!");

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
return "wazzzup!"
\[Thread\: 0x[0-9a-f]+ one\]~+
return "hellomoto!"
)"));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$if(...)'", "[TRACE_OUT_SHOW_THREAD][if]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[](const char *what)
	{
		$thread(two)
		$if (what)
		{
		}
	}, "wazzzup!"}.join();

	const char *what {"hellomoto!"};
	$if (what)
	{
	}

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
if \(what\) => true \("wazzzup!"\)
\{
\}

\[Thread\: 0x[0-9a-f]+ one\]~+
if \(what\) => true \("hellomoto!"\)
\{
\}

)"));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$for(...)'", "[TRACE_OUT_SHOW_THREAD][for]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$for (;;)
		{
			break;
		}
	}}.join();

	$for (;;)
	{
		break;
	}

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
for \(;;\)
\{
    // for: iteration #1
    
\} // for \(;;\)

\[Thread\: 0x[0-9a-f]+ one\]~+
for \(;;\)
\{
    // for: iteration #1
    
\} // for \(;;\)

)"));
}

TEST_CASE("'TRACE_OUT_SHOW_THREAD' with '$while(...)'", "[TRACE_OUT_SHOW_THREAD][for]")
{
	using Catch::Matchers::Matches;

	test::stream.str(std::string {});

	$thread(one)

	std::thread {[]()
	{
		$thread(two)
		$while (true)
		{
			break;
		}
	}}.join();

	$while (true)
	{
		break;
	}

	REQUIRE_THAT(test::stream.str(), Matches(
R"(\[Thread\: 0x[0-9a-f]+ two\]~+
while \(true\)
\{
    // while: iteration #1
    
\} // while \(true\)

\[Thread\: 0x[0-9a-f]+ one\]~+
while \(true\)
\{
    // while: iteration #1
    
\} // while \(true\)

)"));
}

