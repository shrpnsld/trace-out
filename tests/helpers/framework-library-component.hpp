#pragma once

#include "trace-out/trace-out.hpp"

namespace framework
{

using type = int;
framework::type func(framework::type) { $f return {}; }

}

namespace framework { namespace library
{

using type = int;
framework::library::type func(framework::library::type) { $f return {}; }

}
}

namespace framework { namespace library { namespace component
{

using type = int;
framework::library::component::type func(framework::library::component::type) { $f return {}; }

}
}
}

using type = int;

void func() { $f }
::type func0(::type) { $f return {}; }
::framework::type func1(::framework::type){ $f return {}; }
::framework::library::type func2(::framework::library::type){ $f return {}; }

