#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <list>
#include <map>
#include <sstream>
#include <unordered_map>
#include <vector>

TEST_CASE("$tr(begin, end)", "[tr]")
{
	test::out_stream.str(std::string {});

	SECTION("std::vector empty")
	{
		std::vector<int> subject;

		$tr(subject.begin(), subject.end())

		const char *expected {"[subject.begin(), subject.end()) = []\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::vector non-empty")
	{
		std::vector<int> subject {1, 2, 3, 4, 5};

		$tr(subject.begin(), subject.end())

		const char *expected {"[subject.begin(), subject.end()) = [1, 2, 3, 4, 5]\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::list empty")
	{
		std::list<int> subject;

		$tr(subject.begin(), subject.end())

		const char *expected {"[subject.begin(), subject.end()) = []\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::list non-empty")
	{
		std::list<int> subject {1, 2, 3, 4, 5};

		$tr(subject.begin(), subject.end())

		const char *expected {"[subject.begin(), subject.end()) = [1, 2, 3, 4, 5]\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::map non-empty")
	{
		std::map<std::string, int> subject {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}};

		$tr(subject.begin(), subject.end())

		std::stringstream expected;
		expected << "[subject.begin(), subject.end()) = [\n";
		auto itr {subject.begin()};
		expected << "    {\"" << itr->first << "\", " << itr->second << '}';
		for (++itr; itr != subject.end(); ++itr)
		{
			expected << ",\n    {\"" << itr->first << "\", " << itr->second << '}';
		}
		expected << "\n]\n";
		REQUIRE(test::out_stream.str() == expected.str());
	}

	SECTION("std::unordered_map non-empty")
	{
		std::unordered_map<std::string, int> subject {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}};

		$tr(subject.begin(), subject.end())

		std::stringstream expected;
		expected << "[subject.begin(), subject.end()) = [\n";
		auto itr {subject.begin()};
		expected << "    {\"" <<itr->first << "\", " << itr->second << '}';
		for (++itr; itr != subject.end(); ++itr)
		{
			expected << ",\n    {\"" << itr->first << "\", " << itr->second << '}';
		}
		expected << "\n]\n";
		REQUIRE(test::out_stream.str() == expected.str());
	}
}

TEST_CASE("$tr(begin, how_much)", "[tr]")
{
	test::out_stream.str(std::string {});

	SECTION("std::vector empty")
	{
		std::vector<int> subject;

		$tr(subject.begin(), 0)

		const char *expected {"[subject.begin(): 0] = []\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::vector non-empty")
	{
		SECTION(".begin(), 0")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), 0)

			const char *expected {"[subject.begin(): 0] = []\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".begin(), 1")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), 1)

			const char *expected {"[subject.begin(): 1] = [1]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".begin(), 2")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), 2)

			const char *expected {"[subject.begin(): 2] = [1, 2]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".begin(), 4")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), 4)

			const char *expected {"[subject.begin(): 4] = [1, 2, 3, 4]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".begin(), 5")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), 5)

			const char *expected {"[subject.begin(): 5] = [1, 2, 3, 4, 5]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".begin(), (int)how_much")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};
			int how_much {3};

			$tr(subject.begin(), how_much)

			const char *expected {"[subject.begin(): 3] = [1, 2, 3]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION(".begin(), (std::size_t)how_much")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};
			std::size_t how_much {3};

			$tr(subject.begin(), how_much)

			const char *expected {"[subject.begin(): 3] = [1, 2, 3]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}
}

TEST_CASE("$tr(begin, end, how_much)", "[tr]")
{
	test::out_stream.str(std::string {});

	SECTION("std::vector empty")
	{
		SECTION("how_much = 0")
		{
			std::vector<int> subject;

			$tr(subject.begin(), subject.end(), 0)

			const char *expected {"[subject.begin(), subject.end()):0 = []\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("how_much = 1")
		{
			std::vector<int> subject;

			$tr(subject.begin(), subject.end(), 1)

			const char *expected {"[subject.begin(), subject.end()):1 = []\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("how_much = 2")
		{
			std::vector<int> subject;

			$tr(subject.begin(), subject.end(), 2)

			const char *expected {"[subject.begin(), subject.end()):2 = []\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}

	SECTION("std::vector non-empty")
	{
		SECTION("how_much == 0")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), subject.end(), 0)

			const char *expected {"[subject.begin(), subject.end()):0 = []\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("how_much == 1, how_much < .size()")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), subject.end(), 1)

			const char *expected {"[subject.begin(), subject.end()):1 = [1]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("how_much == 2, how_much < .size()")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), subject.end(), 2)

			const char *expected {"[subject.begin(), subject.end()):2 = [1, 2]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("how_much == .size() - 1")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), subject.end(), 4)

			const char *expected {"[subject.begin(), subject.end()):4 = [1, 2, 3, 4]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("how_much == .size()")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), subject.end(), 5)

			const char *expected {"[subject.begin(), subject.end()):5 = [1, 2, 3, 4, 5]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("how_much == .size() + 1")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), subject.end(), 6)

			const char *expected {"[subject.begin(), subject.end()):6 = [1, 2, 3, 4, 5]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}

		SECTION("how_much == .size() + 2")
		{
			std::vector<int> subject {1, 2, 3, 4, 5};

			$tr(subject.begin(), subject.end(), 7)

			const char *expected {"[subject.begin(), subject.end()):7 = [1, 2, 3, 4, 5]\n"};
			REQUIRE(test::out_stream.str() == expected);
		}
	}
}

