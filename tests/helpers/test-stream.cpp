#include "test-stream.hpp"
#include <sstream>

namespace trace_out_to_test_stream
{

std::ostream &stream()
{
	return test::out_stream;
}

}

namespace test
{

std::stringstream out_stream;

}

