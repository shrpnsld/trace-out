#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <iomanip>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

TEST_CASE("$t(value)", "[t]")
{
	test::out_stream.str(std::string {});

	SECTION("bool")
	{
		auto value = GENERATE(false, true);
		bool subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << std::boolalpha << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
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
		expected << "subject = " << std::get<1>(values) << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("const char *")
	{
		auto value = GENERATE("", "hellomoto!", "wazuuup!", "hello\nmoto!");
		const char *subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = \"" << subject << "\"\n";
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("std::string")
	{
		auto value = GENERATE("", "hellomoto!", "wazuuup!", "hello\nmoto!");
		std::string subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = \"" << subject << "\"\n";
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("signed char")
	{
		using type_t = signed char;

		auto value = GENERATE(123, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {static_cast<type_t>(value)};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << static_cast<signed int>(subject) << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("unsigned char")
	{
		using type_t = unsigned char;

		auto value = GENERATE(123, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {static_cast<type_t>(value)};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << static_cast<unsigned int>(subject) << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("short")
	{
		using type_t = short;

		auto value = GENERATE(0, 456, -789, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {static_cast<short>(value)};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("unsigned short")
	{
		using type_t = unsigned short;

		auto value = GENERATE(456, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {static_cast<type_t>(value)};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("int")
	{
		using type_t = int;

		auto value = GENERATE(0, 456, -789, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("unsigned int")
	{
		using type_t = unsigned int;

		auto value = GENERATE(456u, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("long")
	{
		using type_t = long;

		auto value = GENERATE(0l, 456l, -789l, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("unsigned long")
	{
		using type_t = unsigned long;

		auto value = GENERATE(456ul, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("long long")
	{
		using type_t = long long;

		auto value = GENERATE(456ll, -789ll, 0ll, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("unsigned long long")
	{
		using type_t = unsigned long long;

		auto value = GENERATE(456ull, 0ull, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("float")
	{
		using type_t = float;

		auto value = GENERATE(456.789f, -789.123f, 0.0f, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("double")
	{
		using type_t = double;

		auto value = GENERATE(456.789, -789.123, 0.0, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("long double")
	{
		using type_t = long double;

		auto value = GENERATE(456.789L, -789.123L, 0.0L, std::numeric_limits<type_t>::min(), std::numeric_limits<type_t>::max());
		type_t subject {value};

		$t(subject);

		std::stringstream expected;
		expected << "subject = " << subject << '\n';
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("const void *")
	{
		using type_t = const void *;
		type_t subject;

		SECTION("nullptr")
		{
			subject = nullptr;

			$t(subject);

			const char *expected {"subject = <null>\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("non-nullptr")
		{
			auto ptr = GENERATE(0xABADBABE, 0x0B00B135, 0xDEADBEEF, 0xFFFFFFFF);
			subject = reinterpret_cast<type_t>(ptr);

			$t(subject);

			std::stringstream expected;
			expected << "subject = " << subject << '\n';
			REQUIRE(test::out_stream.str() == expected.str());
		}
	}

	SECTION("void *")
	{
		using type_t = void *;
		type_t subject;

		SECTION("nullptr")
		{
			subject = nullptr;

			$t(subject);

			const char *expected {"subject = <null>\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("non-nullptr")
		{
			auto ptr = GENERATE(0xABADBABE, 0x0B00B135, 0xDEADBEEF, 0xFFFFFFFF);
			subject = reinterpret_cast<type_t>(ptr);

			$t(subject);

			std::stringstream expected;
			expected << "subject = " << subject << '\n';
			REQUIRE(test::out_stream.str() == expected.str());
		}
	}

	SECTION("const int *")
	{
		const int *subject;

		SECTION("nullptr")
		{
			subject = nullptr;

			$t(subject);

			const char *expected {"subject = <null>\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("non-nullptr")
		{
			int value {456};
			subject = &value;

			$t(subject);

			std::stringstream expected;
			expected << "subject = " << &value << " -> 456\n";
			REQUIRE(test::out_stream.str() == expected.str());
		}
	}

	SECTION("int *")
	{
		int *subject;

		SECTION("null pointer")
		{
			subject = nullptr;

			$t(subject);

			const char *expected {"subject = <null>\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("non-null pointer")
		{
			int value {456};
			subject = &value;

			$t(subject);

			std::stringstream expected;
			expected << "subject = " << &value << " -> 456\n";
			REQUIRE(test::out_stream.str() == expected.str());
		}
	}

	SECTION("const int[]")
	{
		const int subject[] = {456, 789, 123, 0, 1};

		$t(subject);

		const char *expected {"subject = [456, 789, 123, 0, 1]\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("int[]")
	{
		const int subject[] = {456, 789, 123, 0, 1};

		$t(subject);

		const char *expected {"subject = [456, 789, 123, 0, 1]\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("enum")
	{
		SECTION(": int")
		{
			enum numbers_t : int
			{
				minus_one = -1,
				zero,
				one,
				two,
				three
			};

			numbers_t subject1 {numbers_t::minus_one};
			numbers_t subject2 {numbers_t::two};

			$t(subject1);
			$t(subject2);

			const char *expected {
				"subject1 = -1\n"
				"subject2 = 2\n"
			};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(": unsigned int")
		{
			enum numbers_t : unsigned int
			{
				zero,
				one,
				two,
				three
			};

			numbers_t subject {numbers_t::one};

			$t(subject);

			const char *expected {"subject = 1\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(": unsigned long long int")
		{
			enum numbers_t : unsigned long long int
			{
				zero,
				one,
				two,
				the_biggest = std::numeric_limits<typename std::underlying_type<numbers_t>::type>::max()
			};

			numbers_t subject {numbers_t::the_biggest};

			$t(subject);

			std::stringstream expected;
			expected << "subject = " << numbers_t::the_biggest << '\n';
			REQUIRE(test::out_stream.str() == expected.str());
		}
	}

	SECTION("std::unique_ptr")
	{
		std::unique_ptr<int> subject;

		SECTION("nullptr")
		{
			subject.reset(nullptr);

			$t(subject);

			const char *expected {"subject = <null>\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("non-nullptr")
		{
			int value {456};
			subject.reset(new int {value});

			$t(subject);

			std::stringstream expected;
			expected << "subject = " << subject.get() << " -> 456\n";
			REQUIRE(test::out_stream.str() == expected.str());
		}
	}

	SECTION("std::shared_ptr")
	{
		std::shared_ptr<int> subject;

		SECTION("nullptr")
		{
			subject.reset();

			$t(subject);

			const char *expected {"subject = <null>\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("non-nullptr")
		{
			int value {456};
			subject.reset(new int {value});

			$t(subject);

			std::stringstream expected;
			expected << "subject = " << subject.get() << " (use_count: 1) -> 456\n";
			REQUIRE(test::out_stream.str() == expected.str());

			decltype(subject) another {subject};

			$t(subject);

			expected << "subject = " << subject.get() << " (use_count: 2) -> 456\n";
			REQUIRE(test::out_stream.str() == expected.str());
		}
	}

	SECTION("std::weak_ptr")
	{
		std::shared_ptr<int> ptr;

		SECTION("nullptr")
		{
			ptr.reset();
			std::weak_ptr<int> subject {ptr};

			$t(subject);

			const char *expected {"subject = (use_count: 0)\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("non-nullptr")
		{
			int value {456};
			ptr.reset(new int {value});
			std::weak_ptr<int> subject {ptr};

			$t(subject);

			const char *expected {"subject = (use_count: 1)\n"};
			REQUIRE(test::out_stream.str() == expected);

			decltype(ptr) another {ptr};

			$t(subject);

			expected =
				"subject = (use_count: 1)\n"
				"subject = (use_count: 2)\n";
			REQUIRE(test::out_stream.str() == expected);
		}
	}

	SECTION("std::pair")
	{
		std::pair<char, int> subject {'f', 456};

		$t(subject);

		const char *expected {"subject = {'f', 456}\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::tuple")
	{
		SECTION("<char>")
		{
			std::tuple<char> subject {'f'};

			$t(subject);

			const char *expected {"subject = {'f'}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("<int, float, std::string>")
		{
			std::tuple<int, float, std::string> subject {456, -789.123f, "hellomoto!"};

			$t(subject);

			const char *expected {"subject = {456, -789.123, \"hellomoto!\"}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}

	SECTION("std::bitset")
	{
		std::bitset<17> subject {0b01011001110001111};

		$t(subject);

		const char *expected {"subject = 01011001110001111\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION(".begin(), .end()")
	{
		SECTION("std::vector empty")
		{
			std::vector<int> subject;

			$t(subject);

			const char *expected {"subject = []\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("std::vector non-empty")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$t(subject);

			const char *expected {"subject = [1, 2, 3, 4, 5]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("std::list empty")
		{
			std::list<int> subject;

			$t(subject);

			const char *expected {"subject = []\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("std::list non-empty")
		{
			std::list<int> subject {1, 2, 3, 4, 5};

			$t(subject);

			const char *expected {"subject = [1, 2, 3, 4, 5]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("std::map non-empty")
		{
			std::map<std::string, int> subject {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}};

			$t(subject);

			std::stringstream expected;
			expected << "subject = [";

			auto itr {subject.begin()};
			expected << "{\"" << itr->first << "\", " << itr->second << '}';
			for (++itr; itr != subject.end(); ++itr)
			{
				expected << ", {\"" << itr->first << "\", " << itr->second << '}';
			}
			expected << "]\n";
			REQUIRE(test::out_stream.str() == expected.str());
		}

		SECTION("std::unordered_map non-empty")
		{
			std::unordered_map<std::string, int> subject {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}};

			$t(subject);

			std::stringstream expected;
			expected << "subject = [";

			auto itr {subject.begin()};
			expected << "{\"" << itr->first << "\", " << itr->second << '}';
			for (++itr; itr != subject.end(); ++itr)
			{
				expected << ", {\"" << itr->first << "\", " << itr->second << '}';
			}
			expected << "]\n";
			REQUIRE(test::out_stream.str() == expected.str());
		}
	}

	SECTION(".x .y")
	{
		SECTION(".x .y")
		{
			struct subject_t
			{
				int x, y;
			};

			subject_t subject {456, 789};

			$t(subject);

			const char *expected {"subject = {456, 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".X .Y")
		{
			struct subject_t
			{
				int X, Y;
			};

			subject_t subject {456, 789};

			$t(subject);

			const char *expected {"subject = {456, 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".x() .y()")
		{
			struct subject_t
			{
			public:
				subject_t(int x, int y) : _x {x}, _y {y} {}
				int x() const { return _x; }
				int y() const { return _y; }

			private:
				int _x, _y;
			};

			subject_t subject {456, 789};

			$t(subject);

			const char *expected {"subject = {456, 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".X() .Y()")
		{
			struct subject_t
			{
			public:
				subject_t(int x, int y) : _x {x}, _y {y} {}
				int X() const { return _x; }
				int Y() const { return _y; }

			private:
				int _x, _y;
			};

			subject_t subject {456, 789};

			$t(subject);

			const char *expected {"subject = {456, 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}

	SECTION(".x .y .z")
	{
		SECTION(".x .y .z")
		{
			struct subject_t
			{
				int x, y, z;
			};

			subject_t subject {123, 456, 789};

			$t(subject);

			const char *expected {"subject = {123, 456, 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".X .Y .Z")
		{
			struct subject_t
			{
				int X, Y, Z;
			};

			subject_t subject {123, 456, 789};

			$t(subject);

			const char *expected {"subject = {123, 456, 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".x() .y() .z()")
		{
			struct subject_t
			{
			public:
				subject_t(int x, int y, int z) : _x {x}, _y {y}, _z {z} {}
				int x() const { return _x; }
				int y() const { return _y; }
				int z() const { return _z; }

			private:
				int _x, _y, _z;
			};

			subject_t subject {123, 456, 789};

			$t(subject);

			const char *expected {"subject = {123, 456, 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".X() .Y() .Z()")
		{
			struct subject_t
			{
			public:
				subject_t(int x, int y, int z) : _x {x}, _y {y}, _z {z} {}
				int X() const { return _x; }
				int Y() const { return _y; }
				int Z() const { return _z; }

			private:
				int _x, _y, _z;
			};

			subject_t subject {123, 456, 789};

			$t(subject);

			const char *expected {"subject = {123, 456, 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}

	SECTION(".x .y .z .w")
	{
		SECTION(".x .y .z .w")
		{
			struct subject_t
			{
				int x, y, z, w;
			};

			subject_t subject {123, 456, 789, 987};

			$t(subject);

			const char *expected {"subject = {123, 456, 789, 987}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".X .Y .Z .W")
		{
			struct subject_t
			{
				int X, Y, Z, W;
			};

			subject_t subject {123, 456, 789, 987};

			$t(subject);

			const char *expected {"subject = {123, 456, 789, 987}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".x() .y() .z() .w()")
		{
			struct subject_t
			{
			public:
				subject_t(int x, int y, int z, int w) : _x {x}, _y {y}, _z {z}, _w {w} {}
				int x() const { return _x; }
				int y() const { return _y; }
				int z() const { return _z; }
				int w() const { return _w; }

			private:
				int _x, _y, _z, _w;
			};

			subject_t subject {123, 456, 789, 987};

			$t(subject);

			const char *expected {"subject = {123, 456, 789, 987}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".X() .Y() .Z() .W()")
		{
			struct subject_t
			{
			public:
				subject_t(int x, int y, int z, int w) : _x {x}, _y {y}, _z {z}, _w {w} {}
				int X() const { return _x; }
				int Y() const { return _y; }
				int Z() const { return _z; }
				int W() const { return _w; }

			private:
				int _x, _y, _z, _w;
			};

			subject_t subject {123, 456, 789, 987};

			$t(subject);

			const char *expected {"subject = {123, 456, 789, 987}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}

	SECTION(".width .height")
	{
		SECTION(".width .height")
		{
			struct subject_t
			{
				int width, height;
			};

			subject_t subject {456, 789};

			$t(subject);

			const char *expected {"subject = {456 x 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".Width .Height")
		{
			struct subject_t
			{
				int Width, Height;
			};

			subject_t subject {456, 789};

			$t(subject);

			const char *expected {"subject = {456 x 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".width() .height()")
		{
			struct subject_t
			{
			public:
				subject_t(int width, int height) : _width {width}, _height {height} {}
				int width() const { return _width; }
				int height() const { return _height; }

			private:
				int _width, _height;
			};

			subject_t subject {456, 789};

			$t(subject);

			const char *expected {"subject = {456 x 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".Width() .Height()")
		{
			struct subject_t
			{
			public:
				subject_t(int width, int height) : _width {width}, _height {height} {}
				int Width() const { return _width; }
				int Height() const { return _height; }

			private:
				int _width, _height;
			};

			subject_t subject {456, 789};

			$t(subject);

			const char *expected {"subject = {456 x 789}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}

	SECTION(".x .y .width .height")
	{
		SECTION(".x .y .width .height")
		{
			struct subject_t
			{
				int x, y, width, height;
			};

			subject_t subject {12, 34, 56, 78};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".x .y .Width .Height")
		{
			struct subject_t
			{
				int x, y, Width, Height;
			};

			subject_t subject {12, 34, 56, 78};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".X .Y .Width .Height")
		{
			struct subject_t
			{
				int X, Y, Width, Height;
			};

			subject_t subject {12, 34, 56, 78};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("x() y() .width() .height()")
		{
			struct subject_t
			{
			public:
				subject_t(int x, int y, int width, int height) : _x{x}, _y {y}, _width {width}, _height {height} {}
				int x() const { return _x; }
				int y() const { return _y; }
				int width() const { return _width; }
				int height() const { return _height; }

			private:
				int _x, _y, _width, _height;
			};

			subject_t subject {12, 34, 56, 78};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".x() .y() .Width() .Height()")
		{
			struct subject_t
			{
			public:
				subject_t(int x, int y, int width, int height) : _x{x}, _y {y}, _width {width}, _height {height} {}
				int x() const { return _x; }
				int y() const { return _y; }
				int Width() const { return _width; }
				int Height() const { return _height; }

			private:
				int _x, _y, _width, _height;
			};

			subject_t subject {12, 34, 56, 78};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".X() .Y() .Width() .Height()")
		{
			struct subject_t
			{
			public:
				subject_t(int x, int y, int width, int height) : _x{x}, _y {y}, _width {width}, _height {height} {}
				int X() const { return _x; }
				int Y() const { return _y; }
				int Width() const { return _width; }
				int Height() const { return _height; }

			private:
				int _x, _y, _width, _height;
			};

			subject_t subject {12, 34, 56, 78};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
  }

	SECTION(".origin .size")
	{
		SECTION(".x .y .width .height")
		{
			struct xy_t
			{
				int x, y;
			};

			struct wh_t
			{
				int width, height;
			};

			struct subject_t
			{
				xy_t origin;
				wh_t size;
			};

			subject_t subject {{12, 34}, {56, 78}};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".x .y .Width .Height")
		{
			struct xy_t
			{
				int x, y;
			};

			struct wh_t
			{
				int Width, Height;
			};

			struct subject_t
			{
				xy_t origin;
				wh_t size;
			};

			subject_t subject {{12, 34}, {56, 78}};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".X .Y .Width .Height")
		{
			struct xy_t
			{
				int X, Y;
			};

			struct wh_t
			{
				int Width, Height;
			};

			struct subject_t
			{
				xy_t origin;
				wh_t size;
			};

			subject_t subject {{12, 34}, {56, 78}};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".x() .y() .width() .height()")
		{
			struct xy_t
			{
			public:
				xy_t(int x, int y) : _x {x}, _y {y} {}
				int x() const { return _x; }
				int y() const { return _y; }

			private:
				int _x, _y;
			};

			struct wh_t
			{
			public:
				wh_t(int width, int height) : _width {width}, _height {height} {}
				int width() const { return _width; }
				int height() const { return _height; }

			private:
				int _width, _height;
			};

			struct subject_t
			{
				xy_t origin;
				wh_t size;
			};

			subject_t subject {{12, 34}, {56, 78}};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".x() .y() .Width() .Height()")
		{
			struct xy_t
			{
			public:
				xy_t(int x, int y) : _x {x}, _y {y} {}
				int x() const { return _x; }
				int y() const { return _y; }

			private:
				int _x, _y;
			};

			struct wh_t
			{
			public:
				wh_t(int width, int height) : _width {width}, _height {height} {}
				int Width() const { return _width; }
				int Height() const { return _height; }

			private:
				int _width, _height;
			};

			struct subject_t
			{
				xy_t origin;
				wh_t size;
			};

			subject_t subject {{12, 34}, {56, 78}};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".X() .Y() .Width() .Height()")
		{
			struct xy_t
			{
			public:
				xy_t(int x, int y) : _x {x}, _y {y} {}
				int X() const { return _x; }
				int Y() const { return _y; }

			private:
				int _x, _y;
			};

			struct wh_t
			{
			public:
				wh_t(int width, int height) : _width {width}, _height {height} {}
				int Width() const { return _width; }
				int Height() const { return _height; }

			private:
				int _width, _height;
			};

			struct subject_t
			{
				xy_t origin;
				wh_t size;
			};

			subject_t subject {{12, 34}, {56, 78}};

			$t(subject);

			const char *expected {"subject = {12, 34} {56 x 78}\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}

	SECTION(".real .imag")
	{
		struct subject_t
		{
			int real, imag;
		};

		subject_t subject {456, -789};

		$t(subject);

		const char *expected {"subject = {456, -789}\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION(".cx .cy")
	{
		struct subject_t
		{
			int cx, cy;
		};

		subject_t subject {456, -789};

		$t(subject);

		const char *expected {"subject = {456 x -789}\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION(".left .top .right .bottom")
	{
		struct subject_t
		{
			int left, top, right, bottom;
		};

		subject_t subject {12, 34, 56, 78};

		$t(subject);

		const char *expected {"subject = {12, 34} {56 x 78}\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

// TODO: do :)
//	SECTION(".v1 .v2")
//	{
//	}
//
//	SECTION(".Origin .Direction")
//	{
//	}
//
//	SECTION(".Vertex .Count")
//	{
//	}
//
//	SECTION(".Pitch .Roll .Yaw")
//	{
//	}
//
//	SECTION(".GetLowerBound .GetUpperBound")
//	{
//	}
//
//	SECTION(".GetValue .IsExclusive .IsInclusive .IsOpen")
//	{
//	}
//
//	SECTION(".Min .Max .bIsValid")
//	{
//	}
//
//	SECTION(".Center .W")
//	{
//	}
//
//	SECTION(".Center .Radius .Orientation .Length")
//	{
//	}
//
//	SECTION(".Center .AxisX .AxisY .AxisZ .ExtentX .ExtentY .ExtentZ")
//	{
//	}
//
//	SECTION(".Origin .BoxExtent .SphereRadius")
//	{
//	}
//
//	SECTION(".GetCharArray")
//	{
//	}

	SECTION("unknown type")
	{
		struct unknown_t
		{
		} subject;

		$t(subject);

		REQUIRE(test::out_stream.str() == "subject = <unknown-type>\n");
	}
}

TEST_CASE("$t(<values>...)", "[t]")
{
	test::out_stream.str(std::string {});

	int subject1 {456};
	float subject2 {789.1234f};
	std::string subject3 {"hellomoto!"};

	$t(subject1, subject2, subject3);

	const char *expected {
		"subject1 = 456\n"
		"subject2 = 789.123\n"
		"subject3 = \"hellomoto!\"\n"
		"\n"
	};
	REQUIRE(test::out_stream.str() == expected);
}

