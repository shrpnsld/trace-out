#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <vector>

using trace_out::RESET_FLAGS;

TEST_CASE("$m(<pointer>, <size>)", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40
	};

	SECTION("zero size")
	{
		$m(subject.data(), 0)

		std::stringstream expected;
		expected <<
			"subject.data(), 0 bytes of 1-byte hexadecimal\n"
			"\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("non-zero size")
	{
		$m(subject.data(), subject.size())

		std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};
		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 16 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad 40" "  J.x(=H.@" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $bin, $grp(...), $le|$be)", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("$bin")
	{
		$m(subject.data(), subject.size(), $bin)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 1-byte binary\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11011111 01100100 01101100 11001111" "  .dl." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11111001 11001011 11101101 00010001" "  ...." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01001010 10000011 01111000 00101000" "  J.x(" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00111101 01001000 10101101 01000000" "  =H.@" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00000001 00111001 01001101 10011110" "  .9M." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11111101 10110100 01000101 10100001" "  ..E." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01110100 01101000 11111100 11011001" "  th.." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00011000 11001100 00111011 00110010" "  ..;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$bin, $grp(1), $be")
	{
		$m(subject.data(), subject.size(), $bin, $grp(1), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 1-byte binary\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11011111 01100100 01101100 11001111" "  .dl." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11111001 11001011 11101101 00010001" "  ...." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01001010 10000011 01111000 00101000" "  J.x(" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00111101 01001000 10101101 01000000" "  =H.@" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00000001 00111001 01001101 10011110" "  .9M." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11111101 10110100 01000101 10100001" "  ..E." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01110100 01101000 11111100 11011001" "  th.." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00011000 11001100 00111011 00110010" "  ..;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$bin, $grp(2)")
	{
		$m(subject.data(), subject.size(), $bin, $grp(2))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 2-byte binary\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1101111101100100 0110110011001111" "  .dl." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1111100111001011 1110110100010001" "  ...." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0100101010000011 0111100000101000" "  J.x(" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0011110101001000 1010110101000000" "  =H.@" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0000000100111001 0100110110011110" "  .9M." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1111110110110100 0100010110100001" "  ..E." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0111010001101000 1111110011011001" "  th.." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0001100011001100 0011101100110010" "  ..;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$bin, $grp(2), $le")
	{
		$m(subject.data(), subject.size(), $bin, $grp(2), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 2-byte binary, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0110010011011111 1100111101101100" "  .dl." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1100101111111001 0001000111101101" "  ...." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1000001101001010 0010100001111000" "  J.x(" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0100100000111101 0100000010101101" "  =H.@" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0011100100000001 1001111001001101" "  .9M." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1011010011111101 1010000101000101" "  ..E." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0110100001110100 1101100111111100" "  th.." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1100110000011000 0011001000111011" "  ..;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$bin, $grp(2), $be")
	{
		$m(subject.data(), subject.size(), $bin, $grp(2), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 2-byte binary, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1101111101100100 0110110011001111" "  .dl." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1111100111001011 1110110100010001" "  ...." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0100101010000011 0111100000101000" "  J.x(" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0011110101001000 1010110101000000" "  =H.@" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0000000100111001 0100110110011110" "  .9M." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1111110110110100 0100010110100001" "  ..E." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0111010001101000 1111110011011001" "  th.." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0001100011001100 0011101100110010" "  ..;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$bin, $grp(4)")
	{
		$m(subject.data(), subject.size(), $bin, $grp(4))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 4-byte binary\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11011111011001000110110011001111" "  .dl." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11111001110010111110110100010001" "  ...." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01001010100000110111100000101000" "  J.x(" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00111101010010001010110101000000" "  =H.@" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00000001001110010100110110011110" "  .9M." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11111101101101000100010110100001" "  ..E." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01110100011010001111110011011001" "  th.." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00011000110011000011101100110010" "  ..;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$bin, $grp(4), $le")
	{
		$m(subject.data(), subject.size(), $bin, $grp(4), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 4-byte binary, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11001111011011000110010011011111" "  .dl." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00010001111011011100101111111001" "  ...." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00101000011110001000001101001010" "  J.x(" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01000000101011010100100000111101" "  =H.@" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 10011110010011010011100100000001" "  .9M." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 10100001010001011011010011111101" "  ..E." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11011001111111000110100001110100" "  th.." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00110010001110111100110000011000" "  ..;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$bin, $grp(4), $be")
	{
		$m(subject.data(), subject.size(), $bin, $grp(4), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 4-byte binary, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11011111011001000110110011001111" "  .dl." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11111001110010111110110100010001" "  ...." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01001010100000110111100000101000" "  J.x(" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00111101010010001010110101000000" "  =H.@" "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00000001001110010100110110011110" "  .9M." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11111101101101000100010110100001" "  ..E." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01110100011010001111110011011001" "  th.." "\n"; address += 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 00011000110011000011101100110010" "  ..;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$bin, $grp(8)")
	{
		$m(subject.data(), subject.size(), $bin, $grp(8))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 8-byte binary\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1101111101100100011011001100111111111001110010111110110100010001" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0100101010000011011110000010100000111101010010001010110101000000" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0000000100111001010011011001111011111101101101000100010110100001" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0111010001101000111111001101100100011000110011000011101100110010" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$bin, $grp(8), $le")
	{
		$m(subject.data(), subject.size(), $bin, $grp(8), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 8-byte binary, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0001000111101101110010111111100111001111011011000110010011011111" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0100000010101101010010000011110100101000011110001000001101001010" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1010000101000101101101001111110110011110010011010011100100000001" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0011001000111011110011000001100011011001111111000110100001110100" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$bin, $grp(8), $be")
	{
		$m(subject.data(), subject.size(), $bin, $grp(8), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 8-byte binary, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1101111101100100011011001100111111111001110010111110110100010001" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0100101010000011011110000010100000111101010010001010110101000000" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0000000100111001010011011001111011111101101101000100010110100001" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0111010001101000111111001101100100011000110011000011101100110010" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $hex, $grp(...), $le|$be)", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("$hex")
	{
		$m(subject.data(), subject.size(), $hex)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad 40" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39 4d 9e fd b4 45 a1" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 74 68 fc d9 18 cc 3b 32" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$hex, $grp(1)")
	{
		$m(subject.data(), subject.size(), $hex, $grp(1))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad 40" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39 4d 9e fd b4 45 a1" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 74 68 fc d9 18 cc 3b 32" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$hex, $grp(2)")
	{
		$m(subject.data(), subject.size(), $hex, $grp(2))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 2-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df64 6ccf f9cb ed11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a83 7828 3d48 ad40" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0139 4d9e fdb4 45a1" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 7468 fcd9 18cc 3b32" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$hex, $grp(2), $le")
	{
		$m(subject.data(), subject.size(), $hex, $grp(2), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 2-byte hexadecimal, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 64df cf6c cbf9 11ed" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 834a 2878 483d 40ad" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3901 9e4d b4fd a145" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 6874 d9fc cc18 323b" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$hex, $grp(2), $be")
	{
		$m(subject.data(), subject.size(), $hex, $grp(2), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 2-byte hexadecimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df64 6ccf f9cb ed11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a83 7828 3d48 ad40" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0139 4d9e fdb4 45a1" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 7468 fcd9 18cc 3b32" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$hex, $grp(4)")
	{
		$m(subject.data(), subject.size(), $hex, $grp(4))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 4-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df646ccf f9cbed11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a837828 3d48ad40" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01394d9e fdb445a1" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 7468fcd9 18cc3b32" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$hex, $grp(4), $le")
	{
		$m(subject.data(), subject.size(), $hex, $grp(4), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 4-byte hexadecimal, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": cf6c64df 11edcbf9" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2878834a 40ad483d" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 9e4d3901 a145b4fd" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": d9fc6874 323bcc18" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$hex, $grp(4), $be")
	{
		$m(subject.data(), subject.size(), $hex, $grp(4), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 4-byte hexadecimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df646ccf f9cbed11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a837828 3d48ad40" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01394d9e fdb445a1" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 7468fcd9 18cc3b32" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$hex, $grp(8)")
	{
		$m(subject.data(), subject.size(), $hex, $grp(8))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 8-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df646ccff9cbed11 4a8378283d48ad40" "  .dl.....J.x(=H.@" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01394d9efdb445a1 7468fcd918cc3b32" "  .9M...E.th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$hex, $grp(8), $le")
	{
		$m(subject.data(), subject.size(), $hex, $grp(8), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 8-byte hexadecimal, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11edcbf9cf6c64df 40ad483d2878834a" "  .dl.....J.x(=H.@" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": a145b4fd9e4d3901 323bcc18d9fc6874" "  .9M...E.th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$hex, $grp(8), $be")
	{
		$m(subject.data(), subject.size(), $hex, $grp(8), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 8-byte hexadecimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df646ccff9cbed11 4a8378283d48ad40" "  .dl.....J.x(=H.@" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01394d9efdb445a1 7468fcd918cc3b32" "  .9M...E.th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $sdec, $grp(...), $le|$be)", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("$sdec")
	{
		$m(subject.data(), subject.size(), $sdec)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":  -33  100  108  -49   -7  -53  -19   17" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   74 -125  120   40   61   72  -83   64" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    1   57   77  -98   -3  -76   69  -95" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  116  104   -4  -39   24  -52   59   50" "  th....;2" "\n";
		}
		else if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":  -33  100  108  -49   -7  -53  -19   17" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   74 -125  120   40   61   72  -83   64" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    1   57   77  -98   -3  -76   69  -95" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  116  104   -4  -39   24  -52   59   50" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $le")
	{
		$m(subject.data(), subject.size(), $sdec, $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  -33  100  108  -49   -7  -53  -19   17" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   74 -125  120   40   61   72  -83   64" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    1   57   77  -98   -3  -76   69  -95" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  116  104   -4  -39   24  -52   59   50" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $be")
	{
		$m(subject.data(), subject.size(), $sdec, $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  -33  100  108  -49   -7  -53  -19   17" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   74 -125  120   40   61   72  -83   64" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    1   57   77  -98   -3  -76   69  -95" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  116  104   -4  -39   24  -52   59   50" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(1)")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(1))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":  -33  100  108  -49   -7  -53  -19   17" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   74 -125  120   40   61   72  -83   64" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    1   57   77  -98   -3  -76   69  -95" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  116  104   -4  -39   24  -52   59   50" "  th....;2" "\n";
		}
		else if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":  -33  100  108  -49   -7  -53  -19   17" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   74 -125  120   40   61   72  -83   64" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    1   57   77  -98   -3  -76   69  -95" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  116  104   -4  -39   24  -52   59   50" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(1), $le")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(1), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  -33  100  108  -49   -7  -53  -19   17" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   74 -125  120   40   61   72  -83   64" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    1   57   77  -98   -3  -76   69  -95" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  116  104   -4  -39   24  -52   59   50" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(1), $be")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(1), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  -33  100  108  -49   -7  -53  -19   17" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   74 -125  120   40   61   72  -83   64" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    1   57   77  -98   -3  -76   69  -95" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  116  104   -4  -39   24  -52   59   50" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(2)")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(2))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of 2-byte signed decimal, little-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":  -8348  27855  -1589  -4847" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  19075  30760  15688 -21184" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    313  19870   -588  17825" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  29800   -807   6348  15154" "  th....;2" "\n";
		}
		else if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of 2-byte signed decimal, big-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":  25823 -12436 -13319   4589" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": -31926  10360  18493  16557" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  14593 -25011 -19203 -24251" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  26740  -9732 -13288  12859" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(2), $le")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(2), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 2-byte signed decimal, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  -8348  27855  -1589  -4847" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  19075  30760  15688 -21184" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    313  19870   -588  17825" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  29800   -807   6348  15154" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(2), $be")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(2), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 2-byte signed decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  25823 -12436 -13319   4589" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": -31926  10360  18493  16557" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  14593 -25011 -19203 -24251" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  26740  -9732 -13288  12859" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(4)")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(4))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of 4-byte signed decimal, little-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":  -547066673  -104076015" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  1250129960  1028173120" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    20532638   -38517343" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  1953037529   416037682" "  th....;2" "\n";
		}
		else if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of 4-byte signed decimal, big-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":  -814979873   300796921" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   678986570  1085098045" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": -1639106303 -1589267203" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  -637769612   842779672" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(4), $le")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(4), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 4-byte signed decimal, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  -547066673  -104076015" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1250129960  1028173120" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    20532638   -38517343" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1953037529   416037682" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(4), $be")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(4), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 4-byte signed decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  -814979873   300796921" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   678986570  1085098045" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": -1639106303 -1589267203" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  -637769612   842779672" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(8)")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(8))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of 8-byte signed decimal, little-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":  -2349633465075634927" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   5369267294977961280" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":     88187012967056801" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   8388232315331689266" "  th....;2" "\n";
		}
		else if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of 8-byte signed decimal, big-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":   1291912941912483039" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   4660460616907522890" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  -6825850658834532095" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   3619711132630804596" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(8), $le")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(8), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 8-byte signed decimal, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  -2349633465075634927" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   5369267294977961280" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":     88187012967056801" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   8388232315331689266" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$sdec, $grp(8), $be")
	{
		$m(subject.data(), subject.size(), $sdec, $grp(8), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 8-byte signed decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":   1291912941912483039" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   4660460616907522890" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  -6825850658834532095" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   3619711132630804596" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $udec, $grp(...), $le|$be)", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("$udec")
	{
		$m(subject.data(), subject.size(), $udec)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ": 223 100 108 207 249 203 237  17" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  74 131 120  40  61  72 173  64" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   1  57  77 158 253 180  69 161" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 116 104 252 217  24 204  59  50" "  th....;2" "\n";
		}
		else if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ": 223 100 108 207 249 203 237  17" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  74 131 120  40  61  72 173  64" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   1  57  77 158 253 180  69 161" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 116 104 252 217  24 204  59  50" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $le")
	{
		$m(subject.data(), subject.size(), $udec, $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 223 100 108 207 249 203 237  17" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  74 131 120  40  61  72 173  64" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   1  57  77 158 253 180  69 161" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 116 104 252 217  24 204  59  50" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $be")
	{
		$m(subject.data(), subject.size(), $udec, $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 223 100 108 207 249 203 237  17" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  74 131 120  40  61  72 173  64" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   1  57  77 158 253 180  69 161" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 116 104 252 217  24 204  59  50" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(1)")
	{
		$m(subject.data(), subject.size(), $udec, $grp(1))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ": 223 100 108 207 249 203 237  17" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  74 131 120  40  61  72 173  64" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   1  57  77 158 253 180  69 161" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 116 104 252 217  24 204  59  50" "  th....;2" "\n";
		}
		else if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ": 223 100 108 207 249 203 237  17" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  74 131 120  40  61  72 173  64" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   1  57  77 158 253 180  69 161" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 116 104 252 217  24 204  59  50" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(1), $le")
	{
		$m(subject.data(), subject.size(), $udec, $grp(1), $le)

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
		expected.unsetf(std::ios::basefield);
		expected << "    " << std::hex << address << RESET_FLAGS << ": 223 100 108 207 249 203 237  17" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  74 131 120  40  61  72 173  64" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   1  57  77 158 253 180  69 161" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 116 104 252 217  24 204  59  50" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(1), $be")
	{
		$m(subject.data(), subject.size(), $udec, $grp(1), $be)

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
		expected.unsetf(std::ios::basefield);
		expected << "    " << std::hex << address << RESET_FLAGS << ": 223 100 108 207 249 203 237  17" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  74 131 120  40  61  72 173  64" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   1  57  77 158 253 180  69 161" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 116 104 252 217  24 204  59  50" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(2)")
	{
		$m(subject.data(), subject.size(), $udec, $grp(2))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of 2-byte unsigned decimal, little-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ": 57188 27855 63947 60689" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 19075 30760 15688 44352" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   313 19870 64948 17825" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 29800 64729  6348 15154" "  th....;2" "\n";
		}
		else if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of 2-byte unsigned decimal, big-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ": 25823 53100 52217  4589" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 33610 10360 18493 16557" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 14593 40525 46333 41285" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 26740 55804 52248 12859" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(2), $le")
	{
		$m(subject.data(), subject.size(), $udec, $grp(2), $le)

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 2-byte unsigned decimal, little-endian\n";
		expected.unsetf(std::ios::basefield);
		expected << "    " << std::hex << address << RESET_FLAGS << ": 57188 27855 63947 60689" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 19075 30760 15688 44352" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   313 19870 64948 17825" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 29800 64729  6348 15154" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(2), $be")
	{
		$m(subject.data(), subject.size(), $udec, $grp(2), $be)

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 2-byte unsigned decimal, big-endian\n";
		expected.unsetf(std::ios::basefield);
		expected << "    " << std::hex << address << RESET_FLAGS << ": 25823 53100 52217  4589" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 33610 10360 18493 16557" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 14593 40525 46333 41285" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 26740 55804 52248 12859" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(4)")
	{
		$m(subject.data(), subject.size(), $udec, $grp(4))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of 4-byte unsigned decimal, little-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ": 3747900623 4190891281" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 1250129960 1028173120" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   20532638 4256449953" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 1953037529  416037682" "  th....;2" "\n";
		}
		else if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of 4-byte unsigned decimal, big-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 2655860993 2705700093" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 3657197684  842779672" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(4), $le")
	{
		$m(subject.data(), subject.size(), $udec, $grp(4), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 4-byte unsigned decimal, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3747900623 4190891281" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1250129960 1028173120" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   20532638 4256449953" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1953037529  416037682" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(4), $be")
	{
		$m(subject.data(), subject.size(), $udec, $grp(4), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2655860993 2705700093" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3657197684  842779672" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(8)")
	{
		$m(subject.data(), subject.size(), $udec, $grp(8))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of 8-byte unsigned decimal, little-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ": 16097110608633916689" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  5369267294977961280" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    88187012967056801" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  8388232315331689266" "  th....;2" "\n";
		}
		else if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of 8-byte unsigned decimal, big-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ": 11620893414875019521" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":  3619711132630804596" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(8), $le")
	{
		$m(subject.data(), subject.size(), $udec, $grp(8), $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 8-byte unsigned decimal, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 16097110608633916689" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  5369267294977961280" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    88187012967056801" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  8388232315331689266" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$udec, $grp(8), $be")
	{
		$m(subject.data(), subject.size(), $udec, $grp(8), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11620893414875019521" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  3619711132630804596" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $flt, $le|$be)", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("$flt")
	{
		$m(subject.data(), subject.size(), $flt)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of " << sizeof(float) << "-byte float, little-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":   -1.64598e+19   -1.32356e+35" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    4.30799e+06      0.0489933" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    3.40348e-38   -2.99528e+37" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    7.38367e+31    5.27925e-24" "  th....;2" "\n";
		}
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of " << sizeof(float) << "-byte float, big-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":   -3.96603e+09    3.75177e-28" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    1.37952e-14        5.41507" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   -1.08644e-20   -6.69857e-19" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   -8.88082e+15    1.09312e-08" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$flt, $le")
	{
		$m(subject.data(), subject.size(), $flt, $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of " << sizeof(float) << "-byte float, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":   -1.64598e+19   -1.32356e+35" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    4.30799e+06      0.0489933" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    3.40348e-38   -2.99528e+37" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    7.38367e+31    5.27925e-24" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$flt, $be")
	{
		$m(subject.data(), subject.size(), $flt, $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of " << sizeof(float) << "-byte float, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":   -3.96603e+09    3.75177e-28" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    1.37952e-14        5.41507" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   -1.08644e-20   -6.69857e-19" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   -8.88082e+15    1.09312e-08" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $dbl, $le|$be)", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("$dbl")
	{
		$m(subject.data(), subject.size(), $dbl)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
		{
			expected << "subject.data(), 32 bytes of " << sizeof(double) << "-byte double, little-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":   -3.34295808947304e+151" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":     9.10544235845569e+50" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    9.22443858116523e-303" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":    5.72495988265533e+252" "  th....;2" "\n";
		}
		if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
		{
			expected << "subject.data(), 32 bytes of " << sizeof(double) << "-byte double, big-endian\n";
			expected << "    " << std::hex << address << RESET_FLAGS << ":    2.57598040706935e-222" "  .dl....." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":         3748.11944939234" "  J.x(=H.@" "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":   -2.12203161888808e-148" "  .9M...E." "\n"; address += 8;
			expected << "    " << std::hex << address << RESET_FLAGS << ":     1.03105746265379e-66" "  th....;2" "\n";
		}

		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$dbl, $le")
	{
		$m(subject.data(), subject.size(), $dbl, $le)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of " << sizeof(double) << "-byte double, little-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":   -3.34295808947304e+151" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":     9.10544235845569e+50" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    9.22443858116523e-303" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":    5.72495988265533e+252" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("$dbl, $be")
	{
		$m(subject.data(), subject.size(), $dbl, $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 32 bytes of " << sizeof(double) << "-byte double, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":    2.57598040706935e-222" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":         3748.11944939234" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":   -2.12203161888808e-148" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ":     1.03105746265379e-66" "  th....;2" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $ldbl, $le|$be)", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};
	std::size_t sizeof_long_double = {trace_out::number_format<long double>::size()};

	switch (sizeof_long_double)
	{
		case 8:
		{
			SECTION("$ldbl, 64-bit")
			{
				$m(subject.data(), 32, $ldbl)

				std::stringstream expected;
				expected.unsetf(std::ios::basefield);
				if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
				{
					expected << "subject.data(), 32 bytes of " << sizeof_long_double << "-byte double, little-endian\n";
					expected << "    " << std::hex << address << RESET_FLAGS << ":   -3.34295808947304e+151" "  .dl....." "\n"; address += sizeof_long_double;
					expected << "    " << std::hex << address << RESET_FLAGS << ":     9.10544235845569e+50" "  J.x(=H.@" "\n"; address += sizeof_long_double;
					expected << "    " << std::hex << address << RESET_FLAGS << ":    9.22443858116523e-303" "  .9M...E." "\n"; address += sizeof_long_double;
					expected << "    " << std::hex << address << RESET_FLAGS << ":    5.72495988265533e+252" "  th....;2" "\n";
				}
				if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
				{
					expected << "subject.data(), 32 bytes of " << sizeof_long_double << "-byte double, big-endian\n";
					expected << "    " << std::hex << address << RESET_FLAGS << ":    2.57598040706935e-222" "  .dl....." "\n"; address += sizeof_long_double;
					expected << "    " << std::hex << address << RESET_FLAGS << ":         3748.11944939234" "  J.x(=H.@" "\n"; address += sizeof_long_double;
					expected << "    " << std::hex << address << RESET_FLAGS << ":   -2.12203161888808e-148" "  .9M...E." "\n"; address += sizeof_long_double;
					expected << "    " << std::hex << address << RESET_FLAGS << ":     1.03105746265379e-66" "  th....;2" "\n";
				}

				expected << "\n";

				REQUIRE(test::out_stream.str() == expected.str());
			}

			SECTION("$ldbl, 64-bit, $le")
			{
				$m(subject.data(), 32, $ldbl, $le)

				std::stringstream expected;
				expected.unsetf(std::ios::basefield);
				expected << "subject.data(), 32 bytes of " << sizeof_long_double << "-byte double, little-endian\n";
				expected << "    " << std::hex << address << RESET_FLAGS << ":   -3.34295808947304e+151" "  .dl....." "\n"; address += sizeof_long_double;
				expected << "    " << std::hex << address << RESET_FLAGS << ":     9.10544235845569e+50" "  J.x(=H.@" "\n"; address += sizeof_long_double;
				expected << "    " << std::hex << address << RESET_FLAGS << ":    9.22443858116523e-303" "  .9M...E." "\n"; address += sizeof_long_double;
				expected << "    " << std::hex << address << RESET_FLAGS << ":    5.72495988265533e+252" "  th....;2" "\n";
				expected << "\n";

				REQUIRE(test::out_stream.str() == expected.str());
			}

			SECTION("$ldbl, 64-bit, $be")
			{
				$m(subject.data(), 32, $ldbl, $be)

				std::stringstream expected;
				expected.unsetf(std::ios::basefield);
				expected << "subject.data(), 32 bytes of " << sizeof_long_double << "-byte double, big-endian\n";
				expected << "    " << std::hex << address << RESET_FLAGS << ":    2.57598040706935e-222" "  .dl....." "\n"; address += sizeof_long_double;
				expected << "    " << std::hex << address << RESET_FLAGS << ":         3748.11944939234" "  J.x(=H.@" "\n"; address += sizeof_long_double;
				expected << "    " << std::hex << address << RESET_FLAGS << ":   -2.12203161888808e-148" "  .9M...E." "\n"; address += sizeof_long_double;
				expected << "    " << std::hex << address << RESET_FLAGS << ":     1.03105746265379e-66" "  th....;2" "\n";
				expected << "\n";

				REQUIRE(test::out_stream.str() == expected.str());
			}

			break;
		}

		case 10:
		{
			SECTION("$ldbl, 80-bit")
			{
				$m(subject.data(), 20, $ldbl)

				std::stringstream expected;
				expected.unsetf(std::ios::basefield);
				if (trace_out::byte_order_t::current() == trace_out::byte_order_t::LITTLE)
				{
					expected << "subject.data(), 20 bytes of " << sizeof_long_double << "-byte long double, little-endian\n";
					expected << "    " << std::hex << address << RESET_FLAGS << ":    -2.0302222937866432e+2419" "  .dl.....J." "\n"; address += sizeof_long_double;
					expected << "    " << std::hex << address << RESET_FLAGS << ":    3.87600243484983522e+4327" "  x(=H.@.9M." "\n";
				}
				if (trace_out::byte_order_t::current() == trace_out::byte_order_t::BIG)
				{
					expected << "subject.data(), 20 bytes of " << sizeof_long_double << "-byte long double, big-endian\n";
					expected << "    " << std::hex << address << RESET_FLAGS << ":   -6.90527387463601281e-4680" "  .dl.....J." "\n"; address += sizeof_long_double;
					expected << "    " << std::hex << address << RESET_FLAGS << ":   -9.20363885204217373e-2598" "  x(=H.@.9M." "\n";
				}

				expected << "\n";

				REQUIRE(test::out_stream.str() == expected.str());
			}

			SECTION("$ldbl, 80-bit, $le")
			{
				$m(subject.data(), 20, $ldbl, $le)

				std::stringstream expected;
				expected.unsetf(std::ios::basefield);
				expected << "subject.data(), 20 bytes of " << sizeof_long_double << "-byte long double, little-endian\n";
				expected << "    " << std::hex << address << RESET_FLAGS << ":    -2.0302222937866432e+2419" "  .dl.....J." "\n"; address += sizeof_long_double;
				expected << "    " << std::hex << address << RESET_FLAGS << ":    3.87600243484983522e+4327" "  x(=H.@.9M." "\n";
				expected << "\n";

				REQUIRE(test::out_stream.str() == expected.str());
			}

			SECTION("$ldbl, 80-bit, $be")
			{
				$m(subject.data(), 20, $ldbl, $be)

				std::stringstream expected;
				expected.unsetf(std::ios::basefield);
				expected << "subject.data(), 20 bytes of " << sizeof_long_double << "-byte long double, big-endian\n";
				expected << "    " << std::hex << address << RESET_FLAGS << ":   -6.90527387463601281e-4680" "  .dl.....J." "\n"; address += sizeof_long_double;
				expected << "    " << std::hex << address << RESET_FLAGS << ":   -9.20363885204217373e-2598" "  x(=H.@.9M." "\n";
				expected << "\n";

				REQUIRE(test::out_stream.str() == expected.str());
			}

			break;
		}

		case 16:
		{
			// TODO: do

			SECTION("$ldbl, 128-bit")
			{
			}

			SECTION("$ldbl, 128-bit, $le")
			{
			}

			SECTION("$ldbl, 128-bit, $be")
			{
			}

			break;
		}
	}
}

TEST_CASE("$m(...) incomplete last line", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32,
		0x03, 0xb1, 0x74, 0xb0, 0xd1, 0x46, 0x40, 0xc5, 0x10, 0x2b, 0xb1, 0x80, 0x37, 0x49, 0x14, 0x63,
		0x22, 0xc7, 0xe1, 0x91, 0x12, 0xad, 0x2b, 0x1f, 0x07, 0x77, 0xe0, 0xfc, 0x99, 0xdd, 0x4f, 0xb1,
		0x09, 0x5d, 0xb4, 0x4d, 0xf1, 0x53, 0xc5, 0x28, 0x0f, 0xe0, 0x10, 0x32, 0x4c, 0xa5, 0x16, 0x7c,
		0x78, 0x4f, 0x5f, 0xda, 0x80, 0x4b, 0x92, 0xd9, 0x73, 0xe8, 0x73, 0xa4, 0xc3, 0x1a, 0xbc, 0xd3,
		0x54, 0xb1, 0x78, 0x26, 0xfd, 0x7c, 0x3c, 0xb9, 0xc7, 0x84, 0x95, 0xdf, 0xe3, 0xa5, 0x90, 0xd2,
		0xc4, 0x69, 0x33, 0x6f, 0x1c, 0xfa, 0x68, 0xf5, 0x47, 0x65, 0x84, 0x74, 0x66, 0x28, 0x53, 0x10,
		0xd3, 0xc6, 0x27, 0x83, 0xef, 0x72, 0x4e, 0x8e, 0xd5, 0x3f, 0x6f, 0xbf, 0x3c, 0x25, 0x5a, 0xee,
		0x53, 0x31, 0xd6, 0x0a, 0xa6, 0x90, 0xd8, 0x32, 0x0e, 0xde, 0x72, 0x71, 0x6e, 0xa9, 0x84, 0xf0,
		0xff, 0x32, 0x59, 0x58, 0xf5, 0xeb, 0xf8, 0x77, 0x9d, 0x27, 0x02, 0x16, 0xf2, 0x10, 0xf8, 0xba,
		0xcd, 0xf4, 0x02, 0x47, 0xf1, 0x37, 0x61, 0x93, 0x16, 0x98, 0x4f, 0x02, 0xaa, 0x17, 0x96, 0x7c,
		0x36, 0x58, 0xe7, 0xb6, 0xa0, 0x5c, 0xe5, 0x61, 0xbe, 0x45, 0xec, 0x16, 0xaf, 0xb5, 0xe3, 0x14,
		0x8f, 0xd3, 0x9a, 0x8d, 0x2c, 0x4f, 0xc3, 0x32, 0xd2, 0x4a, 0x03, 0x8b, 0x11, 0x74, 0x83, 0x55,
		0xc3, 0xbc, 0x77, 0x85, 0xc2, 0xc6, 0x6d, 0x38, 0x36, 0x18, 0xd4, 0xd4, 0xe6, 0xd6, 0x49, 0x18,
		0x76, 0x12, 0xe1, 0xd3, 0x89, 0x52, 0xea, 0x31, 0x0d, 0xf6, 0xf5, 0x81, 0xfb, 0xa3, 0xb2, 0x15
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("1 line, 1 item")
	{
		$m(subject.data(), 1, $hex)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 1 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df                     " "  ." "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 2 items")
	{
		$m(subject.data(), 2, $hex)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 2 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64                  " "  .d" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, incomplete by 1 item")
	{
		$m(subject.data(), 15, $hex)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 15 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad   " "  J.x(=H."  "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 1 item on the last line")
	{
		$m(subject.data(), 16 + 1, $hex)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 17 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad 40" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01                     " "  ."        "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 2 items on the last line")
	{
		$m(subject.data(), 16 + 2, $hex)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 18 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad 40" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39                  " "  .9"       "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, the last line is incomplete by 1 item")
	{
		$m(subject.data(), 16 + 15, $hex)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 31 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" "  .dl....." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad 40" "  J.x(=H.@" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39 4d 9e fd b4 45 a1" "  .9M...E." "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 74 68 fc d9 18 cc 3b   " "  th....;"  "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $bin/$hex(<grouping>), $col(<columns>))", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32,
		0x03, 0xb1, 0x74, 0xb0, 0xd1, 0x46, 0x40, 0xc5, 0x10, 0x2b, 0xb1, 0x80, 0x37, 0x49, 0x14, 0x63,
		0x22, 0xc7, 0xe1, 0x91, 0x12, 0xad, 0x2b, 0x1f, 0x07, 0x77, 0xe0, 0xfc, 0x99, 0xdd, 0x4f, 0xb1,
		0x09, 0x5d, 0xb4, 0x4d, 0xf1, 0x53, 0xc5, 0x28, 0x0f, 0xe0, 0x10, 0x32, 0x4c, 0xa5, 0x16, 0x7c,
		0x78, 0x4f, 0x5f, 0xda, 0x80, 0x4b, 0x92, 0xd9, 0x73, 0xe8, 0x73, 0xa4, 0xc3, 0x1a, 0xbc, 0xd3,
		0x54, 0xb1, 0x78, 0x26, 0xfd, 0x7c, 0x3c, 0xb9, 0xc7, 0x84, 0x95, 0xdf, 0xe3, 0xa5, 0x90, 0xd2,
		0xc4, 0x69, 0x33, 0x6f, 0x1c, 0xfa, 0x68, 0xf5, 0x47, 0x65, 0x84, 0x74, 0x66, 0x28, 0x53, 0x10,
		0xd3, 0xc6, 0x27, 0x83, 0xef, 0x72, 0x4e, 0x8e, 0xd5, 0x3f, 0x6f, 0xbf, 0x3c, 0x25, 0x5a, 0xee,
		0x53, 0x31, 0xd6, 0x0a, 0xa6, 0x90, 0xd8, 0x32, 0x0e, 0xde, 0x72, 0x71, 0x6e, 0xa9, 0x84, 0xf0,
		0xff, 0x32, 0x59, 0x58, 0xf5, 0xeb, 0xf8, 0x77, 0x9d, 0x27, 0x02, 0x16, 0xf2, 0x10, 0xf8, 0xba,
		0xcd, 0xf4, 0x02, 0x47, 0xf1, 0x37, 0x61, 0x93, 0x16, 0x98, 0x4f, 0x02, 0xaa, 0x17, 0x96, 0x7c,
		0x36, 0x58, 0xe7, 0xb6, 0xa0, 0x5c, 0xe5, 0x61, 0xbe, 0x45, 0xec, 0x16, 0xaf, 0xb5, 0xe3, 0x14,
		0x8f, 0xd3, 0x9a, 0x8d, 0x2c, 0x4f, 0xc3, 0x32, 0xd2, 0x4a, 0x03, 0x8b, 0x11, 0x74, 0x83, 0x55,
		0xc3, 0xbc, 0x77, 0x85, 0xc2, 0xc6, 0x6d, 0x38, 0x36, 0x18, 0xd4, 0xd4, 0xe6, 0xd6, 0x49, 0x18,
		0x76, 0x12, 0xe1, 0xd3, 0x89, 0x52, 0xea, 0x31, 0x0d, 0xf6, 0xf5, 0x81, 0xfb, 0xa3, 0xb2, 0x15
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("default number of columns")
	{
		$m(subject.data(), subject.size(), $hex)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 256 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" R"=(  .dl.....)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad 40" R"=(  J.x(=H.@)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39 4d 9e fd b4 45 a1" R"=(  .9M...E.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 74 68 fc d9 18 cc 3b 32" R"=(  th....;2)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 03 b1 74 b0 d1 46 40 c5" R"=(  ..t..F@.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 10 2b b1 80 37 49 14 63" R"=(  .+..7I.c)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 22 c7 e1 91 12 ad 2b 1f" R"=(  ".....+.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 07 77 e0 fc 99 dd 4f b1" R"=(  .w....O.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 09 5d b4 4d f1 53 c5 28" R"=(  .].M.S.()=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0f e0 10 32 4c a5 16 7c" R"=(  ...2L..|)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 78 4f 5f da 80 4b 92 d9" R"=(  xO_..K..)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 73 e8 73 a4 c3 1a bc d3" R"=(  s.s.....)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 54 b1 78 26 fd 7c 3c b9" R"=(  T.x&.|<.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": c7 84 95 df e3 a5 90 d2" R"=(  ........)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": c4 69 33 6f 1c fa 68 f5" R"=(  .i3o..h.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 47 65 84 74 66 28 53 10" R"=(  Ge.tf(S.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": d3 c6 27 83 ef 72 4e 8e" R"=(  ..'..rN.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": d5 3f 6f bf 3c 25 5a ee" R"=(  .?o.<%Z.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 53 31 d6 0a a6 90 d8 32" R"=(  S1.....2)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0e de 72 71 6e a9 84 f0" R"=(  ..rqn...)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": ff 32 59 58 f5 eb f8 77" R"=(  .2YX...w)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 9d 27 02 16 f2 10 f8 ba" R"=(  .'......)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": cd f4 02 47 f1 37 61 93" R"=(  ...G.7a.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 16 98 4f 02 aa 17 96 7c" R"=(  ..O....|)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 36 58 e7 b6 a0 5c e5 61" R"=(  6X...\.a)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": be 45 ec 16 af b5 e3 14" R"=(  .E......)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 8f d3 9a 8d 2c 4f c3 32" R"=(  ....,O.2)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": d2 4a 03 8b 11 74 83 55" R"=(  .J...t.U)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": c3 bc 77 85 c2 c6 6d 38" R"=(  ..w...m8)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 36 18 d4 d4 e6 d6 49 18" R"=(  6.....I.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 76 12 e1 d3 89 52 ea 31" R"=(  v....R.1)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0d f6 f5 81 fb a3 b2 15" R"=(  ........)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("oversizing column count relative to stream width #1")
	{
		$m(subject.data(), subject.size(), $hex, $col(32))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 256 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11 4a 83 78 28 3d 48 ad 40 01 39 4d 9e fd b4 45 a1 74 68 fc d9 18 cc 3b 32" R"=(  .dl.....J.x(=H.@.9M...E.th....;2)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 03 b1 74 b0 d1 46 40 c5 10 2b b1 80 37 49 14 63 22 c7 e1 91 12 ad 2b 1f 07 77 e0 fc 99 dd 4f b1" R"=(  ..t..F@..+..7I.c".....+..w....O.)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 09 5d b4 4d f1 53 c5 28 0f e0 10 32 4c a5 16 7c 78 4f 5f da 80 4b 92 d9 73 e8 73 a4 c3 1a bc d3" R"=(  .].M.S.(...2L..|xO_..K..s.s.....)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 54 b1 78 26 fd 7c 3c b9 c7 84 95 df e3 a5 90 d2 c4 69 33 6f 1c fa 68 f5 47 65 84 74 66 28 53 10" R"=(  T.x&.|<..........i3o..h.Ge.tf(S.)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": d3 c6 27 83 ef 72 4e 8e d5 3f 6f bf 3c 25 5a ee 53 31 d6 0a a6 90 d8 32 0e de 72 71 6e a9 84 f0" R"=(  ..'..rN..?o.<%Z.S1.....2..rqn...)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": ff 32 59 58 f5 eb f8 77 9d 27 02 16 f2 10 f8 ba cd f4 02 47 f1 37 61 93 16 98 4f 02 aa 17 96 7c" R"=(  .2YX...w.'.........G.7a...O....|)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 36 58 e7 b6 a0 5c e5 61 be 45 ec 16 af b5 e3 14 8f d3 9a 8d 2c 4f c3 32 d2 4a 03 8b 11 74 83 55" R"=(  6X...\.a.E..........,O.2.J...t.U)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": c3 bc 77 85 c2 c6 6d 38 36 18 d4 d4 e6 d6 49 18 76 12 e1 d3 89 52 ea 31 0d f6 f5 81 fb a3 b2 15" R"=(  ..w...m86.....I.v....R.1........)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("oversizing column count relative to stream width #2")
	{
		$m(subject.data(), subject.size(), $hex, $grp(4), $be, $col(8))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 256 bytes of 4-byte hexadecimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df646ccf f9cbed11 4a837828 3d48ad40 01394d9e fdb445a1 7468fcd9 18cc3b32" R"=(  .dl.....J.x(=H.@.9M...E.th....;2)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 03b174b0 d14640c5 102bb180 37491463 22c7e191 12ad2b1f 0777e0fc 99dd4fb1" R"=(  ..t..F@..+..7I.c".....+..w....O.)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 095db44d f153c528 0fe01032 4ca5167c 784f5fda 804b92d9 73e873a4 c31abcd3" R"=(  .].M.S.(...2L..|xO_..K..s.s.....)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 54b17826 fd7c3cb9 c78495df e3a590d2 c469336f 1cfa68f5 47658474 66285310" R"=(  T.x&.|<..........i3o..h.Ge.tf(S.)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": d3c62783 ef724e8e d53f6fbf 3c255aee 5331d60a a690d832 0ede7271 6ea984f0" R"=(  ..'..rN..?o.<%Z.S1.....2..rqn...)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": ff325958 f5ebf877 9d270216 f210f8ba cdf40247 f1376193 16984f02 aa17967c" R"=(  .2YX...w.'.........G.7a...O....|)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3658e7b6 a05ce561 be45ec16 afb5e314 8fd39a8d 2c4fc332 d24a038b 11748355" R"=(  6X...\.a.E..........,O.2.J...t.U)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": c3bc7785 c2c66d38 3618d4d4 e6d64918 7612e1d3 8952ea31 0df6f581 fba3b215" R"=(  ..w...m86.....I.v....R.1........)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("oversizing column count relative to stream width #3")
	{
		$m(subject.data(), subject.size(), $hex, $grp(8), $be, $col(4))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 256 bytes of 8-byte hexadecimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df646ccff9cbed11 4a8378283d48ad40 01394d9efdb445a1 7468fcd918cc3b32" R"=(  .dl.....J.x(=H.@.9M...E.th....;2)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 03b174b0d14640c5 102bb18037491463 22c7e19112ad2b1f 0777e0fc99dd4fb1" R"=(  ..t..F@..+..7I.c".....+..w....O.)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 095db44df153c528 0fe010324ca5167c 784f5fda804b92d9 73e873a4c31abcd3" R"=(  .].M.S.(...2L..|xO_..K..s.s.....)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 54b17826fd7c3cb9 c78495dfe3a590d2 c469336f1cfa68f5 4765847466285310" R"=(  T.x&.|<..........i3o..h.Ge.tf(S.)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": d3c62783ef724e8e d53f6fbf3c255aee 5331d60aa690d832 0ede72716ea984f0" R"=(  ..'..rN..?o.<%Z.S1.....2..rqn...)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": ff325958f5ebf877 9d270216f210f8ba cdf40247f1376193 16984f02aa17967c" R"=(  .2YX...w.'.........G.7a...O....|)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3658e7b6a05ce561 be45ec16afb5e314 8fd39a8d2c4fc332 d24a038b11748355" R"=(  6X...\.a.E..........,O.2.J...t.U)=" "\n"; address += 32;
		expected << "    " << std::hex << address << RESET_FLAGS << ": c3bc7785c2c66d38 3618d4d4e6d64918 7612e1d38952ea31 0df6f581fba3b215" R"=(  ..w...m86.....I.v....R.1........)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("oversizing column count relative to stream width #4")
	{
		$m(subject.data(), subject.size(), $bin, $grp(8), $be, $col(2))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 256 bytes of 8-byte binary, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1101111101100100011011001100111111111001110010111110110100010001 0100101010000011011110000010100000111101010010001010110101000000" R"=(  .dl.....J.x(=H.@)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0000000100111001010011011001111011111101101101000100010110100001 0111010001101000111111001101100100011000110011000011101100110010" R"=(  .9M...E.th....;2)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0000001110110001011101001011000011010001010001100100000011000101 0001000000101011101100011000000000110111010010010001010001100011" R"=(  ..t..F@..+..7I.c)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0010001011000111111000011001000100010010101011010010101100011111 0000011101110111111000001111110010011001110111010100111110110001" R"=(  ".....+..w....O.)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0000100101011101101101000100110111110001010100111100010100101000 0000111111100000000100000011001001001100101001010001011001111100" R"=(  .].M.S.(...2L..|)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0111100001001111010111111101101010000000010010111001001011011001 0111001111101000011100111010010011000011000110101011110011010011" R"=(  xO_..K..s.s.....)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0101010010110001011110000010011011111101011111000011110010111001 1100011110000100100101011101111111100011101001011001000011010010" R"=(  T.x&.|<.........)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1100010001101001001100110110111100011100111110100110100011110101 0100011101100101100001000111010001100110001010000101001100010000" R"=(  .i3o..h.Ge.tf(S.)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1101001111000110001001111000001111101111011100100100111010001110 1101010100111111011011111011111100111100001001010101101011101110" R"=(  ..'..rN..?o.<%Z.)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0101001100110001110101100000101010100110100100001101100000110010 0000111011011110011100100111000101101110101010011000010011110000" R"=(  S1.....2..rqn...)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1111111100110010010110010101100011110101111010111111100001110111 1001110100100111000000100001011011110010000100001111100010111010" R"=(  .2YX...w.'......)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1100110111110100000000100100011111110001001101110110000110010011 0001011010011000010011110000001010101010000101111001011001111100" R"=(  ...G.7a...O....|)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0011011001011000111001111011011010100000010111001110010101100001 1011111001000101111011000001011010101111101101011110001100010100" R"=(  6X...\.a.E......)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1000111111010011100110101000110100101100010011111100001100110010 1101001001001010000000111000101100010001011101001000001101010101" R"=(  ....,O.2.J...t.U)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1100001110111100011101111000010111000010110001100110110100111000 0011011000011000110101001101010011100110110101100100100100011000" R"=(  ..w...m86.....I.)=" "\n"; address += 16;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0111011000010010111000011101001110001001010100101110101000110001 0000110111110110111101011000000111111011101000111011001000010101" R"=(  v....R.1........)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("undersizing column count relative to stream width")
	{
		$m(subject.data(), subject.size(), $hex, $col(8))

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 256 bytes of 1-byte hexadecimal\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed 11" R"=(  .dl.....)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad 40" R"=(  J.x(=H.@)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39 4d 9e fd b4 45 a1" R"=(  .9M...E.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 74 68 fc d9 18 cc 3b 32" R"=(  th....;2)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 03 b1 74 b0 d1 46 40 c5" R"=(  ..t..F@.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 10 2b b1 80 37 49 14 63" R"=(  .+..7I.c)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 22 c7 e1 91 12 ad 2b 1f" R"=(  ".....+.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 07 77 e0 fc 99 dd 4f b1" R"=(  .w....O.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 09 5d b4 4d f1 53 c5 28" R"=(  .].M.S.()=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0f e0 10 32 4c a5 16 7c" R"=(  ...2L..|)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 78 4f 5f da 80 4b 92 d9" R"=(  xO_..K..)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 73 e8 73 a4 c3 1a bc d3" R"=(  s.s.....)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 54 b1 78 26 fd 7c 3c b9" R"=(  T.x&.|<.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": c7 84 95 df e3 a5 90 d2" R"=(  ........)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": c4 69 33 6f 1c fa 68 f5" R"=(  .i3o..h.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 47 65 84 74 66 28 53 10" R"=(  Ge.tf(S.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": d3 c6 27 83 ef 72 4e 8e" R"=(  ..'..rN.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": d5 3f 6f bf 3c 25 5a ee" R"=(  .?o.<%Z.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 53 31 d6 0a a6 90 d8 32" R"=(  S1.....2)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0e de 72 71 6e a9 84 f0" R"=(  ..rqn...)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": ff 32 59 58 f5 eb f8 77" R"=(  .2YX...w)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 9d 27 02 16 f2 10 f8 ba" R"=(  .'......)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": cd f4 02 47 f1 37 61 93" R"=(  ...G.7a.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 16 98 4f 02 aa 17 96 7c" R"=(  ..O....|)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 36 58 e7 b6 a0 5c e5 61" R"=(  6X...\.a)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": be 45 ec 16 af b5 e3 14" R"=(  .E......)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 8f d3 9a 8d 2c 4f c3 32" R"=(  ....,O.2)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": d2 4a 03 8b 11 74 83 55" R"=(  .J...t.U)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": c3 bc 77 85 c2 c6 6d 38" R"=(  ..w...m8)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 36 18 d4 d4 e6 d6 49 18" R"=(  6.....I.)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 76 12 e1 d3 89 52 ea 31" R"=(  v....R.1)=" "\n"; address += 8;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 0d f6 f5 81 fb a3 b2 15" R"=(  ........)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$m(...) printing leftovers", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32,
		0x03, 0xb1, 0x74, 0xb0, 0xd1, 0x46, 0x40, 0xc5, 0x10, 0x2b, 0xb1, 0x80, 0x37, 0x49, 0x14, 0x63,
		0x22, 0xc7, 0xe1, 0x91, 0x12, 0xad, 0x2b, 0x1f, 0x07, 0x77, 0xe0, 0xfc, 0x99, 0xdd, 0x4f, 0xb1,
		0x09, 0x5d, 0xb4, 0x4d, 0xf1, 0x53, 0xc5, 0x28, 0x0f, 0xe0, 0x10, 0x32, 0x4c, 0xa5, 0x16, 0x7c,
		0x78, 0x4f, 0x5f, 0xda, 0x80, 0x4b, 0x92, 0xd9, 0x73, 0xe8, 0x73, 0xa4, 0xc3, 0x1a, 0xbc, 0xd3,
		0x54, 0xb1, 0x78, 0x26, 0xfd, 0x7c, 0x3c, 0xb9, 0xc7, 0x84, 0x95, 0xdf, 0xe3, 0xa5, 0x90, 0xd2,
		0xc4, 0x69, 0x33, 0x6f, 0x1c, 0xfa, 0x68, 0xf5, 0x47, 0x65, 0x84, 0x74, 0x66, 0x28, 0x53, 0x10,
		0xd3, 0xc6, 0x27, 0x83, 0xef, 0x72, 0x4e, 0x8e, 0xd5, 0x3f, 0x6f, 0xbf, 0x3c, 0x25, 0x5a, 0xee,
		0x53, 0x31, 0xd6, 0x0a, 0xa6, 0x90, 0xd8, 0x32, 0x0e, 0xde, 0x72, 0x71, 0x6e, 0xa9, 0x84, 0xf0,
		0xff, 0x32, 0x59, 0x58, 0xf5, 0xeb, 0xf8, 0x77, 0x9d, 0x27, 0x02, 0x16, 0xf2, 0x10, 0xf8, 0xba,
		0xcd, 0xf4, 0x02, 0x47, 0xf1, 0x37, 0x61, 0x93, 0x16, 0x98, 0x4f, 0x02, 0xaa, 0x17, 0x96, 0x7c,
		0x36, 0x58, 0xe7, 0xb6, 0xa0, 0x5c, 0xe5, 0x61, 0xbe, 0x45, 0xec, 0x16, 0xaf, 0xb5, 0xe3, 0x14,
		0x8f, 0xd3, 0x9a, 0x8d, 0x2c, 0x4f, 0xc3, 0x32, 0xd2, 0x4a, 0x03, 0x8b, 0x11, 0x74, 0x83, 0x55,
		0xc3, 0xbc, 0x77, 0x85, 0xc2, 0xc6, 0x6d, 0x38, 0x36, 0x18, 0xd4, 0xd4, 0xe6, 0xd6, 0x49, 0x18,
		0x76, 0x12, 0xe1, 0xd3, 0x89, 0x52, 0xea, 0x31, 0x0d, 0xf6, 0xf5, 0x81, 0xfb, 0xa3, 0xb2, 0x15
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("1 leftover with $udec, $grp(2), $be")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 64 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 129 bytes of 2-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 25823 53100 52217  4589" R"=(  .dl.....)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 33610 10360 18493 16557" R"=(  J.x(=H.@)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 14593 40525 46333 41285" R"=(  .9M...E.)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 26740 55804 52248 12859" R"=(  th....;2)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 45315 45172 18129 50496" R"=(  ..t..F@.)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11024 32945 18743 25364" R"=(  .+..7I.c)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 50978 37345 44306  7979" R"=(  ".....+.)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 30471 64736 56729 45391" R"=(  .w....O.)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 23817 19892 21489 10437" R"=(  .].M.S.()=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 57359 12816 42316 31766" R"=(  ...2L..|)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 20344 55903 19328 55698" R"=(  xO_..K..)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 59507 42099  6851 54204" R"=(  s.s.....)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 45396  9848 31997 47420" R"=(  T.x&.|<.)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 33991 57237 42467 53904" R"=(  ........)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 27076 28467 64028 62824" R"=(  .i3o..h.)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 25927 29828 10342  4179" R"=(  Ge.tf(S.)=" "\n"; address += type_size * 4;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": d3                     " R"=(  .)="        "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 leftovers with $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 32 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 130 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" R"=(  J.x(=H.@)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2655860993 2705700093" R"=(  .9M...E.)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3657197684  842779672" R"=(  th....;2)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2960437507 3309323985" R"=(  ..t..F@.)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2159094544 1662273847" R"=(  .+..7I.c)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2447492898  522956050" R"=(  ".....+.)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4242568967 2974801305" R"=(  .w....O.)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1303665929  684020721" R"=(  .].M.S.()=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  839966735 2081858892" R"=(  ...2L..|)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3663679352 3650243456" R"=(  xO_..K..)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2759059571 3552320195" R"=(  s.s.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  645443924 3107749117" R"=(  T.x&.|<.)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3751118023 3532695011" R"=(  ........)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1865640388 4117297692" R"=(  .i3o..h.)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 1954833735  273885286" R"=(  Ge.tf(S.)=" "\n"; address += type_size * 2;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": d3 c6                " R"=(  ..)="       "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("6 leftovers with $udec, $grp(8), $be")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 16 + 6, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 134 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" R"=(  J.x(=H.@)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11620893414875019521" R"=(  .9M...E.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  3619711132630804596" R"=(  th....;2)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 14213438290403832067" R"=(  ..t..F@.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  7139411812020202256" R"=(  .+..7I.c)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  2246079134442833698" R"=(  ".....+.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 12776674321315690247" R"=(  .w....O.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  2937846627785006345" R"=(  .].M.S.()=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  8941515856866762767" R"=(  ...2L..|)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 15677676269621694328" R"=(  xO_..K..)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 15257099065204402291" R"=(  s.s.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 13347680822333321556" R"=(  T.x&.|<.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 15172809542738478279" R"=(  ........)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 17683658936901921220" R"=(  .i3o..h.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1176328348180440391" R"=(  Ge.tf(S.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": d3 c6 27 83 ef 72   " R"=(  ..'..r)="   "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("7 leftovers with $udec(8, $be)")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 16 + 7, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 135 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" R"=(  J.x(=H.@)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11620893414875019521" R"=(  .9M...E.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  3619711132630804596" R"=(  th....;2)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 14213438290403832067" R"=(  ..t..F@.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  7139411812020202256" R"=(  .+..7I.c)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  2246079134442833698" R"=(  ".....+.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 12776674321315690247" R"=(  .w....O.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  2937846627785006345" R"=(  .].M.S.()=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  8941515856866762767" R"=(  ...2L..|)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 15677676269621694328" R"=(  xO_..K..)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 15257099065204402291" R"=(  s.s.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 13347680822333321556" R"=(  T.x&.|<.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 15172809542738478279" R"=(  ........)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 17683658936901921220" R"=(  .i3o..h.)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1176328348180440391" R"=(  Ge.tf(S.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": d3 c6 27 83 ef 72 4e" R"=(  ..'..rN)="   "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$m(...) incomplete lines and leftovers", "[m]")
{
	test::out_stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uintptr_t address {reinterpret_cast<std::uintptr_t>(subject.data())};

	SECTION("1 line, 0 items, 1 leftover, $udec, $grp(2), $be")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 0 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 1 bytes of 2-byte unsigned decimal, big-endian\n";
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df                     " R"=(  .)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 1 item, 1 leftover, $udec, $grp(2), $be")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 1 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 3 bytes of 2-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 25823                  " R"=(  .d)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 6c                     " R"=(  l)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, incomplete by 1 item, 1 leftover, $udec, $grp(2), $be")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 7 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 15 bytes of 2-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 25823 53100 52217  4589" R"=(  .dl.....)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 33610 10360 18493      " R"=(  J.x(=H)="   "\n"; address += type_size * 3;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": ad                     " R"=(  .)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 0 items on the last line, 1 leftover, $udec, $grp(2), $be")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 8 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 17 bytes of 2-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 25823 53100 52217  4589" R"=(  .dl.....)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 33610 10360 18493 16557" R"=(  J.x(=H.@)=" "\n"; address += type_size * 4;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01                     " R"=(  .)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 1 item on the last line, 1 leftover, $udec, $grp(2), $be")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 9 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 19 bytes of 2-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 25823 53100 52217  4589" R"=(  .dl.....)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 33610 10360 18493 16557" R"=(  J.x(=H.@)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 14593                  " R"=(  .9)="       "\n"; address += 2;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4d                     " R"=(  M)="        "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, last line is incomplete by 1 item, 1 leftover, $udec, $grp(2), $be")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 15 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 31 bytes of 2-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 25823 53100 52217  4589" R"=(  .dl.....)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 33610 10360 18493 16557" R"=(  J.x(=H.@)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 14593 40525 46333 41285" R"=(  .9M...E.)=" "\n"; address += type_size * 4;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 26740 55804 52248      " R"=(  th....)="   "\n"; address += type_size * 3;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3b                     " R"=(  ;)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 0 items, 1 leftover, $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 0 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 1 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df                   " R"=(  .)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 0 items, 2 leftovers, $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 0 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 2 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64                " R"=(  .d)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 0 items, 3 leftovers, $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 0 + 3, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 3 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c             " R"=(  .dl)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 1 item, 1 leftover, $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 1 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 5 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423           " R"=(  .dl.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": f9                   " R"=(  .)="     "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 1 item, 2 leftovers, $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 1 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 6 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423           " R"=(  .dl.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": f9 cb                " R"=(  ..)="   "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 1 item, 3 leftovers, $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 1 + 3, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 7 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423           " R"=(  .dl.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": f9 cb ed             " R"=(  ...)="  "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, incomplete by 1 item, 1 leftover $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 3 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 13 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570           " R"=(  J.x()="      "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3d                   " R"=(  =)="         "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, incomplete by 1 item, 2 leftovers $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 3 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 14 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570           " R"=(  J.x()=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3d 48                " R"=(  =H)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, incomplete by 1 item, 3 leftovers $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 3 + 3, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 15 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570           " R"=(  J.x()=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3d 48 ad             " R"=(  =H.)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 0 items on the last line, 1 leftover $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 4 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 17 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" R"=(  J.x(=H.@)=" "\n"; address += type_size * 2;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01                   " R"=(  .)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 0 items on the last line, 2 leftovers $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 4 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 18 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" R"=(  J.x(=H.@)=" "\n"; address += type_size * 2;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39                " R"=(  .9)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 0 items on the last line, 3 leftovers $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 4 + 3, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 19 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" R"=(  J.x(=H.@)=" "\n"; address += type_size * 2;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39 4d             " R"=(  .9M)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 1 item on the last line, 1 leftover $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 5 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 21 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" R"=(  J.x(=H.@)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2655860993           " R"=(  .9M.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": fd                   " R"=(  .)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 1 item on the last line, 2 leftovers $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 5 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 22 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" R"=(  J.x(=H.@)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2655860993           " R"=(  .9M.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": fd b4                " R"=(  ..)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 1 item on the last line, 3 leftovers $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 5 + 3, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 23 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" R"=(  J.x(=H.@)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2655860993           " R"=(  .9M.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": fd b4 45             " R"=(  ..E)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, last line is incomplete by 1 item, 1 leftover $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 7 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 29 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" R"=(  J.x(=H.@)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2655860993 2705700093" R"=(  .9M...E.)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3657197684           " R"=(  th..)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 18                   " R"=(  .)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, last line is incomplete by 1 item, 2 leftovers $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 7 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 30 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" R"=(  J.x(=H.@)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2655860993 2705700093" R"=(  .9M...E.)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3657197684           " R"=(  th..)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 18 cc                " R"=(  ..)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, last line is incomplete by 1 item, 3 leftovers $udec, $grp(4), $be")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 7 + 3, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 31 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3479987423  300796921" R"=(  .dl.....)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  678986570 1085098045" R"=(  J.x(=H.@)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 2655860993 2705700093" R"=(  .9M...E.)=" "\n"; address += type_size * 2;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 3657197684           " R"=(  th..)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 18 cc 3b             " R"=(  ..;)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 0 items, 1 leftover, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 0 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 1 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df                  " R"=(  .)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 0 items, 2 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 0 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 2 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64               " R"=(  .d)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 0 items, 6 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 0 + 6, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 6 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb   " R"=(  .dl...)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 0 items, 7 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 0 + 7, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 7 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": df 64 6c cf f9 cb ed" R"=(  .dl....)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 1 item / incomplete by 1 item, 1 leftover, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 1 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 9 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a                  " R"=(  J)="        "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 1 item / incomplete by 1 item, 2 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 1 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 10 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83               " R"=(  J.)="       "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 1 item / incomplete by 1 item, 6 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 1 + 6, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 14 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48   " R"=(  J.x(=H)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("1 line, 1 item / incomplete by 1 item, 7 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 1 + 7, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 15 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 4a 83 78 28 3d 48 ad" R"=(  J.x(=H.)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 0 items on the last line, 1 leftover, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};
		$m(subject.data(), type_size * 2 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 17 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" R"=(  J.x(=H.@)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01                  " R"=(  .)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 0 items on the last line, 2 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};
		$m(subject.data(), type_size * 2 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 18 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" R"=(  J.x(=H.@)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39               " R"=(  .9)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 0 items on the last line, 6 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};
		$m(subject.data(), type_size * 2 + 6, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 22 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" R"=(  J.x(=H.@)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39 4d 9e fd b4   " R"=(  .9M...)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 0 items on the last line, 7 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};
		$m(subject.data(), type_size * 2 + 7, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 23 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" R"=(  J.x(=H.@)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 01 39 4d 9e fd b4 45" R"=(  .9M...E)=" "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 1 item on the last line / incomplete by 1 item, 1 leftover, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};
		$m(subject.data(), type_size * 3 + 1, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 25 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" R"=(  J.x(=H.@)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11620893414875019521" R"=(  .9M...E.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 74                  " R"=(  t)="        "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 1 item on the last line / incomplete by 1 item, 2 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};
		$m(subject.data(), type_size * 3 + 2, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 26 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" R"=(  J.x(=H.@)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11620893414875019521" R"=(  .9M...E.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 74 68               " R"=(  th)="        "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 1 item on the last line / incomplete by 1 item, 6 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};
		$m(subject.data(), type_size * 3 + 6, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 30 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" R"=(  J.x(=H.@)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11620893414875019521" R"=(  .9M...E.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 74 68 fc d9 18 cc   " R"=(  th....)="        "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("2 lines, 1 item on the last line / incomplete by 1 item, 7 leftovers, $udec, $grp(8), $be")
	{
		std::size_t type_size {8};
		$m(subject.data(), type_size * 3 + 7, $udec, $grp(type_size), $be)

		std::stringstream expected;
		expected.unsetf(std::ios::basefield);
		expected << "subject.data(), 31 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ":  1291912941912483039" R"=(  .dl.....)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ":  4660460616907522890" R"=(  J.x(=H.@)=" "\n"; address += type_size * 1;
		expected << "    " << std::hex << address << RESET_FLAGS << ": 11620893414875019521" R"=(  .9M...E.)=" "\n"; address += type_size * 1;
		expected << "\n";
		expected << "    leftovers:\n";
		expected << "    " << std::hex << address << RESET_FLAGS << ": 74 68 fc d9 18 cc 3b" R"=(  th....;)="        "\n";
		expected << "\n";

		REQUIRE(test::out_stream.str() == expected.str());
	}
}

