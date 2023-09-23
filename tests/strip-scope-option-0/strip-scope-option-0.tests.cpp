#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

namespace framework
{

using type = int;
type func(type) { $f return {}; }

}

namespace framework { namespace library
{

using type = int;
type func(type) { $f return {}; }

}
}

namespace framework { namespace library { namespace component
{

using type = int;
type func(type) { $f return {}; }

}
}
}

using type = int;

void func() { $f }
::type func0(::type) { $f return {}; }
::framework::type func1(::framework::type){ $f return {}; }
::framework::library::type func2(::framework::library::type){ $f return {}; }

TEST_CASE("TRACE_OUT_STRIP_SCOPE=0 with nothing to strip", "[TRACE_OUT_STRIP_SCOPE][f]")
{
	test::stream.str(std::string {});

	func();

	const char *expected {
		"void func()\n"
		"{\n"
		"} // void func()\n"
		"\n"
	};
	REQUIRE(test::stream.str() == expected);
}

TEST_CASE("TRACE_OUT_STRIP_SCOPE=0 with something to strip", "[TRACE_OUT_STRIP_SCOPE][f]")
{
	test::stream.str(std::string {});

	SECTION("framework::")
	{
		framework::func({});

		const char *expected {
			"type func(type)\n"
			"{\n"
			"} // type func(type)\n"
			"\n"
		};
		REQUIRE(test::stream.str() == expected);
	}

	SECTION("::type")
	{
		func0({});

		const char *expected {
			"type func0(type)\n"
			"{\n"
			"} // type func0(type)\n"
			"\n"
		};
		REQUIRE(test::stream.str() == expected);
	}

	SECTION("framework::library::")
	{
		framework::library::func({});

		const char *expected {
			"type func(type)\n"
			"{\n"
			"} // type func(type)\n"
			"\n"
		};
		REQUIRE(test::stream.str() == expected);
	}

	SECTION("::framework::")
	{
		func1({});

		const char *expected {
			"type func1(type)\n"
			"{\n"
			"} // type func1(type)\n"
			"\n"
		};
		REQUIRE(test::stream.str() == expected);
	}

	SECTION("framework::library::component::")
	{
		framework::library::component::func({});

		const char *expected {
			"type func(type)\n"
			"{\n"
			"} // type func(type)\n"
			"\n"
		};
		REQUIRE(test::stream.str() == expected);
	}

	SECTION("::framework::library::")
	{
		func2({});

		const char *expected {
			"type func2(type)\n"
			"{\n"
			"} // type func2(type)\n"
			"\n"
		};
		REQUIRE(test::stream.str() == expected);
	}
}

