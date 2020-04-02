#include <algorithm>
#include <iterator>
#include <string>
#include "trace-out/detail/system/constants.hpp"
#include "trace-out/detail/stuff/constants.hpp"
#include "trace-out/detail/stuff/stuff.hpp"


#include <iostream>

namespace trace_out { namespace detail
{

	static const std::string::value_type NAMESPACE_DELIMITER[] = "::";
	static const std::string::value_type *NAMESPACE_DELIMITER_END = NAMESPACE_DELIMITER + (sizeof(NAMESPACE_DELIMITER) / sizeof(NAMESPACE_DELIMITER[0]) - 1);
	std::iterator_traits<std::string::const_iterator>::difference_type NAMESPACE_DELIMITER_LENGTH = sizeof(NAMESPACE_DELIMITER) / sizeof(std::string::value_type) - 1;


	bool is_delimiter(std::string::value_type character);

	template <typename Iterator>
	Iterator skip_components(Iterator first, Iterator last, std::size_t parent_component_count);

	std::string::iterator find_identifier_start(std::string::iterator first, std::string::iterator last, std::size_t parent_component_count);

}
}


namespace trace_out { namespace detail
{

	const std::string filename_from_path(const char *path)
	{
		std::string file_path(path);
		return file_path.substr(file_path.rfind(system::FILE_PATH_COMPONENT_DELIMITER) + 1);
	}


	const std::string filename_line_field(const std::string &file, unsigned long line)
	{
		std::stringstream stream;
		stream.fill(' ');

		stream.width(FILENAME_FIELD_WIDTH);
		stream.flags(std::ios::right);
		std::string filename = file;
		if (filename.length() > FILENAME_FIELD_WIDTH)
		{
			filename = filename.substr(0, FILENAME_FIELD_WIDTH - FILENAME_FIELD_EXCESS_PADDING_SIZE);
			filename += FILENAME_FIELD_EXCESS_PADDING;
		}

		stream << filename;

		stream.width(0);
		stream << ":";

		stream.width(LINE_FIELD_WIDTH);
		stream.flags(std::ios::left);
		stream << line;

		return stream.str();
	}


	void apply_io_manipulators(std::ostream &stream, va_list manipulators)
	{
		for (;;)
		{
			manipulator_t manipulator = va_arg(manipulators, manipulator_t);
			if (manipulator == NULL)
			{
				break;
			}

			stream << manipulator;
		}
	}


	std::string first_token(const std::string &tokens)
	{
		return tokens.substr(0, tokens.find(','));
	}


	std::string rest_tokens(const std::string &tokens)
	{
		standard::size_t from = tokens.find(',') + 1;
		while (tokens[from] == ' ')
		{
			++from;
		}

		return tokens.substr(from, tokens.size());
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
	Iterator skip_components(Iterator first, Iterator last, std::size_t parent_component_count)
	{
		for ( ; parent_component_count > 0; --parent_component_count)
		{
			first = std::search(first, last, NAMESPACE_DELIMITER, NAMESPACE_DELIMITER_END);
			if (first != last)
			{
				first += NAMESPACE_DELIMITER_LENGTH;
			}
		}

		return first;
	}


	std::string::const_iterator find_identifier_start(std::string::const_iterator first, std::string::const_iterator last, std::size_t parent_component_count)
	{
		std::iterator_traits<std::string::const_iterator>::difference_type dist = std::distance(first, last);
		std::string::const_reverse_iterator rfirst(first + dist);
		std::string::const_reverse_iterator rlast(last - dist);

		rfirst = skip_components(rfirst, rlast, parent_component_count);
		std::string::const_reverse_iterator place = std::search(rfirst, rlast, NAMESPACE_DELIMITER, NAMESPACE_DELIMITER_END);
		if (place == rlast)
		{
			return first;
		}

		return place.base();
	}


	std::string strip_namespaces(const std::string &line, std::size_t parent_namespace_count)
	{
		std::string stripped_string;
		for (std::string::const_iterator itr = line.begin(); itr != line.end(); )
		{
			std::string::const_iterator token_end = std::find_if(itr, line.end(), is_delimiter);
			std::string::const_iterator identifier_start = find_identifier_start(itr, token_end, parent_namespace_count);

			if (token_end != line.cend())
			{
				++token_end;
			}

			std::copy(identifier_start, token_end, std::back_inserter(stripped_string));

			itr = token_end;
		}

		return stripped_string;
	}

}
}

