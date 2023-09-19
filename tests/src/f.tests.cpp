#include "trace-out/trace-out.hpp"
#include "helpers/test-stream.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <memory>
#include <string>

void subject_func1() {$f}
int subject_func2() {$f return {}; }
void subject_func3(int) {$f}
void subject_func4(double, char) {$f}
void subject_func5(float, float, unsigned long *) {$f}
std::unique_ptr<std::string> subject_func6(const std::string &) {$f return {}; }
bool subject_func7(const char *, const char *) {$f return {}; }
std::string subject_func8(const std::string &, std::size_t, char) {$f return {}; }

class subject_class
{
public:
	void func1() {$f}
	int func2() {$f return {}; }
	void func3(int) {$f}
	void func4(double, char) {$f}
	void func5(float, float, unsigned long *) {$f}
	std::unique_ptr<std::string> func6(const std::string &) {$f return {}; }
	bool func7(const char *, const char *) {$f return {}; }
	std::string func8(const std::string &, std::size_t, char) {$f return {}; }
};

TEST_CASE("$f", "[f]")
{
	test::stream.str(std::string {});
	std::stringstream expected;

	SECTION("void subject_func1()")
	{
		subject_func1();
		expected <<
R"(void subject_func1()
{
} // void subject_func1()
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("int subject_func2()")
	{
		subject_func2();
		expected <<
R"(int subject_func2()
{
} // int subject_func2()
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("int subject_func3()")
	{
		subject_func3({});
		expected <<
R"(void subject_func3(int)
{
} // void subject_func3(int)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("void subject_func4(double, char)")
	{
		subject_func4({}, {});
		expected <<
R"(void subject_func4(double, char)
{
} // void subject_func4(double, char)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("void subject_func5(float, float, unsigned long *)")
	{
		subject_func5({}, {}, {});
		expected <<
R"(void subject_func5(float, float, unsigned long *)
{
} // void subject_func5(float, float, unsigned long *)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("std::unique_ptr<std::string> subject_func6(const std::string &)")
	{
		subject_func6({});
		expected <<
R"(std::unique_ptr<std::string> subject_func6(const std::string &)
{
} // std::unique_ptr<std::string> subject_func6(const std::string &)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("bool subject_func7(const char *, const char *)")
	{
		subject_func7({}, {});
		expected <<
R"(bool subject_func7(const char *, const char *)
{
} // bool subject_func7(const char *, const char *)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("std::string subject_func8(const std::string &, std::size_t, char)")
	{
		subject_func8({}, {}, {});
		expected <<
R"(std::string subject_func8(const std::string &, std::size_t, char)
{
} // std::string subject_func8(const std::string &, std::size_t, char)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("void subject_class::func1()")
	{
		subject_class inst;
		inst.func1();
		expected <<
R"(void subject_class::func1()
{
} // void subject_class::func1()
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("int subject_class::func2()")
	{
		subject_class inst;
		inst.func2();
		expected <<
R"(int subject_class::func2()
{
} // int subject_class::func2()
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("void subject_class::func3(int)")
	{
		subject_class inst;
		inst.func3({});
		expected <<
R"(void subject_class::func3(int)
{
} // void subject_class::func3(int)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("void subject_class::func4(double, char)")
	{
		subject_class inst;
		inst.func4({}, {});
		expected <<
R"(void subject_class::func4(double, char)
{
} // void subject_class::func4(double, char)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("void subject_class::func5(float, float, unsigned long *)")
	{
		subject_class inst;
		inst.func5({}, {}, {});
		expected <<
R"(void subject_class::func5(float, float, unsigned long *)
{
} // void subject_class::func5(float, float, unsigned long *)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("std::unique_ptr<std::string> subject_class::func6(const std::string &)")
	{
		subject_class inst;
		inst.func6({});
		expected <<
R"(std::unique_ptr<std::string> subject_class::func6(const std::string &)
{
} // std::unique_ptr<std::string> subject_class::func6(const std::string &)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("bool subject_class::func7(const char *, const char *)")
	{
		subject_class inst;
		inst.func7({}, {});
		expected <<
R"(bool subject_class::func7(const char *, const char *)
{
} // bool subject_class::func7(const char *, const char *)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}

	SECTION("std::string subject_class::func8(const std::string &, std::size_t, char)")
	{
		subject_class inst;
		inst.func8({}, {}, {});
		expected <<
R"(std::string subject_class::func8(const std::string &, std::size_t, char)
{
} // std::string subject_class::func8(const std::string &, std::size_t, char)
)" << std::endl;
		REQUIRE(test::stream.str() == expected.str());
	}
}

