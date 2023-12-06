#include "dummy.hpp"
#include "trace-out/trace-out.hpp"

int main()
{$f
	$if (true)
	{
	}

	$if (true)
	{
	}

	$for ( ; false; )
	{
	}

	$for ( ; false; )
	{
	}

	$while (false)
	{
	}

	$while (false)
	{
	}

	$s(dummy();)
	$s(dummy();)

	$time("dummy", dummy();)
	$time("dummy", dummy();)

	$clocks("dummy", dummy();)
	$clocks("dummy", dummy();)

	$time_stats("dummy", 1, dummy();)
	$time_stats("dummy", 1, dummy();)

	$clock_stats("dummy", 1, dummy();)
	$clock_stats("dummy", 1, dummy();)

	$return 0;
	$return 0;
}

