#include "test-stream.hpp"
#include <sstream>

namespace test
{

std::stringstream out_stream;

std::ostream &stream()
{
	return out_stream;
}

}

