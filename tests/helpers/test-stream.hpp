#pragma once

#include <ostream>

namespace trace_out_to_test_stream
{

extern std::ostream &stream();

}

namespace test
{

extern std::stringstream out_stream;

}

