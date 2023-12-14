#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

//
// Public

#define TEST_CASE(name) \
	DOLLAR_STORE_CATCH2_PRIVATE__DECLARE_AND_REGISTER_TEST_CASE(name, DOLLAR_STORE_CATCH2_PRIVATE__CONCAT(dollar_store_catch2__enabler, __COUNTER__), DOLLAR_STORE_CATCH2_PRIVATE__CONCAT(dollar_store_catch2__test_case_function, __COUNTER__))

#define SECTION(name) \
	dollar_store_catch2::current_running_section_name() = name;

#define REQUIRE(...) \
	if (!(__VA_ARGS__)) \
	{ \
		std::cerr \
			<< "Test '" << dollar_store_catch2::current_running_test_name() \
			<< "', section '" << dollar_store_catch2::current_running_section_name() \
			<< "' failed at " << dollar_store_catch2::file_path_in_project(DOLLAR_STORE_CATCH2__PROJECT_ROOT_DIR, __FILE__) << ':' << __LINE__ << "\n" \
			<< "  '" << #__VA_ARGS__ << '\'' \
			<< std::endl; \
		std::exit(1); \
	}

//
// Private

#define DOLLAR_STORE_CATCH2_PRIVATE__CONCAT_IMPL(left, right) \
	left##right

#define DOLLAR_STORE_CATCH2_PRIVATE__CONCAT(left, right) \
	DOLLAR_STORE_CATCH2_PRIVATE__CONCAT_IMPL(left, right)

#define DOLLAR_STORE_CATCH2_PRIVATE__ID(name) \
	DOLLAR_STORE_CATCH2_PRIVATE__CONCAT(name, __COUNTER__)

#define DOLLAR_STORE_CATCH2_PRIVATE__DECLARE_AND_REGISTER_TEST_CASE(name, enabler, function) \
	static void function(); \
	static int enabler = dollar_store_catch2::add_test(name, function); \
	void function()

namespace dollar_store_catch2
{

typedef void (*test_case_t)();

std::string file_path_in_project(const std::string &project_root, const std::string &file_path);
int add_test(const char *name, test_case_t function);
void run_tests();
std::string &current_running_test_name();
std::string &current_running_section_name();

}

