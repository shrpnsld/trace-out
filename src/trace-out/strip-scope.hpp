#pragma once

#include "trace-out/integer.hpp"
#include <algorithm>
#include <iterator>
#include <string>

//
// Public

#if defined(TRACE_OUT_STRIP_SCOPE)
	#define trace_out_private__strip_scope(string) \
				trace_out::strip_scope(string, TRACE_OUT_STRIP_SCOPE)
#else
	#define trace_out_private__strip_scope(string) \
				string
#endif

//
// Private

namespace trace_out
{

static const std::string::value_type CPP_SCOPE_DELIMITER[] = "::";
static const std::string::value_type *CPP_SCOPE_DELIMITER_END = CPP_SCOPE_DELIMITER + (sizeof(CPP_SCOPE_DELIMITER) / sizeof(CPP_SCOPE_DELIMITER[0]) - 1);
static std::iterator_traits<std::string::const_iterator>::difference_type CPP_SCOPE_DELIMITER_LENGTH = sizeof(CPP_SCOPE_DELIMITER) / sizeof(std::string::value_type) - 1;

inline std::string strip_scope(const std::string &line, standard::size_t parent_scope_count = 0);
inline bool is_delimiter(std::string::value_type character);

template <typename Iterator>
Iterator skip_components(Iterator first, Iterator last, standard::size_t parent_component_count);

inline std::string::const_iterator find_identifier_start(std::string::const_iterator first, std::string::const_iterator last, standard::size_t parent_component_count);

}

//
// Implementation

namespace trace_out
{

std::string strip_scope(const std::string &line, standard::size_t parent_scope_count)
{
	std::string stripped_string;
	for (std::string::const_iterator itr = line.begin(); itr != line.end(); )
	{
		std::string::const_iterator token_end = std::find_if(itr, line.end(), is_delimiter);
		std::string::const_iterator identifier_start = find_identifier_start(itr, token_end, parent_scope_count);

		if (token_end != line.cend())
		{
			++token_end;
		}

		std::copy(identifier_start, token_end, std::back_inserter(stripped_string));

		itr = token_end;
	}

	return stripped_string;
}

bool is_delimiter(std::string::value_type character)
{
	switch (character)
	{
		case ' ':
		case '(':
		case ')':
		case '<':
		case '>':
		case '[':
		case ']':
			return true;

		default:
			return false;
	}
}

template <typename Iterator>
Iterator skip_components(Iterator first, Iterator last, standard::size_t parent_component_count)
{
	for ( ; parent_component_count > 0; --parent_component_count)
	{
		first = std::search(first, last, CPP_SCOPE_DELIMITER, CPP_SCOPE_DELIMITER_END);
		if (first != last)
		{
			first += CPP_SCOPE_DELIMITER_LENGTH;
		}
	}

	return first;
}

std::string::const_iterator find_identifier_start(std::string::const_iterator first, std::string::const_iterator last, standard::size_t parent_component_count)
{
	std::iterator_traits<std::string::const_iterator>::difference_type dist = std::distance(first, last);
	std::string::const_reverse_iterator rfirst(first + dist);
	std::string::const_reverse_iterator rlast(last - dist);

	rfirst = skip_components(rfirst, rlast, parent_component_count);
	std::string::const_reverse_iterator place = std::search(rfirst, rlast, CPP_SCOPE_DELIMITER, CPP_SCOPE_DELIMITER_END);
	if (place == rlast)
	{
		return first;
	}

	return place.base();
}

}
