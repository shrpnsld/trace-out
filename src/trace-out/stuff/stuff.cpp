#include <algorithm>
#include <iterator>
#include <string>
#include "trace-out/system/constants.hpp"
#include "trace-out/stuff/constants.hpp"
#include "trace-out/stuff/stuff.hpp"


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

}
}

