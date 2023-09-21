#pragma once

#include "trace-out/standard/integer.hpp"
#include "trace-out/stuff/platform-detection.hpp"
#include <ios>
#include <sstream>
#include <string>

//
// Public

#define TRACE_OUT_FILENAME_LINE \
			(trace_out::filename_line_field(trace_out::filename_from_path(__FILE__), static_cast<unsigned long>(__LINE__)))

namespace trace_out
{

inline const std::string filename_from_path(const char *path);
inline const std::string filename_line_field(const std::string &file, unsigned long line);

}

//
// Private

namespace trace_out
{

static const char FILENAME_FIELD_EXCESS_PADDING[] = "~";
static const standard::size_t FILENAME_FIELD_EXCESS_PADDING_SIZE = sizeof(FILENAME_FIELD_EXCESS_PADDING);
static const standard::size_t FILENAME_FIELD_WIDTH = 20;
static const standard::size_t LINE_FIELD_WIDTH = 4;

static const char FILE_PATH_COMPONENT_DELIMITER =
#if defined(TRACE_OUT_POSIX)
	'/'
#elif defined(TRACE_OUT_WINDOWS)
	'\\'
#endif
	;

}

//
// Implementation

namespace trace_out
{

const std::string filename_from_path(const char *path)
{
	std::string file_path(path);
	return file_path.substr(file_path.rfind(FILE_PATH_COMPONENT_DELIMITER) + 1);
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

}

