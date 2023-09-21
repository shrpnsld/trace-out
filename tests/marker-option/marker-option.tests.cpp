#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

char some_func(const char *str, unsigned int length)
{$f
	$w(str)
	$e(str);
	$r(str, str + length)
	$m(str, length)
	$p("wazzzup!")
	$t(char character {str[0]};)

	$if (str[0] == 'h')
	{
	}

	$for ( ; str[0] != '\0'; )
	{
		break;
	}

	$while (str[0] != '\0')
	{
		break;
	}

	$return str[0];
}

TEST_CASE("TRACE_OUT_MARKER", "[TRACE_OUT_MARKER]")
{
	test::stream.str(std::string {});

	char str[11] {"hellomoto!"};
	some_func(str, 11);

	std::stringstream expected;
	expected <<
		"@@ char some_func(const char *, unsigned int)\n"
		"@@ {\n"
		"@@     str = \"hellomoto!\"\n"
		"@@     str = \"hellomoto!\"\n"
		"@@     [str, str + length) = ['h', 'e', 'l', 'l', 'o', 'm', 'o', 't', 'o', '!', '']\n"
		"@@     str, 11 bytes of 1-byte hexadecimal\n"
		"@@         " << static_cast<const void *>(str) << ": 68 65 6c 6c 6f 6d 6f 74\n"
		"@@         " << static_cast<const void *>(str + 8) << ": 6f 21 00\n"
		"@@         \n"
		"@@     // wazzzup!\n"
		"@@     char character {str[0]}; // trace-out: statement passed\n"
		"@@     if (str[0] == 'h') => true\n"
		"@@     {\n"
		"@@     }\n"
		"@@     \n"
		"@@     for (; str[0] != '\\0';)\n"
		"@@     {\n"
		"@@         //\n"
		"@@         // for: iteration #1\n"
		"@@         \n"
		"@@     } // for (; str[0] != '\\0';)\n"
		"@@     \n"
		"@@     while (str[0] != '\\0')\n"
		"@@     {\n"
		"@@         //\n"
		"@@         // while: iteration #1\n"
		"@@         \n"
		"@@     } // while (str[0] != '\\0')\n"
		"@@     \n"
		"@@     return 'h'\n"
		"@@ } // char some_func(const char *, unsigned int)\n"
		"@@ \n";

	REQUIRE(test::stream.str() == expected.str());
}

