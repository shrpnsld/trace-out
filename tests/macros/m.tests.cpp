#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <vector>

TEST_CASE("$m(<pointer>, <size>)", "[m]")
{
	test::stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40
	};

	SECTION("zero size")
	{
		$m(subject.data(), 0)

		std::stringstream expected;
		expected <<
			"subject.data(), 0 bytes of 1-byte hexadecimal\n"
			"    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("non-zero size")
	{
		$m(subject.data(), subject.size())

		std::stringstream expected;
		expected <<
			"subject.data(), 16 bytes of 1-byte hexadecimal\n"
			"    " << static_cast<const void *>(subject.data()) << ":"
			" df 64 6c cf f9 cb ed 11 4a 83 78 28 3d 48 ad 40" "\n"
			"    \n";

		REQUIRE(test::stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $bin(<grouping>))", "[m]")
{
	test::stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uint8_t *memory {subject.data()};

	SECTION("$bin")
	{
		$m(subject.data(), subject.size(), $bin)

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte binary\n";
		expected << "    " << static_cast<const void *>(memory) << ": 11011111 01100100 01101100 11001111" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 11111001 11001011 11101101 00010001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 01001010 10000011 01111000 00101000" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 00111101 01001000 10101101 01000000" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 00000001 00111001 01001101 10011110" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 11111101 10110100 01000101 10100001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 01110100 01101000 11111100 11011001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 00011000 11001100 00111011 00110010" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$bin(1)")
	{
		$m(subject.data(), subject.size(), $bin(1))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte binary\n";
		expected << "    " << static_cast<const void *>(memory) << ": 11011111 01100100 01101100 11001111" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 11111001 11001011 11101101 00010001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 01001010 10000011 01111000 00101000" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 00111101 01001000 10101101 01000000" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 00000001 00111001 01001101 10011110" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 11111101 10110100 01000101 10100001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 01110100 01101000 11111100 11011001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 00011000 11001100 00111011 00110010" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$bin(2)")
	{
		$m(subject.data(), subject.size(), $bin(2))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 2-byte binary\n";
		expected << "    " << static_cast<const void *>(memory) << ": 1101111101100100 0110110011001111" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 1111100111001011 1110110100010001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 0100101010000011 0111100000101000" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 0011110101001000 1010110101000000" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 0000000100111001 0100110110011110" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 1111110110110100 0100010110100001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 0111010001101000 1111110011011001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 0001100011001100 0011101100110010" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$bin(4)")
	{
		$m(subject.data(), subject.size(), $bin(4))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 4-byte binary\n";
		expected << "    " << static_cast<const void *>(memory) << ": 11011111011001000110110011001111" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 11111001110010111110110100010001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 01001010100000110111100000101000" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 00111101010010001010110101000000" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 00000001001110010100110110011110" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 11111101101101000100010110100001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 01110100011010001111110011011001" "\n"; memory += 4;
		expected << "    " << static_cast<const void *>(memory) << ": 00011000110011000011101100110010" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$bin(8)")
	{
		$m(subject.data(), subject.size(), $bin(8))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 8-byte binary\n";
		expected << "    " << static_cast<const void *>(memory) << ": 1101111101100100011011001100111111111001110010111110110100010001" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0100101010000011011110000010100000111101010010001010110101000000" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0000000100111001010011011001111011111101101101000100010110100001" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0111010001101000111111001101100100011000110011000011101100110010" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $hex(<grouping>))", "[m]")
{
	test::stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uint8_t *memory {subject.data()};

	SECTION("$hex")
	{
		$m(subject.data(), subject.size(), $hex)

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df 64 6c cf f9 cb ed 11 4a 83 78 28 3d 48 ad 40" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 01 39 4d 9e fd b4 45 a1 74 68 fc d9 18 cc 3b 32" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$hex(1)")
	{
		$m(subject.data(), subject.size(), $hex(1))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df 64 6c cf f9 cb ed 11 4a 83 78 28 3d 48 ad 40" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 01 39 4d 9e fd b4 45 a1 74 68 fc d9 18 cc 3b 32" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$hex(2)")
	{
		$m(subject.data(), subject.size(), $hex(2))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 2-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df64 6ccf f9cb ed11 4a83 7828 3d48 ad40" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 0139 4d9e fdb4 45a1 7468 fcd9 18cc 3b32" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$hex(4)")
	{
		$m(subject.data(), subject.size(), $hex(4))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 4-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df646ccf f9cbed11 4a837828 3d48ad40" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 01394d9e fdb445a1 7468fcd9 18cc3b32" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$hex(8)")
	{
		$m(subject.data(), subject.size(), $hex(8))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 8-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df646ccff9cbed11 4a8378283d48ad40" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 01394d9efdb445a1 7468fcd918cc3b32" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $sdec(<grouping>, <byte-order>))", "[m]")
{
	test::stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uint8_t *memory {subject.data()};

	SECTION("$sdec($le)")
	{
		$m(subject.data(), subject.size(), $sdec($le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
		expected << "    " << static_cast<const void *>(memory) << ":  -33  100  108  -49   -7  -53  -19   17" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":   74 -125  120   40   61   72  -83   64" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":    1   57   77  -98   -3  -76   69  -95" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  116  104   -4  -39   24  -52   59   50" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$sdec($be)")
	{
		$m(subject.data(), subject.size(), $sdec($be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
		expected << "    " << static_cast<const void *>(memory) << ":  -33  100  108  -49   -7  -53  -19   17" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":   74 -125  120   40   61   72  -83   64" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":    1   57   77  -98   -3  -76   69  -95" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  116  104   -4  -39   24  -52   59   50" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$sdec(1, $le)")
	{
		$m(subject.data(), subject.size(), $sdec(1, $le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
		expected << "    " << static_cast<const void *>(memory) << ":  -33  100  108  -49   -7  -53  -19   17" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":   74 -125  120   40   61   72  -83   64" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":    1   57   77  -98   -3  -76   69  -95" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  116  104   -4  -39   24  -52   59   50" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$sdec(1, $be)")
	{
		$m(subject.data(), subject.size(), $sdec(1, $be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte signed decimal\n";
		expected << "    " << static_cast<const void *>(memory) << ":  -33  100  108  -49   -7  -53  -19   17" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":   74 -125  120   40   61   72  -83   64" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":    1   57   77  -98   -3  -76   69  -95" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  116  104   -4  -39   24  -52   59   50" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$sdec(2, $le)")
	{
		$m(subject.data(), subject.size(), $sdec(2, $le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 2-byte signed decimal, little-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":  -8348  27855  -1589  -4847" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  19075  30760  15688 -21184" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":    313  19870   -588  17825" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  29800   -807   6348  15154" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$sdec(2, $be)")
	{
		$m(subject.data(), subject.size(), $sdec(2, $be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 2-byte signed decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":  25823 -12436 -13319   4589" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": -31926  10360  18493  16557" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  14593 -25011 -19203 -24251" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  26740  -9732 -13288  12859" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$sdec(4, $le)")
	{
		$m(subject.data(), subject.size(), $sdec(4, $le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 4-byte signed decimal, little-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":  -547066673  -104076015  1250129960  1028173120" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":    20532638   -38517343  1953037529   416037682" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$sdec(4, $be)")
	{
		$m(subject.data(), subject.size(), $sdec(4, $be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 4-byte signed decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":  -814979873   300796921   678986570  1085098045" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": -1639106303 -1589267203  -637769612   842779672" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$sdec(8, $le)")
	{
		$m(subject.data(), subject.size(), $sdec(8, $le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 8-byte signed decimal, little-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":  -2349633465075634927   5369267294977961280" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":     88187012967056801   8388232315331689266" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$sdec(8, $be)")
	{
		$m(subject.data(), subject.size(), $sdec(8, $be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 8-byte signed decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":   1291912941912483039   4660460616907522890" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  -6825850658834532095   3619711132630804596" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $udec(<grouping>, <byte-order>))", "[m]")
{
	test::stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uint8_t *memory {subject.data()};

	SECTION("$udec($le)")
	{
		$m(subject.data(), subject.size(), $udec($le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": 223 100 108 207 249 203 237  17" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  74 131 120  40  61  72 173  64" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":   1  57  77 158 253 180  69 161" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 116 104 252 217  24 204  59  50" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$udec($be)")
	{
		$m(subject.data(), subject.size(), $udec($be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": 223 100 108 207 249 203 237  17" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  74 131 120  40  61  72 173  64" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":   1  57  77 158 253 180  69 161" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 116 104 252 217  24 204  59  50" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$udec(1, $le)")
	{
		$m(subject.data(), subject.size(), $udec(1, $le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": 223 100 108 207 249 203 237  17" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  74 131 120  40  61  72 173  64" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":   1  57  77 158 253 180  69 161" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 116 104 252 217  24 204  59  50" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$udec(1, $be)")
	{
		$m(subject.data(), subject.size(), $udec(1, $be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 1-byte unsigned decimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": 223 100 108 207 249 203 237  17" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":  74 131 120  40  61  72 173  64" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":   1  57  77 158 253 180  69 161" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 116 104 252 217  24 204  59  50" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$udec(2, $le)")
	{
		$m(subject.data(), subject.size(), $udec(2, $le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 2-byte unsigned decimal, little-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ": 57188 27855 63947 60689 19075 30760 15688 44352" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":   313 19870 64948 17825 29800 64729  6348 15154" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$udec(2, $be)")
	{
		$m(subject.data(), subject.size(), $udec(2, $be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 2-byte unsigned decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ": 25823 53100 52217  4589 33610 10360 18493 16557" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 14593 40525 46333 41285 26740 55804 52248 12859" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$udec(4, $le)")
	{
		$m(subject.data(), subject.size(), $udec(4, $le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 4-byte unsigned decimal, little-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ": 3747900623 4190891281 1250129960 1028173120" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":   20532638 4256449953 1953037529  416037682" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$udec(4, $be)")
	{
		$m(subject.data(), subject.size(), $udec(4, $be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ": 3479987423  300796921  678986570 1085098045" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 2655860993 2705700093 3657197684  842779672" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$udec(8, $le)")
	{
		$m(subject.data(), subject.size(), $udec(8, $le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 8-byte unsigned decimal, little-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ": 16097110608633916689  5369267294977961280" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":    88187012967056801  8388232315331689266" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$udec(8, $be)")
	{
		$m(subject.data(), subject.size(), $udec(8, $be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":  1291912941912483039  4660460616907522890" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 11620893414875019521  3619711132630804596" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $flt(<byte-order>))", "[m]")
{
	test::stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uint8_t *memory {subject.data()};

	SECTION("$flt($le)")
	{
		$m(subject.data(), subject.size(), $flt($le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of " << sizeof(float) << "-byte float, little-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":   -1.64598e+19   -1.32356e+35" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":    4.30799e+06      0.0489933" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":    3.40348e-38   -2.99528e+37" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":    7.38367e+31    5.27925e-24" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$flt($be)")
	{
		$m(subject.data(), subject.size(), $flt($be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of " << sizeof(float) << "-byte float, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":   -3.96603e+09    3.75177e-28" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":    1.37952e-14        5.41507" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":   -1.08644e-20   -6.69857e-19" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ":   -8.88082e+15    1.09312e-08" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $dbl(<byte-order>))", "[m]")
{
	test::stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uint8_t *memory {subject.data()};

	SECTION("$dbl($le)")
	{
		$m(subject.data(), subject.size(), $dbl($le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of " << sizeof(double) << "-byte double, little-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":   -3.34295808947304e+151     9.10544235845569e+50" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":    9.22443858116523e-303    5.72495988265533e+252" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$dbl($be)")
	{
		$m(subject.data(), subject.size(), $dbl($be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of " << sizeof(double) << "-byte double, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":    2.57598040706935e-222         3748.11944939234" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":   -2.12203161888808e-148     1.03105746265379e-66" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $ldbl(<byte-order>))", "[m]")
{
	test::stream.str(std::string {});

	std::vector<std::uint8_t> subject {
		0xdf, 0x64, 0x6c, 0xcf, 0xf9, 0xcb, 0xed, 0x11, 0x4a, 0x83, 0x78, 0x28, 0x3d, 0x48, 0xad, 0x40,
		0x01, 0x39, 0x4d, 0x9e, 0xfd, 0xb4, 0x45, 0xa1, 0x74, 0x68, 0xfc, 0xd9, 0x18, 0xcc, 0x3b, 0x32
	};
	std::uint8_t *memory {subject.data()};

	SECTION("$ldbl($le)")
	{
		$m(subject.data(), subject.size(), $ldbl($le))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of " << sizeof(long double) << "-byte long double, little-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":   -1.11973504014201921e+3473" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":     1.10671162169717802e+434" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("$ldbl($be)")
	{
		$m(subject.data(), subject.size(), $ldbl($be))

		std::stringstream expected;
		expected << "subject.data(), 32 bytes of " << sizeof(long double) << "-byte long double, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":   -6.90527387463601281e-4680" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":    7.37929517979928498e+3117" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}
}

TEST_CASE("$m(<pointer>, <size>, $hex(<grouping>), $col(<columns>))", "[m]")
{
	test::stream.str(std::string {});

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
	std::uint8_t *memory {subject.data()};

	SECTION("default number of columns")
	{
		$m(subject.data(), subject.size(), $hex)

		std::stringstream expected;
		expected << "subject.data(), 256 bytes of 1-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df 64 6c cf f9 cb ed 11 4a 83 78 28 3d 48 ad 40" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 01 39 4d 9e fd b4 45 a1 74 68 fc d9 18 cc 3b 32" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 03 b1 74 b0 d1 46 40 c5 10 2b b1 80 37 49 14 63" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 22 c7 e1 91 12 ad 2b 1f 07 77 e0 fc 99 dd 4f b1" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 09 5d b4 4d f1 53 c5 28 0f e0 10 32 4c a5 16 7c" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 78 4f 5f da 80 4b 92 d9 73 e8 73 a4 c3 1a bc d3" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 54 b1 78 26 fd 7c 3c b9 c7 84 95 df e3 a5 90 d2" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": c4 69 33 6f 1c fa 68 f5 47 65 84 74 66 28 53 10" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": d3 c6 27 83 ef 72 4e 8e d5 3f 6f bf 3c 25 5a ee" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 53 31 d6 0a a6 90 d8 32 0e de 72 71 6e a9 84 f0" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": ff 32 59 58 f5 eb f8 77 9d 27 02 16 f2 10 f8 ba" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": cd f4 02 47 f1 37 61 93 16 98 4f 02 aa 17 96 7c" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 36 58 e7 b6 a0 5c e5 61 be 45 ec 16 af b5 e3 14" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 8f d3 9a 8d 2c 4f c3 32 d2 4a 03 8b 11 74 83 55" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": c3 bc 77 85 c2 c6 6d 38 36 18 d4 d4 e6 d6 49 18" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 76 12 e1 d3 89 52 ea 31 0d f6 f5 81 fb a3 b2 15" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("oversizing column count relative to stream width #1")
	{
		$m(subject.data(), subject.size(), $hex, $col(32))

		std::stringstream expected;
		expected << "subject.data(), 256 bytes of 1-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df 64 6c cf f9 cb ed 11 4a 83 78 28 3d 48 ad 40" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 01 39 4d 9e fd b4 45 a1 74 68 fc d9 18 cc 3b 32" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 03 b1 74 b0 d1 46 40 c5 10 2b b1 80 37 49 14 63" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 22 c7 e1 91 12 ad 2b 1f 07 77 e0 fc 99 dd 4f b1" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 09 5d b4 4d f1 53 c5 28 0f e0 10 32 4c a5 16 7c" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 78 4f 5f da 80 4b 92 d9 73 e8 73 a4 c3 1a bc d3" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 54 b1 78 26 fd 7c 3c b9 c7 84 95 df e3 a5 90 d2" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": c4 69 33 6f 1c fa 68 f5 47 65 84 74 66 28 53 10" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": d3 c6 27 83 ef 72 4e 8e d5 3f 6f bf 3c 25 5a ee" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 53 31 d6 0a a6 90 d8 32 0e de 72 71 6e a9 84 f0" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": ff 32 59 58 f5 eb f8 77 9d 27 02 16 f2 10 f8 ba" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": cd f4 02 47 f1 37 61 93 16 98 4f 02 aa 17 96 7c" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 36 58 e7 b6 a0 5c e5 61 be 45 ec 16 af b5 e3 14" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 8f d3 9a 8d 2c 4f c3 32 d2 4a 03 8b 11 74 83 55" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": c3 bc 77 85 c2 c6 6d 38 36 18 d4 d4 e6 d6 49 18" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 76 12 e1 d3 89 52 ea 31 0d f6 f5 81 fb a3 b2 15" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("oversizing column count relative to stream width #2")
	{
		$m(subject.data(), subject.size(), $hex(4), $col(32))

		std::stringstream expected;
		expected << "subject.data(), 256 bytes of 4-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df646ccf f9cbed11 4a837828 3d48ad40" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 01394d9e fdb445a1 7468fcd9 18cc3b32" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 03b174b0 d14640c5 102bb180 37491463" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 22c7e191 12ad2b1f 0777e0fc 99dd4fb1" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 095db44d f153c528 0fe01032 4ca5167c" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 784f5fda 804b92d9 73e873a4 c31abcd3" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 54b17826 fd7c3cb9 c78495df e3a590d2" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": c469336f 1cfa68f5 47658474 66285310" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": d3c62783 ef724e8e d53f6fbf 3c255aee" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 5331d60a a690d832 0ede7271 6ea984f0" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": ff325958 f5ebf877 9d270216 f210f8ba" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": cdf40247 f1376193 16984f02 aa17967c" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 3658e7b6 a05ce561 be45ec16 afb5e314" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 8fd39a8d 2c4fc332 d24a038b 11748355" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": c3bc7785 c2c66d38 3618d4d4 e6d64918" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 7612e1d3 8952ea31 0df6f581 fba3b215" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("oversizing column count relative to stream width #3")
	{
		$m(subject.data(), subject.size(), $hex(8), $col(32))

		std::stringstream expected;
		expected << "subject.data(), 256 bytes of 8-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df646ccff9cbed11 4a8378283d48ad40" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 01394d9efdb445a1 7468fcd918cc3b32" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 03b174b0d14640c5 102bb18037491463" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 22c7e19112ad2b1f 0777e0fc99dd4fb1" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 095db44df153c528 0fe010324ca5167c" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 784f5fda804b92d9 73e873a4c31abcd3" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 54b17826fd7c3cb9 c78495dfe3a590d2" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": c469336f1cfa68f5 4765847466285310" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": d3c62783ef724e8e d53f6fbf3c255aee" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 5331d60aa690d832 0ede72716ea984f0" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": ff325958f5ebf877 9d270216f210f8ba" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": cdf40247f1376193 16984f02aa17967c" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 3658e7b6a05ce561 be45ec16afb5e314" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 8fd39a8d2c4fc332 d24a038b11748355" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": c3bc7785c2c66d38 3618d4d4e6d64918" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 7612e1d38952ea31 0df6f581fba3b215" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("oversizing column count relative to stream width #4")
	{
		$m(subject.data(), subject.size(), $bin(8), $col(32))

		std::stringstream expected;
		expected << "subject.data(), 256 bytes of 8-byte binary\n";
		expected << "    " << static_cast<const void *>(memory) << ": 1101111101100100011011001100111111111001110010111110110100010001" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0100101010000011011110000010100000111101010010001010110101000000" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0000000100111001010011011001111011111101101101000100010110100001" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0111010001101000111111001101100100011000110011000011101100110010" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0000001110110001011101001011000011010001010001100100000011000101" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0001000000101011101100011000000000110111010010010001010001100011" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0010001011000111111000011001000100010010101011010010101100011111" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0000011101110111111000001111110010011001110111010100111110110001" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0000100101011101101101000100110111110001010100111100010100101000" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0000111111100000000100000011001001001100101001010001011001111100" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0111100001001111010111111101101010000000010010111001001011011001" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0111001111101000011100111010010011000011000110101011110011010011" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0101010010110001011110000010011011111101011111000011110010111001" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1100011110000100100101011101111111100011101001011001000011010010" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1100010001101001001100110110111100011100111110100110100011110101" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0100011101100101100001000111010001100110001010000101001100010000" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1101001111000110001001111000001111101111011100100100111010001110" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1101010100111111011011111011111100111100001001010101101011101110" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0101001100110001110101100000101010100110100100001101100000110010" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0000111011011110011100100111000101101110101010011000010011110000" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1111111100110010010110010101100011110101111010111111100001110111" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1001110100100111000000100001011011110010000100001111100010111010" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1100110111110100000000100100011111110001001101110110000110010011" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0001011010011000010011110000001010101010000101111001011001111100" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0011011001011000111001111011011010100000010111001110010101100001" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1011111001000101111011000001011010101111101101011110001100010100" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1000111111010011100110101000110100101100010011111100001100110010" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1101001001001010000000111000101100010001011101001000001101010101" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 1100001110111100011101111000010111000010110001100110110100111000" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0011011000011000110101001101010011100110110101100100100100011000" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0111011000010010111000011101001110001001010100101110101000110001" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0000110111110110111101011000000111111011101000111011001000010101" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("undersizing column count relative to stream width")
	{
		$m(subject.data(), subject.size(), $hex, $col(8))

		std::stringstream expected;
		expected << "subject.data(), 256 bytes of 1-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df 64 6c cf f9 cb ed 11" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 4a 83 78 28 3d 48 ad 40" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 01 39 4d 9e fd b4 45 a1" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 74 68 fc d9 18 cc 3b 32" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 03 b1 74 b0 d1 46 40 c5" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 10 2b b1 80 37 49 14 63" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 22 c7 e1 91 12 ad 2b 1f" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 07 77 e0 fc 99 dd 4f b1" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 09 5d b4 4d f1 53 c5 28" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0f e0 10 32 4c a5 16 7c" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 78 4f 5f da 80 4b 92 d9" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 73 e8 73 a4 c3 1a bc d3" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 54 b1 78 26 fd 7c 3c b9" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": c7 84 95 df e3 a5 90 d2" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": c4 69 33 6f 1c fa 68 f5" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 47 65 84 74 66 28 53 10" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": d3 c6 27 83 ef 72 4e 8e" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": d5 3f 6f bf 3c 25 5a ee" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 53 31 d6 0a a6 90 d8 32" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0e de 72 71 6e a9 84 f0" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": ff 32 59 58 f5 eb f8 77" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 9d 27 02 16 f2 10 f8 ba" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": cd f4 02 47 f1 37 61 93" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 16 98 4f 02 aa 17 96 7c" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 36 58 e7 b6 a0 5c e5 61" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": be 45 ec 16 af b5 e3 14" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 8f d3 9a 8d 2c 4f c3 32" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": d2 4a 03 8b 11 74 83 55" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": c3 bc 77 85 c2 c6 6d 38" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 36 18 d4 d4 e6 d6 49 18" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 76 12 e1 d3 89 52 ea 31" "\n"; memory += 8;
		expected << "    " << static_cast<const void *>(memory) << ": 0d f6 f5 81 fb a3 b2 15" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("undersizing memory size, so the column is incomplete")
	{
		$m(subject.data(), 5, $hex, $col(8))

		std::stringstream expected;
		expected << "subject.data(), 5 bytes of 1-byte hexadecimal\n";
		expected << "    " << static_cast<const void *>(memory) << ": df 64 6c cf f9" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}
}

TEST_CASE("$m(...) printing leftovers", "[m]")
{
	test::stream.str(std::string {});

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
	std::uint8_t *memory {subject.data()};

	SECTION("1 leftover with $udec(2, $be)")
	{
		std::size_t type_size {2};

		$m(subject.data(), type_size * 64 + 1, $udec(type_size, $be))

		std::stringstream expected;
		expected << "subject.data(), 129 bytes of 2-byte unsigned decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ": 25823 53100 52217  4589 33610 10360 18493 16557" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 14593 40525 46333 41285 26740 55804 52248 12859" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 45315 45172 18129 50496 11024 32945 18743 25364" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 50978 37345 44306  7979 30471 64736 56729 45391" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 23817 19892 21489 10437 57359 12816 42316 31766" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 20344 55903 19328 55698 59507 42099  6851 54204" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 45396  9848 31997 47420 33991 57237 42467 53904" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 27076 28467 64028 62824 25927 29828 10342  4179" "\n"; memory += 16;
		expected << "    \n";
		expected << "    leftovers:\n";
		expected << "    " << static_cast<const void *>(memory) << ": d3" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("2 leftovers with $udec(4, $be)")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 32 + 2, $udec(type_size, $be))

		std::stringstream expected;
		expected << "subject.data(), 130 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ": 3479987423  300796921  678986570 1085098045" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 2655860993 2705700093 3657197684  842779672" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 2960437507 3309323985 2159094544 1662273847" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 2447492898  522956050 4242568967 2974801305" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 1303665929  684020721  839966735 2081858892" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 3663679352 3650243456 2759059571 3552320195" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  645443924 3107749117 3751118023 3532695011" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 1865640388 4117297692 1954833735  273885286" "\n"; memory += 16;
		expected << "    \n";
		expected << "    leftovers:\n";
		expected << "    " << static_cast<const void *>(memory) << ": d3 c6" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("3 leftovers with $udec(4, $be)")
	{
		std::size_t type_size {4};
		$m(subject.data(), type_size * 32 + 3, $udec(type_size, $be))

		std::stringstream expected;
		expected << "subject.data(), 131 bytes of 4-byte unsigned decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ": 3479987423  300796921  678986570 1085098045" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 2655860993 2705700093 3657197684  842779672" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 2960437507 3309323985 2159094544 1662273847" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 2447492898  522956050 4242568967 2974801305" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 1303665929  684020721  839966735 2081858892" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 3663679352 3650243456 2759059571 3552320195" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  645443924 3107749117 3751118023 3532695011" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 1865640388 4117297692 1954833735  273885286" "\n"; memory += 16;
		expected << "    \n";
		expected << "    leftovers:\n";
		expected << "    " << static_cast<const void *>(memory) << ": d3 c6 27" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("4 leftovers with $udec(8, $be)")
	{
		std::size_t type_size {8};
		$m(subject.data(), type_size * 16 + 4, $udec(type_size, $be))

		std::stringstream expected;
		expected << "subject.data(), 132 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":  1291912941912483039  4660460616907522890" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 11620893414875019521  3619711132630804596" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 14213438290403832067  7139411812020202256" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  2246079134442833698 12776674321315690247" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  2937846627785006345  8941515856866762767" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 15677676269621694328 15257099065204402291" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 13347680822333321556 15172809542738478279" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 17683658936901921220  1176328348180440391" "\n"; memory += 16;
		expected << "    \n";
		expected << "    leftovers:\n";
		expected << "    " << static_cast<const void *>(memory) << ": d3 c6 27 83" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("5 leftovers with $udec(8, $be)")
	{
		std::size_t type_size {8};
		$m(subject.data(), type_size * 16 + 5, $udec(type_size, $be))

		std::stringstream expected;
		expected << "subject.data(), 133 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":  1291912941912483039  4660460616907522890" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 11620893414875019521  3619711132630804596" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 14213438290403832067  7139411812020202256" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  2246079134442833698 12776674321315690247" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  2937846627785006345  8941515856866762767" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 15677676269621694328 15257099065204402291" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 13347680822333321556 15172809542738478279" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 17683658936901921220  1176328348180440391" "\n"; memory += 16;
		expected << "    \n";
		expected << "    leftovers:\n";
		expected << "    " << static_cast<const void *>(memory) << ": d3 c6 27 83 ef" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("6 leftovers with $udec(8, $be)")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 16 + 6, $udec(type_size, $be))

		std::stringstream expected;
		expected << "subject.data(), 134 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":  1291912941912483039  4660460616907522890" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 11620893414875019521  3619711132630804596" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 14213438290403832067  7139411812020202256" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  2246079134442833698 12776674321315690247" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  2937846627785006345  8941515856866762767" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 15677676269621694328 15257099065204402291" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 13347680822333321556 15172809542738478279" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 17683658936901921220  1176328348180440391" "\n"; memory += 16;
		expected << "    \n";
		expected << "    leftovers:\n";
		expected << "    " << static_cast<const void *>(memory) << ": d3 c6 27 83 ef 72" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("7 leftovers with $udec(8, $be)")
	{
		std::size_t type_size {8};

		$m(subject.data(), type_size * 16 + 7, $udec(type_size, $be))

		std::stringstream expected;
		expected << "subject.data(), 135 bytes of 8-byte unsigned decimal, big-endian\n";
		expected << "    " << static_cast<const void *>(memory) << ":  1291912941912483039  4660460616907522890" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 11620893414875019521  3619711132630804596" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 14213438290403832067  7139411812020202256" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  2246079134442833698 12776674321315690247" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ":  2937846627785006345  8941515856866762767" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 15677676269621694328 15257099065204402291" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 13347680822333321556 15172809542738478279" "\n"; memory += 16;
		expected << "    " << static_cast<const void *>(memory) << ": 17683658936901921220  1176328348180440391" "\n"; memory += 16;
		expected << "    \n";
		expected << "    leftovers:\n";
		expected << "    " << static_cast<const void *>(memory) << ": d3 c6 27 83 ef 72 4e" "\n";
		expected << "    \n";

		REQUIRE(test::stream.str() == expected.str());
	}
}

