#include "framework-library-component.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

TEST_CASE("'TRACE_OUT_STRIP_SCOPE=2' with nothing to strip", "[TRACE_OUT_STRIP_SCOPE][f]")
{
	test::out_stream.str(std::string {});

	SECTION("global scope")
	{
		func();

		const char *expected {
			"void func()\n"
			"{\n"
			"} // void func()\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("framework::")
	{
		framework::func({});

		const char *expected {
			"framework::type framework::func(framework::type)\n"
			"{\n"
			"} // framework::type framework::func(framework::type)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("::type")
	{
		func0({});

		const char *expected {
			"::type func0(::type)\n"
			"{\n"
			"} // ::type func0(::type)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("framework::library::")
	{
		framework::library::func({});

		const char *expected {
			"framework::library::type framework::library::func(framework::library::type)\n"
			"{\n"
			"} // framework::library::type framework::library::func(framework::library::type)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("::framework::")
	{
		func1({});

		const char *expected {
			"::framework::type func1(::framework::type)\n"
			"{\n"
			"} // ::framework::type func1(::framework::type)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

TEST_CASE("'TRACE_OUT_STRIP_SCOPE=2' with something to strip", "[TRACE_OUT_STRIP_SCOPE][f]")
{
	test::out_stream.str(std::string {});

	SECTION("framework::library::component::")
	{
		framework::library::component::func({});

		const char *expected {
			"library::component::type library::component::func(library::component::type)\n"
			"{\n"
			"} // library::component::type library::component::func(library::component::type)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}

	SECTION("::framework::library::")
	{
		func2({});

		const char *expected {
			"framework::library::type func2(framework::library::type)\n"
			"{\n"
			"} // framework::library::type func2(framework::library::type)\n"
			"\n"
		};
		REQUIRE(test::out_stream.str() == expected);
	}
}

