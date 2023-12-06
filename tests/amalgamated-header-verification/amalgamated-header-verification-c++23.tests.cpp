#include "dummy.hpp"
#include "trace-out.hpp"
#include <memory>
#include <optional>
#include <variant>
#include <expected>

int main()
{$thread(main) $f
	int subject1 {456};
	float subject2 {789.123f};
	std::string subject3 {"hellomoto!"};
	std::unique_ptr<int> subject4 {new int {456}};
	std::optional<int> subject5 {789};
	std::variant<float, int> subject6 {789.123f};
	std::expected<int, std::string> subject7 {std::unexpected {"you smell!"}};

	$t("hellomoto!");
	$t(subject1, subject2, subject3, subject4, subject5, subject6, subject7);
	$tbin(subject1);
	$toct(subject1);
	$thex(subject1);
	$tbin(subject2);
	$toct(subject2);
	$thex(subject2);
	$tbin(subject1, subject2);
	$toct(subject1, subject2);
	$thex(subject1, subject2);
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

