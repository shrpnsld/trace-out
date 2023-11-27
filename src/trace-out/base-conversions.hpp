#pragma once

//
// Public

namespace trace_out
{

inline const char *byte_to_binary(standard::uint8_t byte);
inline const char *byte_to_octal(standard::uint8_t byte);
inline const char *byte_to_hexadecimal(standard::uint8_t byte);

}

//
// Implementation

namespace trace_out
{

const char *byte_to_binary(standard::uint8_t byte)
{
	static const char *const BINARY_VALUES[] = {
		"00000000", "00000001", "00000010", "00000011", "00000100", "00000101", "00000110", "00000111",
		"00001000", "00001001", "00001010", "00001011", "00001100", "00001101", "00001110", "00001111",
		"00010000", "00010001", "00010010", "00010011", "00010100", "00010101", "00010110", "00010111",
		"00011000", "00011001", "00011010", "00011011", "00011100", "00011101", "00011110", "00011111",
		"00100000", "00100001", "00100010", "00100011", "00100100", "00100101", "00100110", "00100111",
		"00101000", "00101001", "00101010", "00101011", "00101100", "00101101", "00101110", "00101111",
		"00110000", "00110001", "00110010", "00110011", "00110100", "00110101", "00110110", "00110111",
		"00111000", "00111001", "00111010", "00111011", "00111100", "00111101", "00111110", "00111111",
		"01000000", "01000001", "01000010", "01000011", "01000100", "01000101", "01000110", "01000111",
		"01001000", "01001001", "01001010", "01001011", "01001100", "01001101", "01001110", "01001111",
		"01010000", "01010001", "01010010", "01010011", "01010100", "01010101", "01010110", "01010111",
		"01011000", "01011001", "01011010", "01011011", "01011100", "01011101", "01011110", "01011111",
		"01100000", "01100001", "01100010", "01100011", "01100100", "01100101", "01100110", "01100111",
		"01101000", "01101001", "01101010", "01101011", "01101100", "01101101", "01101110", "01101111",
		"01110000", "01110001", "01110010", "01110011", "01110100", "01110101", "01110110", "01110111",
		"01111000", "01111001", "01111010", "01111011", "01111100", "01111101", "01111110", "01111111",
		"10000000", "10000001", "10000010", "10000011", "10000100", "10000101", "10000110", "10000111",
		"10001000", "10001001", "10001010", "10001011", "10001100", "10001101", "10001110", "10001111",
		"10010000", "10010001", "10010010", "10010011", "10010100", "10010101", "10010110", "10010111",
		"10011000", "10011001", "10011010", "10011011", "10011100", "10011101", "10011110", "10011111",
		"10100000", "10100001", "10100010", "10100011", "10100100", "10100101", "10100110", "10100111",
		"10101000", "10101001", "10101010", "10101011", "10101100", "10101101", "10101110", "10101111",
		"10110000", "10110001", "10110010", "10110011", "10110100", "10110101", "10110110", "10110111",
		"10111000", "10111001", "10111010", "10111011", "10111100", "10111101", "10111110", "10111111",
		"11000000", "11000001", "11000010", "11000011", "11000100", "11000101", "11000110", "11000111",
		"11001000", "11001001", "11001010", "11001011", "11001100", "11001101", "11001110", "11001111",
		"11010000", "11010001", "11010010", "11010011", "11010100", "11010101", "11010110", "11010111",
		"11011000", "11011001", "11011010", "11011011", "11011100", "11011101", "11011110", "11011111",
		"11100000", "11100001", "11100010", "11100011", "11100100", "11100101", "11100110", "11100111",
		"11101000", "11101001", "11101010", "11101011", "11101100", "11101101", "11101110", "11101111",
		"11110000", "11110001", "11110010", "11110011", "11110100", "11110101", "11110110", "11110111",
		"11111000", "11111001", "11111010", "11111011", "11111100", "11111101", "11111110", "11111111"
	};

	return BINARY_VALUES[byte];
}

const char *byte_to_octal(standard::uint8_t byte)
{
	static const char *const BINARY_VALUES[] = {
		"000", "001", "002", "003", "004", "005", "006", "007", "010", "011", "012", "013", "014", "015", "016", "017",
		"020", "021", "022", "023", "024", "025", "026", "027", "030", "031", "032", "033", "034", "035", "036", "037",
		"040", "041", "042", "043", "044", "045", "046", "047", "050", "051", "052", "053", "054", "055", "056", "057",
		"060", "061", "062", "063", "064", "065", "066", "067", "070", "071", "072", "073", "074", "075", "076", "077",
		"100", "101", "102", "103", "104", "105", "106", "107", "110", "111", "112", "113", "114", "115", "116", "117",
		"120", "121", "122", "123", "124", "125", "126", "127", "130", "131", "132", "133", "134", "135", "136", "137",
		"140", "141", "142", "143", "144", "145", "146", "147", "150", "151", "152", "153", "154", "155", "156", "157",
		"160", "161", "162", "163", "164", "165", "166", "167", "170", "171", "172", "173", "174", "175", "176", "177",
		"200", "201", "202", "203", "204", "205", "206", "207", "210", "211", "212", "213", "214", "215", "216", "217",
		"220", "221", "222", "223", "224", "225", "226", "227", "230", "231", "232", "233", "234", "235", "236", "237",
		"240", "241", "242", "243", "244", "245", "246", "247", "250", "251", "252", "253", "254", "255", "256", "257",
		"260", "261", "262", "263", "264", "265", "266", "267", "270", "271", "272", "273", "274", "275", "276", "277",
		"300", "301", "302", "303", "304", "305", "306", "307", "310", "311", "312", "313", "314", "315", "316", "317",
		"320", "321", "322", "323", "324", "325", "326", "327", "330", "331", "332", "333", "334", "335", "336", "337",
		"340", "341", "342", "343", "344", "345", "346", "347", "350", "351", "352", "353", "354", "355", "356", "357",
		"360", "361", "362", "363", "364", "365", "366", "367", "370", "371", "372", "373", "374", "375", "376", "377"
	};

	return BINARY_VALUES[byte];
}

const char *byte_to_hexadecimal(standard::uint8_t byte)
{
	static const char *const HEXADECIMAL_VALUES[] = {
		"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b", "0c", "0d", "0e", "0f",
		"10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1a", "1b", "1c", "1d", "1e", "1f",
		"20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f",
		"30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3a", "3b", "3c", "3d", "3e", "3f",
		"40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c", "4d", "4e", "4f",
		"50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a", "5b", "5c", "5d", "5e", "5f",
		"60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d", "6e", "6f",
		"70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a", "7b", "7c", "7d", "7e", "7f",
		"80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
		"90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b", "9c", "9d", "9e", "9f",
		"a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "aa", "ab", "ac", "ad", "ae", "af",
		"b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf",
		"c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "ca", "cb", "cc", "cd", "ce", "cf",
		"d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "da", "db", "dc", "dd", "de", "df",
		"e0", "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef",
		"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb", "fc", "fd", "fe", "ff"
	};

	return HEXADECIMAL_VALUES[byte];
}

}

