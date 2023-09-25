#pragma once

#include "fit.hpp"
#include "trace-out/trace-out.hpp"

namespace framework
{

using type = int;
framework::type func(framework::type) { $f return fit(); }

}

namespace framework { namespace library
{

using type = int;
framework::library::type func(framework::library::type) { $f return fit(); }

}
}

namespace framework { namespace library { namespace component
{

using type = int;
framework::library::component::type func(framework::library::component::type) { $f return fit(); }

}
}
}

using type = int;

void func() { $f }
::type func0(::type) { $f return fit(); }
::framework::type func1(::framework::type){ $f return fit(); }
::framework::library::type func2(::framework::library::type){ $f return fit(); }

