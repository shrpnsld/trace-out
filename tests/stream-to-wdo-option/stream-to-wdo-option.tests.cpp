#include "dummy.hpp"
#include "trace-out/trace-out.hpp"

int main()
{
	$thread(main)
	$f

	int subject1 = 456;
	float subject2 = 789.123f;
	std::string subject3 = "hellomoto!";

	$t("hellomoto!");
	$t(subject1);
	$t(subject2);
	$t(subject3);
	$tbin(subject1);
	$toct(subject1);
	$thex(subject1);
	$tbin(subject2);
	$toct(subject2);
	$thex(subject2);
	$tr(subject3.begin(), subject3.end())
	$m(subject3.c_str(), subject3.size(), $hex, $grp(1), $col(8))
	$s(subject3 = "wazuuup!";)

	$if (true)
	{
	}

	$for (;;)
	{
		break;
	}

	$while(true)
	{
		break;
	}

	$time("dummy", dummy();)
	$clocks("dummy", dummy();)
	$time_stats("dummy", 1, dummy();)
	$clock_stats("dummy", 1, dummy();)

	$return 0;
}

