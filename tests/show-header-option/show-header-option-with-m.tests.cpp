#include "dummy.hpp"
#include "test-stream.hpp"
#include "trace-out/trace-out.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("'TRACE_OUT_SHOW_HEADER' with '$m(...)'", "[TRACE_OUT_SHOW_HEADER][m]")
{
	using Catch::Matchers::Matches;

	test::out_stream.str(std::string {});

	const char *what {"hellomoto!"};
	std::size_t size {std::strlen(what) + 1};
	$m(what, size)

	REQUIRE_THAT(test::out_stream.str(), Matches(
		R"=(#### \[ [0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2} \] #########################################\n)="
		R"=(\n)="
		R"=(what, 11 bytes of 1-byte hexadecimal\n)="
		R"=(    [0-9a-f]+: 68 65 6c 6c 6f 6d 6f 74  hellomot\n)="
		R"=(    [0-9a-f]+: 6f 21 00                 o!\.\n)="
		R"=(\n)="
	));
}

