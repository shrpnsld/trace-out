#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <list>
#include <map>
#include <sstream>
#include <unordered_map>
#include <vector>

TEST_CASE("$r(begin, end)", "[r]")
{
	test::out_stream.str(std::string {});

	SECTION("std::vector empty")
	{
		std::vector<int> subject;

		$r(subject.begin(), subject.end())

		const char *expected {"[subject.begin(), subject.end()) = []\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::vector non-empty")
	{
		std::vector<int> subject {1, 2, 3, 4, 5};

		$r(subject.begin(), subject.end())

		const char *expected {"[subject.begin(), subject.end()) = [1, 2, 3, 4, 5]\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::list empty")
	{
		std::list<int> subject;

		$r(subject.begin(), subject.end())

		const char *expected {"[subject.begin(), subject.end()) = []\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::list non-empty")
	{
		std::list<int> subject {1, 2, 3, 4, 5};

		$r(subject.begin(), subject.end())

		const char *expected {"[subject.begin(), subject.end()) = [1, 2, 3, 4, 5]\n"};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::map non-empty")
	{
		std::map<std::string, int> subject {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}};

		$r(subject.begin(), subject.end())

		std::stringstream expected;
		expected << "[subject.begin(), subject.end()) = [";
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

		$r(subject.begin(), subject.end())

		std::stringstream expected;
		expected << "[subject.begin(), subject.end()) = [";
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

