#include "dummy.hpp"
#include "trace-out.hpp"
#include <memory>
#include <optional>
#include <variant>

int main()
{$thread(main) $f
	int subject1 {456};
	float subject2 {789.123f};
	std::string subject3 {"hellomoto!"};
	std::unique_ptr<int> subject4 {new int {456}};
	std::optional<int> subject5 {789};
	std::variant<float, int> subject6 {789.123f};

	$t("hellomoto!");
	$t(subject1, subject2, subject3, subject4, subject5, subject6);
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

