#include "trace-out/trace-out.hpp"
#include "test-stream.hpp"
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
	test::out_stream.str(std::string {});

	SECTION("void subject_func1()")
	{
		subject_func1();

		const char *expected {
			"void subject_func1()\n"
			"{\n"
			"} // void subject_func1()\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("int subject_func2()")
	{
		subject_func2();

		const char *expected {
			"int subject_func2()\n"
			"{\n"
			"} // int subject_func2()\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("int subject_func3()")
	{
		subject_func3({});

		const char *expected {
			"void subject_func3(int)\n"
			"{\n"
			"} // void subject_func3(int)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("void subject_func4(double, char)")
	{
		subject_func4({}, {});

		const char *expected {
			"void subject_func4(double, char)\n"
			"{\n"
			"} // void subject_func4(double, char)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("void subject_func5(float, float, unsigned long *)")
	{
		subject_func5({}, {}, {});

		const char *expected {
			"void subject_func5(float, float, unsigned long *)\n"
			"{\n"
			"} // void subject_func5(float, float, unsigned long *)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::unique_ptr<std::string> subject_func6(const std::string &)")
	{
		subject_func6({});

		const char *expected {
			"std::unique_ptr<std::string> subject_func6(const std::string &)\n"
			"{\n"
			"} // std::unique_ptr<std::string> subject_func6(const std::string &)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("bool subject_func7(const char *, const char *)")
	{
		subject_func7({}, {});

		const char *expected {
			"bool subject_func7(const char *, const char *)\n"
			"{\n"
			"} // bool subject_func7(const char *, const char *)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::string subject_func8(const std::string &, std::size_t, char)")
	{
		subject_func8({}, {}, {});

		const char *expected {
			"std::string subject_func8(const std::string &, std::size_t, char)\n"
			"{\n"
			"} // std::string subject_func8(const std::string &, std::size_t, char)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("void subject_class::func1()")
	{
		subject_class inst;
		inst.func1();

		const char *expected {
			"void subject_class::func1()\n"
			"{\n"
			"} // void subject_class::func1()\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("int subject_class::func2()")
	{
		subject_class inst;
		inst.func2();

		const char *expected {
			"int subject_class::func2()\n"
			"{\n"
			"} // int subject_class::func2()\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("void subject_class::func3(int)")
	{
		subject_class inst;
		inst.func3({});

		const char *expected {
			"void subject_class::func3(int)\n"
			"{\n"
			"} // void subject_class::func3(int)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("void subject_class::func4(double, char)")
	{
		subject_class inst;
		inst.func4({}, {});

		const char *expected {
			"void subject_class::func4(double, char)\n"
			"{\n"
			"} // void subject_class::func4(double, char)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("void subject_class::func5(float, float, unsigned long *)")
	{
		subject_class inst;
		inst.func5({}, {}, {});

		const char *expected {
			"void subject_class::func5(float, float, unsigned long *)\n"
			"{\n"
			"} // void subject_class::func5(float, float, unsigned long *)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::unique_ptr<std::string> subject_class::func6(const std::string &)")
	{
		subject_class inst;
		inst.func6({});

		const char *expected {
			"std::unique_ptr<std::string> subject_class::func6(const std::string &)\n"
			"{\n"
			"} // std::unique_ptr<std::string> subject_class::func6(const std::string &)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("bool subject_class::func7(const char *, const char *)")
	{
		subject_class inst;
		inst.func7({}, {});

		const char *expected {
			"bool subject_class::func7(const char *, const char *)\n"
			"{\n"
			"} // bool subject_class::func7(const char *, const char *)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("std::string subject_class::func8(const std::string &, std::size_t, char)")
	{
		subject_class inst;
		inst.func8({}, {}, {});

		const char *expected {
			"std::string subject_class::func8(const std::string &, std::size_t, char)\n"
			"{\n"
			"} // std::string subject_class::func8(const std::string &, std::size_t, char)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

