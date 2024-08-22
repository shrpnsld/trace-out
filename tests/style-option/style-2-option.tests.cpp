#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <list>
#include <map>
#include <sstream>
#include <unordered_map>
#include <vector>

using trace_out::RESET_FLAGS;

void subject1();
bool subject2();
int subject3();
char subject4();
std::string subject5();

TEST_CASE("'TRACE_OUT_STYLE=2' with '$t(...)'", "[TRACE_OUT_STYLE][t]")
{
	test::out_stream.str(std::string {});

	SECTION("bool")
	{
		bool subject {true};

		$t(subject);

		const char *expected {"\033[0;36msubject\033[0m = \033[0;34mtrue\033[0m\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("int")
	{
		int subject {456};

		$t(subject);

		const char *expected {"\033[0;36msubject\033[0m = \033[0;35m456\033[0m\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("char")
	{
		auto values = GENERATE(table<char, const char *>({
				{'\x1F', "'\\x1F'"},
				{'\x20', "' '"},
				{'\x7E', "'~'"},
				{'\x7F', "'\\x7F'"},
				{'\x00', "'\\x00'"},
				{'\xFF', "'\\xFF'"}
			}));
		char subject {std::get<0>(values)};

		$t(subject);

		std::stringstream expected;
		expected << "\033[0;36msubject\033[0m = \033[0;32m" << std::get<1>(values) << "\033[0m\n";
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("const char *")
	{
		const char *subject {"hellomoto!"};

		$t(subject);

		const char *expected {"\033[0;36msubject\033[0m = \033[0;33m\"hellomoto!\"\033[0m\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::string")
	{
		std::string subject {"hellomoto!"};

		$t(subject);

		const char *expected {"\033[0;36msubject\033[0m = \033[0;33m\"hellomoto!\"\033[0m\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION(".begin(), .end()")
	{
		SECTION("std::vector empty")
		{
			std::vector<int> subject;

			$t(subject);

			const char *expected {"\033[0;36msubject\033[0m = []\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("std::vector non-empty")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$t(subject);

			const char *expected {"\033[0;36msubject\033[0m = [\033[0;35m1\033[0m, \033[0;35m2\033[0m, \033[0;35m3\033[0m, \033[0;35m4\033[0m, \033[0;35m5\033[0m]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$tbin(...)'", "[TRACE_OUT_STYLE][tbin]")
{
	test::out_stream.str(std::string {});

	SECTION("1-byte")
	{
		$tbin(std::uint8_t {0x0f});
		const char *expected {
			"\033[0;36mstd::uint8_t {0x0f}\033[0m = \033[0;37mbin:\033[0m \033[0;35m00001111\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("2-byte")
	{
		$tbin(std::uint16_t {0x000f});
		const char *expected {
			"\033[0;36mstd::uint16_t {0x000f}\033[0m = \033[0;37mbin:\033[0m \033[0;35m00000000 00001111\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("4-byte")
	{
		$tbin(std::uint32_t {0x0000000f});
		const char *expected {
			"\033[0;36mstd::uint32_t {0x0000000f}\033[0m = \033[0;37mbin:\033[0m \033[0;35m00000000 00000000 00000000 00001111\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("8-byte")
	{
		$tbin(std::uint64_t {0x000000000000000f});
		const char *expected {
			"\033[0;36mstd::uint64_t {0x000000000000000f}\033[0m = \033[0;37mbin:\033[0m \033[0;35m00000000 00000000 00000000 00000000 00000000 00000000 00000000 00001111\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("float")
	{
		$tbin(-456.789f);

		const char *expected {
			"\033[0;36m-456.789f\033[0m = \033[0;37mbin:\033[0m \033[0;35m1  10000111  1100100 01100100 11111110\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("double")
	{
		$tbin(-456.789);

		const char *expected {
			"\033[0;36m-456.789\033[0m = \033[0;37mbin:\033[0m \033[0;35m1  100 00000111  1100 10001100 10011111 10111110 01110110 11001000 10110100\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("long double")
	{
		long double subject {-456.789};
		$tbin(subject);

		const char *expected {
			"\033[0;36msubject\033[0m = \033[0;37mbin:\033[0m \033[0;35m1  1000000 00000111  11100100 01100100 11111101 11110011 10110110 01000101 10100000 00000000\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("multiple subjects")
	{
		std::uint8_t subject1 {0x0f};
		std::uint16_t subject2 {0x00ff};
		std::uint32_t subject3 {0x0000ffff};
		std::uint64_t subject4 {0x00000000ffffffff};
		float subject5 {-456.789f};
		double subject6 {-456.789};
		long double subject7 {-456.789};

		$tbin(subject1, subject2, subject3, subject4, subject5, subject6, subject7);

		const char *expected {
			"\033[0;36msubject1\033[0m = \033[0;37mbin:\033[0m \033[0;35m00001111\033[0m" "\n"
			"\033[0;36msubject2\033[0m = \033[0;37mbin:\033[0m \033[0;35m00000000 11111111\033[0m" "\n"
			"\033[0;36msubject3\033[0m = \033[0;37mbin:\033[0m \033[0;35m00000000 00000000 11111111 11111111\033[0m" "\n"
			"\033[0;36msubject4\033[0m = \033[0;37mbin:\033[0m \033[0;35m00000000 00000000 00000000 00000000 11111111 11111111 11111111 11111111\033[0m" "\n"
			"\033[0;36msubject5\033[0m = \033[0;37mbin:\033[0m \033[0;35m1  10000111  1100100 01100100 11111110" "\033[0m\n"
			"\033[0;36msubject6\033[0m = \033[0;37mbin:\033[0m \033[0;35m1  100 00000111  1100 10001100 10011111 10111110 01110110 11001000 10110100\033[0m" "\n"
			"\033[0;36msubject7\033[0m = \033[0;37mbin:\033[0m \033[0;35m1  1000000 00000111  11100100 01100100 11111101 11110011 10110110 01000101 10100000 00000000\033[0m" "\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$toct(...)'", "[TRACE_OUT_STYLE][toct]")
{
	test::out_stream.str(std::string {});

	SECTION("1-byte")
	{
		$toct(std::uint8_t {0x0f});
		const char *expected {
			"\033[0;36mstd::uint8_t {0x0f}\033[0m = \033[0;37moct:\033[0m \033[0;35m017\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("2-byte")
	{
		$toct(std::uint16_t {0x000f});
		const char *expected {
			"\033[0;36mstd::uint16_t {0x000f}\033[0m = \033[0;37moct:\033[0m \033[0;35m000017\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("4-byte")
	{
		$toct(std::uint32_t {0x0000000f});
		const char *expected {
			"\033[0;36mstd::uint32_t {0x0000000f}\033[0m = \033[0;37moct:\033[0m \033[0;35m000000 000017\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("8-byte")
	{
		$toct(std::uint64_t {0x000000000000000f});
		const char *expected {
			"\033[0;36mstd::uint64_t {0x000000000000000f}\033[0m = \033[0;37moct:\033[0m \033[0;35m000000 000000 000000 000017\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("float")
	{
		$toct(-456.789f);

		const char *expected {
			"\033[0;36m-456.789f\033[0m = \033[0;37moct:\033[0m \033[0;35m303344 144376\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("double")
	{
		$toct(-456.789);

		const char *expected {
			"\033[0;36m-456.789\033[0m = \033[0;37moct:\033[0m \033[0;35m300174 214237 276166 310264\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("long double")
	{
		long double subject {-456.789};
		$toct(subject);

		const char *expected {
			"\033[0;36msubject\033[0m = \033[0;37moct:\033[0m \033[0;35m300007 344144 375363 266105 240000\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("multiple subjects")
	{
		std::uint8_t subject1 {0x0f};
		std::uint16_t subject2 {0x00ff};
		std::uint32_t subject3 {0x0000ffff};
		std::uint64_t subject4 {0x00000000ffffffff};
		float subject5 {-456.789f};
		double subject6 {-456.789};
		long double subject7 {-456.789};

		$toct(subject1, subject2, subject3, subject4, subject5, subject6, subject7);

		const char *expected {
			"\033[0;36msubject1\033[0m = \033[0;37moct:\033[0m \033[0;35m017\033[0m" "\n"
			"\033[0;36msubject2\033[0m = \033[0;37moct:\033[0m \033[0;35m000377\033[0m" "\n"
			"\033[0;36msubject3\033[0m = \033[0;37moct:\033[0m \033[0;35m000000 377377\033[0m" "\n"
			"\033[0;36msubject4\033[0m = \033[0;37moct:\033[0m \033[0;35m000000 000000 377377 377377\033[0m" "\n"
			"\033[0;36msubject5\033[0m = \033[0;37moct:\033[0m \033[0;35m303344 144376" "\033[0m\n"
			"\033[0;36msubject6\033[0m = \033[0;37moct:\033[0m \033[0;35m300174 214237 276166 310264\033[0m" "\n"
			"\033[0;36msubject7\033[0m = \033[0;37moct:\033[0m \033[0;35m300007 344144 375363 266105 240000\033[0m" "\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$thex(...)'", "[TRACE_OUT_STYLE][thex]")
{
	test::out_stream.str(std::string {});

	SECTION("1-byte")
	{
		$thex(std::uint8_t {0x0f});
		const char *expected {
			"\033[0;36mstd::uint8_t {0x0f}\033[0m = \033[0;37mhex:\033[0m \033[0;35m0f\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("2-byte")
	{
		$thex(std::uint16_t {0x000f});
		const char *expected {
			"\033[0;36mstd::uint16_t {0x000f}\033[0m = \033[0;37mhex:\033[0m \033[0;35m000f\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("4-byte")
	{
		$thex(std::uint32_t {0x0000000f});
		const char *expected {
			"\033[0;36mstd::uint32_t {0x0000000f}\033[0m = \033[0;37mhex:\033[0m \033[0;35m0000000f\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("8-byte")
	{
		$thex(std::uint64_t {0x000000000000000f});
		const char *expected {
			"\033[0;36mstd::uint64_t {0x000000000000000f}\033[0m = \033[0;37mhex:\033[0m \033[0;35m00000000 0000000f\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("float")
	{
		$thex(-456.789f);

		const char *expected {
			"\033[0;36m-456.789f\033[0m = \033[0;37mhex:\033[0m \033[0;35mc3e464fe\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("double")
	{
		$thex(-456.789);

		const char *expected {
			"\033[0;36m-456.789\033[0m = \033[0;37mhex:\033[0m \033[0;35mc07c8c9f be76c8b4\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("long double")
	{
		long double subject {-456.789};
		$thex(subject);

		const char *expected {
			"\033[0;36msubject\033[0m = \033[0;37mhex:\033[0m \033[0;35mc007 e464fdf3 b645a000\033[0m" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("multiple subjects")
	{
		std::uint8_t subject1 {0x0f};
		std::uint16_t subject2 {0x00ff};
		std::uint32_t subject3 {0x0000ffff};
		std::uint64_t subject4 {0x00000000ffffffff};
		float subject5 {-456.789f};
		double subject6 {-456.789};
		long double subject7 {-456.789};

		$thex(subject1, subject2, subject3, subject4, subject5, subject6, subject7);

		const char *expected {
			"\033[0;36msubject1\033[0m = \033[0;37mhex:\033[0m \033[0;35m0f\033[0m" "\n"
			"\033[0;36msubject2\033[0m = \033[0;37mhex:\033[0m \033[0;35m00ff\033[0m" "\n"
			"\033[0;36msubject3\033[0m = \033[0;37mhex:\033[0m \033[0;35m0000ffff\033[0m" "\n"
			"\033[0;36msubject4\033[0m = \033[0;37mhex:\033[0m \033[0;35m00000000 ffffffff\033[0m" "\n"
			"\033[0;36msubject5\033[0m = \033[0;37mhex:\033[0m \033[0;35mc3e464fe\033[0m" "\n"
			"\033[0;36msubject6\033[0m = \033[0;37mhex:\033[0m \033[0;35mc07c8c9f be76c8b4\033[0m" "\n"
			"\033[0;36msubject7\033[0m = \033[0;37mhex:\033[0m \033[0;35mc007 e464fdf3 b645a000\033[0m" "\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$tr(...)'", "[TRACE_OUT_STYLE][tr]")
{
	test::out_stream.str(std::string {});

	SECTION("std::vector empty")
	{
		std::vector<int> subject;

		$tr(subject.begin(), subject.end())

		const char *expected {"[\033[0;36msubject.begin()\033[0m, \033[0;36msubject.end()\033[0m) = []\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::vector .begin(), .end()")
	{
		std::vector<int> subject {1, 2, 3, 4, 5};

		$tr(subject.begin(), subject.end())

		const char *expected {"[\033[0;36msubject.begin()\033[0m, \033[0;36msubject.end()\033[0m) = [\033[0;35m1\033[0m, \033[0;35m2\033[0m, \033[0;35m3\033[0m, \033[0;35m4\033[0m, \033[0;35m5\033[0m]\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::vector .begin(), how_much")
	{
		std::vector<int> subject {1, 2, 3, 4, 5};

		$tr(subject.begin(), 5)

		const char *expected {"[\033[0;36msubject.begin()\033[0m: \033[0;36m5\033[0m] = [\033[0;35m1\033[0m, \033[0;35m2\033[0m, \033[0;35m3\033[0m, \033[0;35m4\033[0m, \033[0;35m5\033[0m]\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::vector .begin(), .end(), how_much")
	{
		std::vector<int> subject {1, 2, 3, 4, 5};

		$tr(subject.begin(), subject.end(), 5)

		const char *expected {"[\033[0;36msubject.begin()\033[0m, \033[0;36msubject.end()\033[0m):\033[0;36m5\033[0m = [\033[0;35m1\033[0m, \033[0;35m2\033[0m, \033[0;35m3\033[0m, \033[0;35m4\033[0m, \033[0;35m5\033[0m]\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::map empty")
	{
		std::map<std::string, int> subject {};

		$tr(subject.begin(), subject.end())

		const char *expected {"[\033[0;36msubject.begin()\033[0m, \033[0;36msubject.end()\033[0m) = []" "\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::map non-empty")
	{
		std::map<std::string, int> subject {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}};

		$tr(subject.begin(), subject.end())

		const char *expected {
			"[\033[0;36msubject.begin()\033[0m, \033[0;36msubject.end()\033[0m) = [\n"
			"    {\033[0;33m\"five\"\033[0m, \033[0;35m5\033[0m},\n"
			"    {\033[0;33m\"four\"\033[0m, \033[0;35m4\033[0m},\n"
			"    {\033[0;33m\"one\"\033[0m, \033[0;35m1\033[0m},\n"
			"    {\033[0;33m\"three\"\033[0m, \033[0;35m3\033[0m},\n"
			"    {\033[0;33m\"two\"\033[0m, \033[0;35m2\033[0m}\n"
			"]\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$m(...)'", "[TRACE_OUT_STYLE][m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("32 bytes of 1-byte hexadecimal")
	{
		$m(subject.data(), subject.size(), $hex)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "\033[0;36msubject.data()\033[0m, 32 bytes of 1-byte hexadecimal\n";
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: df 64 6c cf f9 cb ed 11" "  \033[0;37m.\033[0;32mdl\033[0;37m.....\033[0m" "\n"; address += 8;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 4a 83 78 28 3d 48 ad 40" "  \033[0;32mJ\033[0;37m.\033[0;32mx(=H\033[0;37m.\033[0;32m@\033[0m" "\n"; address += 8;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 01 39 4d 9e fd b4 45 a1" "  \033[0;37m.\033[0;32m9M\033[0;37m...\033[0;32mE\033[0;37m.\033[0m" "\n"; address += 8;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 74 68 fc d9 18 cc 3b 32" "  \033[0;32mth\033[0;37m....\033[0;32m;2\033[0m" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("32 bytes of 2-byte hexadecimal")
	{
		$m(subject.data(), subject.size(), $hex, $grp(2))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "\033[0;36msubject.data()\033[0m, 32 bytes of 2-byte hexadecimal\n";
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: df64 6ccf f9cb ed11" "  \033[0;37m.\033[0;32mdl\033[0;37m.....\033[0m" "\n"; address += 8;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 4a83 7828 3d48 ad40" "  \033[0;32mJ\033[0;37m.\033[0;32mx(=H\033[0;37m.\033[0;32m@\033[0m" "\n"; address += 8;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 0139 4d9e fdb4 45a1" "  \033[0;37m.\033[0;32m9M\033[0;37m...\033[0;32mE\033[0;37m.\033[0m" "\n"; address += 8;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 7468 fcd9 18cc 3b32" "  \033[0;32mth\033[0;37m....\033[0;32m;2\033[0m" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("32 bytes of 4-byte hexadecimal")
	{
		$m(subject.data(), subject.size(), $hex, $grp(4))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "\033[0;36msubject.data()\033[0m, 32 bytes of 4-byte hexadecimal\n";
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: df646ccf f9cbed11" "  \033[0;37m.\033[0;32mdl\033[0;37m.....\033[0m" "\n"; address += 8;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 4a837828 3d48ad40" "  \033[0;32mJ\033[0;37m.\033[0;32mx(=H\033[0;37m.\033[0;32m@\033[0m" "\n"; address += 8;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 01394d9e fdb445a1" "  \033[0;37m.\033[0;32m9M\033[0;37m...\033[0;32mE\033[0;37m.\033[0m" "\n"; address += 8;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 7468fcd9 18cc3b32" "  \033[0;32mth\033[0;37m....\033[0;32m;2\033[0m" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("32 bytes of 8-byte hexadecimal")
	{
		$m(subject.data(), subject.size(), $hex, $grp(8))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "\033[0;36msubject.data()\033[0m, 32 bytes of 8-byte hexadecimal\n";
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: df646ccff9cbed11 4a8378283d48ad40" "  \033[0;37m.\033[0;32mdl\033[0;37m.....\033[0;32mJ\033[0;37m.\033[0;32mx(=H\033[0;37m.\033[0;32m@\033[0m" "\n"; address += 16;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 01394d9efdb445a1 7468fcd918cc3b32" "  \033[0;37m.\033[0;32m9M\033[0;37m...\033[0;32mE\033[0;37m.\033[0;32mth\033[0;37m....\033[0;32m;2\033[0m" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("incomplete line")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 7, $hex, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "\033[0;36msubject.data()\033[0m, 14 bytes of 2-byte hexadecimal, big-endian\n";
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: df64 6ccf f9cb ed11" "  \033[0;37m.\033[0;32mdl\033[0;37m.....\033[0m" "\n"; address += type_size * 4;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 4a83 7828 3d48     " "  \033[0;32mJ\033[0;37m.\033[0;32mx(=H\033[0m"   "\n"; address += type_size * 3;
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("incomplete line and leftovers")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 7 + 1, $hex, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "\033[0;36msubject.data()\033[0m, 15 bytes of 2-byte hexadecimal, big-endian\n";
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: df64 6ccf f9cb ed11" "  \033[0;37m.\033[0;32mdl\033[0;37m.....\033[0m" "\n"; address += type_size * 4;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 4a83 7828 3d48     " "  \033[0;32mJ\033[0;37m.\033[0;32mx(=H\033[0m"   "\n"; address += type_size * 3;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: ad                 " "  \033[0;37m.\033[0m" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("complete line and leftovers")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 8 + 1, $hex, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "\033[0;36msubject.data()\033[0m, 17 bytes of 2-byte hexadecimal, big-endian\n";
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: df64 6ccf f9cb ed11" "  \033[0;37m.\033[0;32mdl\033[0;37m.....\033[0m" "\n"; address += type_size * 4;
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 4a83 7828 3d48 ad40" "  \033[0;32mJ\033[0;37m.\033[0;32mx(=H\033[0;37m.\033[0;32m@\033[0m"   "\n"; address += type_size * 4;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    \033[0;35m" << std::hex << address << RESET_FLAGS << "\033[0m: 01                 " "  \033[0;37m.\033[0m" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$f(...)'", "[TRACE_OUT_STYLE][f]")
{
	test::out_stream.str(std::string {});

	subject1();

	const char *expected {
		"void \033[1;36msubject1\033[0m()" "\n"
		"{" "\n"
		"} \033[0;37m// void \033[1;37msubject1\033[0;37m()\033[0m" "\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$return'", "[TRACE_OUT_STYLE][return]")
{
	test::out_stream.str(std::string {});

	SECTION("bool")
	{
		subject2();

		const char *expected {"\033[1;34mreturn\033[0m \033[0;34mtrue\033[0m\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("int")
	{
		subject3();

		const char *expected {"\033[1;34mreturn\033[0m \033[0;35m456\033[0m\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("char")
	{
		subject4();

		const char *expected {"\033[1;34mreturn\033[0m \033[0;32m'f'\033[0m\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::string")
	{
		subject5();

		const char *expected {"\033[1;34mreturn\033[0m \033[0;33m\"hellomoto!\"\033[0m\n"};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$if(...)'", "[TRACE_OUT_STYLE][if]")
{
	test::out_stream.str(std::string {});

	SECTION("true")
	{
		int value {456};

		$if (value == 456) {}

		const char *expected {
			"\033[1;34mif\033[0m (\033[0;36mvalue == 456\033[0m) => \033[0;34mtrue\033[0m\n"
			"{\n"
			"} \033[0;37m// \033[1;37mif\033[0;37m (value == 456) => true\033[0m\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("false")
	{
		int value {789};

		$if (value == 456) {}

		const char *expected {
			"\033[1;34mif\033[0m (\033[0;36mvalue == 456\033[0m) => \033[0;34mfalse\033[0m\n"
			"{\n"
			"} \033[0;37m// \033[1;37mif\033[0;37m (value == 456) => false\033[0m\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$for(...)'", "[TRACE_OUT_STYLE][for]")
{
	test::out_stream.str(std::string {});

	$for (unsigned int i {0}; i < 5; ++i)
	{
	}

	const char *expected {
		"\033[1;34mfor\033[0m (\033[0;36munsigned int i {0}; i < 5; ++i\033[0m)\n"
		"{\n"
		"    \033[0;37m// \033[1;37mfor\033[0;37m: iteration #1\033[0m\n"
		"\n"
		"    \033[0;37m// \033[1;37mfor\033[0;37m: iteration #2\033[0m\n"
		"\n"
		"    \033[0;37m// \033[1;37mfor\033[0;37m: iteration #3\033[0m\n"
		"\n"
		"    \033[0;37m// \033[1;37mfor\033[0;37m: iteration #4\033[0m\n"
		"\n"
		"    \033[0;37m// \033[1;37mfor\033[0;37m: iteration #5\033[0m\n"
		"\n"
		"} \033[0;37m// \033[1;37mfor\033[0;37m (unsigned int i {0}; i < 5; ++i)\033[0m\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$while(...)'", "[TRACE_OUT_STYLE][while]")
{
	test::out_stream.str(std::string {});

	unsigned int i {0};

	$while (i < 5)
	{
		++i;
	}

	const char *expected {
		"\033[1;34mwhile\033[0m (\033[0;36mi < 5\033[0m)\n"
		"{\n"
		"    \033[0;37m// \033[1;37mwhile\033[0;37m: iteration #1\033[0m\n"
		"\n"
		"    \033[0;37m// \033[1;37mwhile\033[0;37m: iteration #2\033[0m\n"
		"\n"
		"    \033[0;37m// \033[1;37mwhile\033[0;37m: iteration #3\033[0m\n"
		"\n"
		"    \033[0;37m// \033[1;37mwhile\033[0;37m: iteration #4\033[0m\n"
		"\n"
		"    \033[0;37m// \033[1;37mwhile\033[0;37m: iteration #5\033[0m\n"
		"\n"
		"} \033[0;37m// \033[1;37mwhile\033[0;37m (i < 5)\033[0m\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);

}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$s(...)'", "[TRACE_OUT_STYLE][m]")
{
	test::out_stream.str(std::string {});

	int value {456};

	$s(value = 789;)

	const char *expected {
		"\033[0;36mvalue = 789;\033[0m \033[0;37m// running...\033[0m\n"
		"\033[0;36mvalue = 789;\033[0m \033[0;37m// done.\033[0m\n"
	};
	REQUIRE(test::out_stream.str() == expected);
	REQUIRE(value == 789);
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$time(...)'", "[TRACE_OUT_STYLE][time]")
{
	test::out_stream.str(std::string {});

	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$time("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(Timing \[0;36m"dummy"\[0m\.\.\.\n)="
		R"=(\[0;36m"dummy"\[0m timed in \[0;35m[0-9]+\[0m ms\n)="
	));
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$clocks(...)'", "[TRACE_OUT_STYLE][clocks]")
{
	test::out_stream.str(std::string {});

	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	$clocks("dummy", dummy();)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(Clocking \[0;36m"dummy"\[0m\.\.\.\n)="
		R"=(\[0;36m"dummy"\[0m clocked in \[0;35m[0-9]+\[0m clocks \(\[0;35m[0-9\.]+\[0m ms\)\n)="
	));
}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$time_stats(...)'", "[TRACE_OUT_STYLE][time_stats]")
{
	test::out_stream.str(std::string {});

	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$time_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(\[0;37m// Execution time statistics \(ms\) for \[0;36m"dummy"\[0;37m:\[0m\n)="
		R"=(\[0;37m//   avg/med: \[0;35m[0-9\.]+\[0;37m / \[0;35m[0-9\.]+\[0m\n)="
		R"=(\[0;37m//     ( mode|modes): \[0;35m[0-9\.]+\[0;37m(, \[0;35m[0-9\.]+\[0;37m)* \((each = \[0;35m[0-9\.]+%\[0;37m, all = )?\[0;35m[0-9\.]+%\[0;37m of all values\)\[0m\n)="
		R"=(\[0;37m//     range: \[0;35m[0-9\.]+\[0;37m \[\[0;35m[0-9\.]+\[0;37m\.\.\.\[0;35m[0-9\.]+\[0;37m\]\[0m\n)="
		R"=(\n)="
	));

}

TEST_CASE("'TRACE_OUT_STYLE=2' with '$clock_stats(...)'", "[TRACE_OUT_STYLE][clock_stats]")
{
	test::out_stream.str(std::string {});

	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	for (std::size_t passes {10}; passes > 0; --passes)
	{
		$clock_stats("dummy", 10, dummy();)
	}

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(\[0;37m// Execution time statistics \(clocks\) for \[0;36m"dummy"\[0;37m:\[0m\n)="
		R"=(\[0;37m//   avg/med: \[0;35m[0-9\.]+\[0;37m / \[0;35m[0-9\.]+\[0m\n)="
		R"=(\[0;37m//     ( mode|modes): \[0;35m[0-9\.]+\[0;37m(, \[0;35m[0-9\.]+\[0;37m)* \((each = \[0;35m[0-9\.]+%\[0;37m, all = )?\[0;35m[0-9\.]+%\[0;37m of all values\)\[0m\n)="
		R"=(\[0;37m//     range: \[0;35m[0-9\.]+\[0;37m \[\[0;35m[0-9\.]+\[0;37m\.\.\.\[0;35m[0-9\.]+\[0;37m\]\[0m\n)="
		R"=(\n)="
	));
}

void subject1()
{$f
}

bool subject2()
{
	$return true;
}

int subject3()
{
	$return 456;
}

char subject4()
{
	$return 'f';
}

std::string subject5()
{
	$return std::string {"hellomoto!"};
}

