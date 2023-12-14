#include "dollar-store-catch2.hpp"
#include <cassert>
#include <map>
#include <utility>

namespace dollar_store_catch2
{

typedef std::map<std::string, test_case_t> test_cases_t;

test_cases_t &test_cases()
{
	static std::map<std::string, test_case_t> value;

	return value;
}

std::string &current_running_test_name()
{
	static std::string value;

	return value;
}

std::string &current_running_section_name()
{
	static std::string value;

	return value;
}

std::string file_path_in_project(const std::string &project_root, const std::string &file_path)
{
	std::string::size_type place = file_path.find(project_root);
	if (place == 0)
	{
		return file_path.substr(project_root.size() + 1, file_path.size() - project_root.size());
	}
	else
	{
		return file_path;
	}
}

int add_test(const char *name, test_case_t function)
{
	test_cases().insert(std::make_pair(name, function));
	return 0;
}

void run_tests()
{
	assert(!test_cases().empty());

	for (test_cases_t::iterator itr = test_cases().begin(); itr != test_cases().end(); ++itr)
	{
		current_running_test_name() = itr->first;
		test_case_t function = itr->second;
		function();
	}
}

}

