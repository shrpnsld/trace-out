#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <string>

TEST_CASE("$tbin(<value>)", "[tbin][tbase]")
{
	test::out_stream.str(std::string {});

	SECTION("1-byte")
	{
		$tbin(std::uint8_t {0x0f});
		$tbin(std::uint8_t {0xf0});

		const char *expected {
			"std::uint8_t {0x0f} = bin: 00001111" "\n"
			"std::uint8_t {0xf0} = bin: 11110000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("2-byte")
	{
		$tbin(std::uint16_t {0x000f});
		$tbin(std::uint16_t {0x00f0});
		$tbin(std::uint16_t {0x0f00});
		$tbin(std::uint16_t {0xf000});

		const char *expected {
			"std::uint16_t {0x000f} = bin: 00000000 00001111" "\n"
			"std::uint16_t {0x00f0} = bin: 00000000 11110000" "\n"
			"std::uint16_t {0x0f00} = bin: 00001111 00000000" "\n"
			"std::uint16_t {0xf000} = bin: 11110000 00000000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("4-byte")
	{
		$tbin(std::uint32_t {0x0000000f});
		$tbin(std::uint32_t {0x000000f0});
		$tbin(std::uint32_t {0x00000f00});
		$tbin(std::uint32_t {0x0000f000});
		$tbin(std::uint32_t {0x000f0000});
		$tbin(std::uint32_t {0x00f00000});
		$tbin(std::uint32_t {0x0f000000});
		$tbin(std::uint32_t {0xf0000000});

		const char *expected {
			"std::uint32_t {0x0000000f} = bin: 00000000 00000000 00000000 00001111" "\n"
			"std::uint32_t {0x000000f0} = bin: 00000000 00000000 00000000 11110000" "\n"
			"std::uint32_t {0x00000f00} = bin: 00000000 00000000 00001111 00000000" "\n"
			"std::uint32_t {0x0000f000} = bin: 00000000 00000000 11110000 00000000" "\n"
			"std::uint32_t {0x000f0000} = bin: 00000000 00001111 00000000 00000000" "\n"
			"std::uint32_t {0x00f00000} = bin: 00000000 11110000 00000000 00000000" "\n"
			"std::uint32_t {0x0f000000} = bin: 00001111 00000000 00000000 00000000" "\n"
			"std::uint32_t {0xf0000000} = bin: 11110000 00000000 00000000 00000000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("8-byte")
	{
		$tbin(std::uint64_t {0x000000000000000f});
		$tbin(std::uint64_t {0x00000000000000f0});
		$tbin(std::uint64_t {0x0000000000000f00});
		$tbin(std::uint64_t {0x000000000000f000});
		$tbin(std::uint64_t {0x00000000000f0000});
		$tbin(std::uint64_t {0x0000000000f00000});
		$tbin(std::uint64_t {0x000000000f000000});
		$tbin(std::uint64_t {0x00000000f0000000});
		$tbin(std::uint64_t {0x0000000f00000000});
		$tbin(std::uint64_t {0x000000f000000000});
		$tbin(std::uint64_t {0x00000f0000000000});
		$tbin(std::uint64_t {0x0000f00000000000});
		$tbin(std::uint64_t {0x000f000000000000});
		$tbin(std::uint64_t {0x00f0000000000000});
		$tbin(std::uint64_t {0x0f00000000000000});
		$tbin(std::uint64_t {0xf000000000000000});

		const char *expected {
			"std::uint64_t {0x000000000000000f} = bin: 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00001111" "\n"
			"std::uint64_t {0x00000000000000f0} = bin: 00000000 00000000 00000000 00000000 00000000 00000000 00000000 11110000" "\n"
			"std::uint64_t {0x0000000000000f00} = bin: 00000000 00000000 00000000 00000000 00000000 00000000 00001111 00000000" "\n"
			"std::uint64_t {0x000000000000f000} = bin: 00000000 00000000 00000000 00000000 00000000 00000000 11110000 00000000" "\n"
			"std::uint64_t {0x00000000000f0000} = bin: 00000000 00000000 00000000 00000000 00000000 00001111 00000000 00000000" "\n"
			"std::uint64_t {0x0000000000f00000} = bin: 00000000 00000000 00000000 00000000 00000000 11110000 00000000 00000000" "\n"
			"std::uint64_t {0x000000000f000000} = bin: 00000000 00000000 00000000 00000000 00001111 00000000 00000000 00000000" "\n"
			"std::uint64_t {0x00000000f0000000} = bin: 00000000 00000000 00000000 00000000 11110000 00000000 00000000 00000000" "\n"
			"std::uint64_t {0x0000000f00000000} = bin: 00000000 00000000 00000000 00001111 00000000 00000000 00000000 00000000" "\n"
			"std::uint64_t {0x000000f000000000} = bin: 00000000 00000000 00000000 11110000 00000000 00000000 00000000 00000000" "\n"
			"std::uint64_t {0x00000f0000000000} = bin: 00000000 00000000 00001111 00000000 00000000 00000000 00000000 00000000" "\n"
			"std::uint64_t {0x0000f00000000000} = bin: 00000000 00000000 11110000 00000000 00000000 00000000 00000000 00000000" "\n"
			"std::uint64_t {0x000f000000000000} = bin: 00000000 00001111 00000000 00000000 00000000 00000000 00000000 00000000" "\n"
			"std::uint64_t {0x00f0000000000000} = bin: 00000000 11110000 00000000 00000000 00000000 00000000 00000000 00000000" "\n"
			"std::uint64_t {0x0f00000000000000} = bin: 00001111 00000000 00000000 00000000 00000000 00000000 00000000 00000000" "\n"
			"std::uint64_t {0xf000000000000000} = bin: 11110000 00000000 00000000 00000000 00000000 00000000 00000000 00000000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("float")
	{
		$tbin(-456.789f);

		const char *expected {
			"-456.789f = bin: 1  10000111  1100100 01100100 11111110" "\n"
		};

		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("double")
	{
		$tbin(-456.789);

		const char *expected {
			"-456.789 = bin: 1  100 00000111  1100 10001100 10011111 10111110 01110110 11001000 10110100" "\n"
		};

		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("long double")
	{
		long double subject {-456.789};
		$tbin(subject);

		const char *expected {
			"subject = bin: 1  1000000 00000111  11100100 01100100 11111101 11110011 10110110 01000101 10100000 00000000" "\n"
		};

		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("$tbin(<values>...)", "[tbin][tbase]")
{
	test::out_stream.str(std::string {});

	std::uint8_t subject1 {0x0f};
	std::uint16_t subject2 {0x00ff};
	std::uint32_t subject3 {0x0000ffff};
	std::uint64_t subject4 {0x00000000ffffffff};
	float subject5 {-456.789f};
	double subject6 {-456.789};
	long double subject7 {-456.789};

	$tbin(subject1, subject2, subject3, subject4, subject5, subject6, subject7);

	const char *expected {
		"subject1 = bin: 00001111" "\n"
		"subject2 = bin: 00000000 11111111" "\n"
		"subject3 = bin: 00000000 00000000 11111111 11111111" "\n"
		"subject4 = bin: 00000000 00000000 00000000 00000000 11111111 11111111 11111111 11111111" "\n"
		"subject5 = bin: 1  10000111  1100100 01100100 11111110" "\n"
		"subject6 = bin: 1  100 00000111  1100 10001100 10011111 10111110 01110110 11001000 10110100" "\n"
		"subject7 = bin: 1  1000000 00000111  11100100 01100100 11111101 11110011 10110110 01000101 10100000 00000000" "\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("$toct(<value>)", "[toct][tbase]")
{
	test::out_stream.str(std::string {});

	SECTION("1-byte")
	{
		$toct(std::uint8_t {0x0f});
		$toct(std::uint8_t {0xf0});

		const char *expected {
			"std::uint8_t {0x0f} = oct: 017" "\n"
			"std::uint8_t {0xf0} = oct: 360" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("2-byte")
	{
		$toct(std::uint16_t {0x000f});
		$toct(std::uint16_t {0x00f0});
		$toct(std::uint16_t {0x0f00});
		$toct(std::uint16_t {0xf000});

		const char *expected {
			"std::uint16_t {0x000f} = oct: 000017" "\n"
			"std::uint16_t {0x00f0} = oct: 000360" "\n"
			"std::uint16_t {0x0f00} = oct: 017000" "\n"
			"std::uint16_t {0xf000} = oct: 360000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("4-byte")
	{
		$toct(std::uint32_t {0x0000000f});
		$toct(std::uint32_t {0x000000f0});
		$toct(std::uint32_t {0x00000f00});
		$toct(std::uint32_t {0x0000f000});
		$toct(std::uint32_t {0x000f0000});
		$toct(std::uint32_t {0x00f00000});
		$toct(std::uint32_t {0x0f000000});
		$toct(std::uint32_t {0xf0000000});

		const char *expected {
			"std::uint32_t {0x0000000f} = oct: 000000 000017" "\n"
			"std::uint32_t {0x000000f0} = oct: 000000 000360" "\n"
			"std::uint32_t {0x00000f00} = oct: 000000 017000" "\n"
			"std::uint32_t {0x0000f000} = oct: 000000 360000" "\n"
			"std::uint32_t {0x000f0000} = oct: 000017 000000" "\n"
			"std::uint32_t {0x00f00000} = oct: 000360 000000" "\n"
			"std::uint32_t {0x0f000000} = oct: 017000 000000" "\n"
			"std::uint32_t {0xf0000000} = oct: 360000 000000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("8-byte")
	{
		$toct(std::uint64_t {0x000000000000000f});
		$toct(std::uint64_t {0x00000000000000f0});
		$toct(std::uint64_t {0x0000000000000f00});
		$toct(std::uint64_t {0x000000000000f000});
		$toct(std::uint64_t {0x00000000000f0000});
		$toct(std::uint64_t {0x0000000000f00000});
		$toct(std::uint64_t {0x000000000f000000});
		$toct(std::uint64_t {0x00000000f0000000});
		$toct(std::uint64_t {0x0000000f00000000});
		$toct(std::uint64_t {0x000000f000000000});
		$toct(std::uint64_t {0x00000f0000000000});
		$toct(std::uint64_t {0x0000f00000000000});
		$toct(std::uint64_t {0x000f000000000000});
		$toct(std::uint64_t {0x00f0000000000000});
		$toct(std::uint64_t {0x0f00000000000000});
		$toct(std::uint64_t {0xf000000000000000});

		const char *expected {
			"std::uint64_t {0x000000000000000f} = oct: 000000 000000 000000 000017" "\n"
			"std::uint64_t {0x00000000000000f0} = oct: 000000 000000 000000 000360" "\n"
			"std::uint64_t {0x0000000000000f00} = oct: 000000 000000 000000 017000" "\n"
			"std::uint64_t {0x000000000000f000} = oct: 000000 000000 000000 360000" "\n"
			"std::uint64_t {0x00000000000f0000} = oct: 000000 000000 000017 000000" "\n"
			"std::uint64_t {0x0000000000f00000} = oct: 000000 000000 000360 000000" "\n"
			"std::uint64_t {0x000000000f000000} = oct: 000000 000000 017000 000000" "\n"
			"std::uint64_t {0x00000000f0000000} = oct: 000000 000000 360000 000000" "\n"
			"std::uint64_t {0x0000000f00000000} = oct: 000000 000017 000000 000000" "\n"
			"std::uint64_t {0x000000f000000000} = oct: 000000 000360 000000 000000" "\n"
			"std::uint64_t {0x00000f0000000000} = oct: 000000 017000 000000 000000" "\n"
			"std::uint64_t {0x0000f00000000000} = oct: 000000 360000 000000 000000" "\n"
			"std::uint64_t {0x000f000000000000} = oct: 000017 000000 000000 000000" "\n"
			"std::uint64_t {0x00f0000000000000} = oct: 000360 000000 000000 000000" "\n"
			"std::uint64_t {0x0f00000000000000} = oct: 017000 000000 000000 000000" "\n"
			"std::uint64_t {0xf000000000000000} = oct: 360000 000000 000000 000000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("float")
	{
		$toct(-456.789f);

		const char *expected {
			"-456.789f = oct: 303344 144376" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("double")
	{
		$toct(-456.789);

		const char *expected {
			"-456.789 = oct: 300174 214237 276166 310264" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("long double")
	{
		long double subject {-456.789};
		$toct(subject);

		const char *expected {
			"subject = oct: 300007 344144 375363 266105 240000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("$toct(<values>...)", "[toct][tbase]")
{
	test::out_stream.str(std::string {});

	std::uint8_t subject1 {0x0f};
	std::uint16_t subject2 {0x00ff};
	std::uint32_t subject3 {0x0000ffff};
	std::uint64_t subject4 {0x00000000ffffffff};
	float subject5 {-456.789f};
	double subject6 {-456.789};
	long double subject7 {-456.789};

	$toct(subject1, subject2, subject3, subject4, subject5, subject6, subject7);

	const char *expected {
		"subject1 = oct: 017" "\n"
		"subject2 = oct: 000377" "\n"
		"subject3 = oct: 000000 377377" "\n"
		"subject4 = oct: 000000 000000 377377 377377" "\n"
		"subject5 = oct: 303344 144376" "\n"
		"subject6 = oct: 300174 214237 276166 310264" "\n"
		"subject7 = oct: 300007 344144 375363 266105 240000" "\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

TEST_CASE("$thex(<value>)", "[thex][tbase]")
{
	test::out_stream.str(std::string {});

	SECTION("1-byte")
	{
		$thex(std::uint8_t {0x0f});
		$thex(std::uint8_t {0xf0});

		const char *expected {
			"std::uint8_t {0x0f} = hex: 0f" "\n"
			"std::uint8_t {0xf0} = hex: f0" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("2-byte")
	{
		$thex(std::uint16_t {0x000f});
		$thex(std::uint16_t {0x00f0});
		$thex(std::uint16_t {0x0f00});
		$thex(std::uint16_t {0xf000});

		const char *expected {
			"std::uint16_t {0x000f} = hex: 000f" "\n"
			"std::uint16_t {0x00f0} = hex: 00f0" "\n"
			"std::uint16_t {0x0f00} = hex: 0f00" "\n"
			"std::uint16_t {0xf000} = hex: f000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("4-byte")
	{
		$thex(std::uint32_t {0x0000000f});
		$thex(std::uint32_t {0x000000f0});
		$thex(std::uint32_t {0x00000f00});
		$thex(std::uint32_t {0x0000f000});
		$thex(std::uint32_t {0x000f0000});
		$thex(std::uint32_t {0x00f00000});
		$thex(std::uint32_t {0x0f000000});
		$thex(std::uint32_t {0xf0000000});

		const char *expected {
			"std::uint32_t {0x0000000f} = hex: 0000000f" "\n"
			"std::uint32_t {0x000000f0} = hex: 000000f0" "\n"
			"std::uint32_t {0x00000f00} = hex: 00000f00" "\n"
			"std::uint32_t {0x0000f000} = hex: 0000f000" "\n"
			"std::uint32_t {0x000f0000} = hex: 000f0000" "\n"
			"std::uint32_t {0x00f00000} = hex: 00f00000" "\n"
			"std::uint32_t {0x0f000000} = hex: 0f000000" "\n"
			"std::uint32_t {0xf0000000} = hex: f0000000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("8-byte")
	{
		$thex(std::uint64_t {0x000000000000000f});
		$thex(std::uint64_t {0x00000000000000f0});
		$thex(std::uint64_t {0x0000000000000f00});
		$thex(std::uint64_t {0x000000000000f000});
		$thex(std::uint64_t {0x00000000000f0000});
		$thex(std::uint64_t {0x0000000000f00000});
		$thex(std::uint64_t {0x000000000f000000});
		$thex(std::uint64_t {0x00000000f0000000});
		$thex(std::uint64_t {0x0000000f00000000});
		$thex(std::uint64_t {0x000000f000000000});
		$thex(std::uint64_t {0x00000f0000000000});
		$thex(std::uint64_t {0x0000f00000000000});
		$thex(std::uint64_t {0x000f000000000000});
		$thex(std::uint64_t {0x00f0000000000000});
		$thex(std::uint64_t {0x0f00000000000000});
		$thex(std::uint64_t {0xf000000000000000});

		const char *expected {
			"std::uint64_t {0x000000000000000f} = hex: 00000000 0000000f" "\n"
			"std::uint64_t {0x00000000000000f0} = hex: 00000000 000000f0" "\n"
			"std::uint64_t {0x0000000000000f00} = hex: 00000000 00000f00" "\n"
			"std::uint64_t {0x000000000000f000} = hex: 00000000 0000f000" "\n"
			"std::uint64_t {0x00000000000f0000} = hex: 00000000 000f0000" "\n"
			"std::uint64_t {0x0000000000f00000} = hex: 00000000 00f00000" "\n"
			"std::uint64_t {0x000000000f000000} = hex: 00000000 0f000000" "\n"
			"std::uint64_t {0x00000000f0000000} = hex: 00000000 f0000000" "\n"
			"std::uint64_t {0x0000000f00000000} = hex: 0000000f 00000000" "\n"
			"std::uint64_t {0x000000f000000000} = hex: 000000f0 00000000" "\n"
			"std::uint64_t {0x00000f0000000000} = hex: 00000f00 00000000" "\n"
			"std::uint64_t {0x0000f00000000000} = hex: 0000f000 00000000" "\n"
			"std::uint64_t {0x000f000000000000} = hex: 000f0000 00000000" "\n"
			"std::uint64_t {0x00f0000000000000} = hex: 00f00000 00000000" "\n"
			"std::uint64_t {0x0f00000000000000} = hex: 0f000000 00000000" "\n"
			"std::uint64_t {0xf000000000000000} = hex: f0000000 00000000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("float")
	{
		$thex(-456.789f);

		const char *expected {
			"-456.789f = hex: c3e464fe" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("double")
	{
		$thex(-456.789);

		const char *expected {
			"-456.789 = hex: c07c8c9f be76c8b4" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("long double")
	{
		long double subject {-456.789};
		$thex(subject);

		const char *expected {
			"subject = hex: c007 e464fdf3 b645a000" "\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("$thex(<values>...)", "[thex][tbase]")
{
	test::out_stream.str(std::string {});

	std::uint8_t subject1 {0x0f};
	std::uint16_t subject2 {0x00ff};
	std::uint32_t subject3 {0x0000ffff};
	std::uint64_t subject4 {0x00000000ffffffff};
	float subject5 {-456.789f};
	double subject6 {-456.789};
	long double subject7 {-456.789};

	$thex(subject1, subject2, subject3, subject4, subject5, subject6, subject7);

	const char *expected {
		"subject1 = hex: 0f" "\n"
		"subject2 = hex: 00ff" "\n"
		"subject3 = hex: 0000ffff" "\n"
		"subject4 = hex: 00000000 ffffffff" "\n"
		"subject5 = hex: c3e464fe" "\n"
		"subject6 = hex: c07c8c9f be76c8b4" "\n"
		"subject7 = hex: c007 e464fdf3 b645a000" "\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

