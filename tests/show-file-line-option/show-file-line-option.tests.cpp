#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

const long int subject_func11_line {__LINE__ + 2};
void subject_func11()
{$f
}

const long int subject_func12_line {__LINE__ + 3};
int subject_func12()
{
	$return 789;
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$w(...)'", "[TRACE_OUT_SHOW_FILE_LINE][w]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};

	long int line {__LINE__ + 1};
	$w(str)

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "   |  str = \"hellomoto!\"\n";
	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$e(...)'", "[TRACE_OUT_SHOW_FILE_LINE][e]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};

	long int line {__LINE__ + 1};
	$e(str);

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "   |  str = \"hellomoto!\"\n";
	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$r(...)'", "[TRACE_OUT_SHOW_FILE_LINE][r]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};

	long int line {__LINE__ + 1};
	$r(str, str + length)

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "   |  [str, str + length) = ['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!', '']\n";
	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$m(...)'", "[TRACE_OUT_SHOW_FILE_LINE][m]")
{
	test::stream.str(std::string {});

	const char *str {"hellomoto!"};
	std::size_t length {11};

	long int line {__LINE__ + 1};
	$m(str, length)

	std::stringstream expected;
	expected <<
		" show-file-line-opt~:" << line << "   |  str, 11 bytes of 1-byte hexadecimal\n"
		"                          |      " << static_cast<const void *>(str) << ": 68 65 6c 6c 6f 6d 6f 74 6f 21 00\n"
		"                          |      \n";
	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$p(...)'", "[TRACE_OUT_SHOW_FILE_LINE][p]")
{
	test::stream.str(std::string {});

	long int line {__LINE__ + 1};
	$p("wazzzup!")

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "   |  // wazzzup!\n";
	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$t(...)'", "[TRACE_OUT_SHOW_FILE_LINE][t]")
{
	test::stream.str(std::string {});

	long int line {__LINE__ + 1};
	$t(char character {'h'};)

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "   |  char character {'h'}; // trace-out: statement passed\n";
	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$f'", "[TRACE_OUT_SHOW_FILE_LINE][f]")
{
	test::stream.str(std::string {});

	subject_func11();

	std::stringstream expected;
	expected <<
		" show-file-line-opt~:" << subject_func11_line << "    |  void subject_func11()\n"
									"                          |  {\n"
		" show-file-line-opt~:" << subject_func11_line << "    |  } // void subject_func11()\n"
									"                          |  \n";
	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$return'", "[TRACE_OUT_SHOW_FILE_LINE][return]")
{
	test::stream.str(std::string {});

	subject_func12();

	std::stringstream expected;
	expected << " show-file-line-opt~:" << subject_func12_line << "   |  return 789\n";
	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$if(...)'", "[TRACE_OUT_SHOW_FILE_LINE][if]")
{
	test::stream.str(std::string {});

	long int line {__LINE__ + 1};
	$if (true)
	{
	}

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "  |  if (true) => true\n"
		"                          |  {\n"
		"                          |  }\n"
		"                          |  \n";
	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$for(...)'", "[TRACE_OUT_SHOW_FILE_LINE][for]")
{
	test::stream.str(std::string {});

	long int line {__LINE__ + 1};
	$for ( ; true; )
	{
		break;
	}

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "  |  for (; true;)\n"
		"                          |  {\n"
		" show-file-line-opt~:" << line << "  |      // for: iteration #1\n"
		"                          |      \n"
		"                          |  } // for (; true;)\n"
		"                          |  \n";
	REQUIRE(test::stream.str() == expected.str());
}

TEST_CASE("'TRACE_OUT_SHOW_FILE_LINE' with '$while(...)'", "[TRACE_OUT_SHOW_FILE_LINE][while]")
{
	test::stream.str(std::string {});

	long int line {__LINE__ + 1};
	$while (true)
	{
		break;
	}

	std::stringstream expected;
	expected << " show-file-line-opt~:" << line << "  |  while (true)\n"
		"                          |  {\n"
		" show-file-line-opt~:" << line << "  |      // while: iteration #1\n"
		"                          |      \n"
		"                          |  } // while (true)\n"
		"                          |  \n";
	REQUIRE(test::stream.str() == expected.str());
}

