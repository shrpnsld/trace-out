#pragma once

#include "trace-out/autolock.hpp"
#include "trace-out/console.hpp"
#include "trace-out/current-thread-name.hpp"
#include "trace-out/date-time.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/mutex.hpp"
#include "trace-out/platform-detection.hpp"
#include "trace-out/styles.hpp"
#include "trace-out/thread.hpp"
#include "trace-out/thread-local-storage.hpp"
#include <iomanip>
#include <ostream>
#include <string>
#include <sstream>

//
// Public

#define TRACE_OUT_FILE_LINE \
			(trace_out::file_line_t(__FILE__, static_cast<unsigned long>(__LINE__)))

namespace trace_out
{

struct file_line_t
{
	inline file_line_t(const char *path, unsigned long line);

	const std::string path;
	const unsigned long line;

	static inline std::string blank();
};

struct NEW_PARAGRAPH
{
	inline explicit NEW_PARAGRAPH(const file_line_t &filename_line);

	const file_line_t &filename_line;
};

static struct reset_flags_t {} RESET_FLAGS;
static struct start_header_t {} START_HEADER;
static struct thread_info_t {} THREAD_INFO;
static struct marker_t {} MARKER;
static const std::string DATE_TIME_BLANK = "                   ";
static const std::string FILE_LINE_BLANK = file_line_t::blank();
static struct continue_paragraph_t {} CONTINUE_PARAGRAPH;
static struct break_paragraph_t {} BREAK_PARAGRAPH;

inline system::mutex &stream_mutex();
inline std::ostream &operator <<(std::ostream &stream, reset_flags_t);
inline std::ostream &operator <<(std::ostream &stream, start_header_t);
inline std::ostream &operator <<(std::ostream &stream, thread_info_t);
inline std::ostream &operator <<(std::ostream &stream, marker_t);
inline std::ostream &operator <<(std::ostream &stream, const file_line_t &filename_line);
inline std::ostream &operator <<(std::ostream &stream, const NEW_PARAGRAPH &paragraph);
inline std::ostream &operator <<(std::ostream &stream, continue_paragraph_t);
inline std::ostream &operator <<(std::ostream &stream, break_paragraph_t);

}

//
// Private

namespace trace_out
{

static const standard::size_t FILENAME_FIELD_WIDTH = 20;
static const standard::size_t LINE_FIELD_WIDTH = 4;
static const char TIME_SPACE_CONTEXT_DELIMITER[] = " | ";

static const char FILENAME_FIELD_EXCESS_PADDING[] = "~";
static const standard::size_t FILENAME_FIELD_EXCESS_PADDING_SIZE = sizeof(FILENAME_FIELD_EXCESS_PADDING);

static const char FILE_PATH_COMPONENT_DELIMITER =
#if defined(TRACE_OUT_POSIX)
	'/'
#elif defined(TRACE_OUT_WINDOWS)
	'\\'
#endif
	;

static system::mutex _is_header_printed_mutex;
static bool _is_header_printed = false;
inline bool is_header_printed();
inline void set_header_printed();

static system::tls<bool> _is_paragraph_broken;
inline bool is_paragraph_broken();
inline void set_paragraph_broken(bool value);
inline const std::string filename_from_path(const char *path);

}

//
// Implementation

namespace trace_out
{

NEW_PARAGRAPH::NEW_PARAGRAPH(const file_line_t &filename_line)
	:
	filename_line(filename_line)
{
}

file_line_t::file_line_t(const char *path, unsigned long line)
	:
	path(filename_from_path(path)),
	line(line)
{
}

std::string file_line_t::blank()
{
	std::stringstream stream;
	stream.fill(' ');
	stream.width(FILENAME_FIELD_WIDTH + 1 + LINE_FIELD_WIDTH);
	stream << "" << RESET_FLAGS;
	return stream.str();
}

system::mutex &stream_mutex()
{
	static system::mutex _mutex;

	return _mutex;
}

std::ostream &operator <<(std::ostream &stream, reset_flags_t)
{
	stream.flags(static_cast<std::ios_base::fmtflags>(0));
	stream.width(0);
	stream.fill(' ');
	stream.precision(6);
	return stream;
}

std::ostream &operator <<(std::ostream &stream, start_header_t)
{
	(void)stream;

#if defined(TRACE_OUT_SHOW_HEADER)
	if (is_header_printed())
	{
		return stream;
	}

	standard::size_t header_width = 0;

	stream << "#### [";
	header_width += 6;

	std::string date_time = date_time_now();
	stream << ' ' << styles::STRING << date_time << styles::NORMAL;
	header_width += 1 + date_time.size();

#if defined(TRACE_OUT_SHOW_HEADER_TARGET)
	stream << ' ' << styles::SUBJECT << TRACE_OUT_SHOW_HEADER_TARGET << styles::NORMAL;
	header_width += 1 + std::strlen(TRACE_OUT_SHOW_HEADER_TARGET);
#endif // defined(TRACE_OUT_SHOW_HEADER_TARGET)

	stream << " ] ";
	header_width += 3;

	standard::size_t console_width = system::console_width();
	standard::size_t fill_width = console_width > header_width ? console_width - header_width : 4;
	stream << std::setw(fill_width) << std::setfill('#') << "" << RESET_FLAGS << "\n\n";
	set_header_printed();
#endif // defined(TRACE_OUT_SHOW_HEADER)

	return stream;
}

std::ostream &operator <<(std::ostream &stream, thread_info_t)
{
	(void)stream;

#if defined(TRACE_OUT_SHOW_THREAD)
	if (is_running_same_thread())
	{
		return stream;
	}

	const std::string &thread_name = current_thread_name();
	stream << MARKER << styles::THREAD << "~~~~[Thread: " << std::setbase(16) << system::current_thread_id() << RESET_FLAGS << (!thread_name.empty() ? " " : "") << thread_name << "]~~~~" << styles::NORMAL;
	stream << std::endl;
#endif

	return stream;
}

std::ostream &operator <<(std::ostream &stream, marker_t)
{
#if defined(TRACE_OUT_MARKER)
	stream << TRACE_OUT_MARKER " ";
#endif

	return stream;
}

std::ostream &operator <<(std::ostream &stream, const file_line_t &filename_line)
{
	stream.fill(' ');

	stream.width(FILENAME_FIELD_WIDTH);
	stream.flags(std::ios::right);
	std::string filename = filename_line.path;
	if (filename.length() > FILENAME_FIELD_WIDTH)
	{
		filename = filename.substr(0, FILENAME_FIELD_WIDTH - FILENAME_FIELD_EXCESS_PADDING_SIZE);
		filename += FILENAME_FIELD_EXCESS_PADDING;
	}

	stream << filename;

	stream.width(0);
	stream << styles::COMMENT << ':' << styles::NORMAL;

	stream.width(LINE_FIELD_WIDTH);
	stream.flags(std::ios::left);
	stream << filename_line.line;

	stream << RESET_FLAGS;

	return stream;
}

std::ostream &operator <<(std::ostream &stream, const NEW_PARAGRAPH &paragraph)
{
	(void)paragraph;

	stream << MARKER;

#if defined(TRACE_OUT_SHOW_DATE_TIME)
	stream << date_time_now();
#endif

#if defined(TRACE_OUT_SHOW_DATE_TIME) && defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << ' ';
#endif

#if defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << paragraph.filename_line;
#endif

#if defined(TRACE_OUT_SHOW_DATE_TIME) || defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << styles::COMMENT << TIME_SPACE_CONTEXT_DELIMITER << styles::NORMAL;
#endif

	set_paragraph_broken(false);

	return stream << indentation();
}

std::ostream &operator <<(std::ostream &stream, continue_paragraph_t)
{
	stream << MARKER;

#if defined(TRACE_OUT_SHOW_DATE_TIME)
	stream << DATE_TIME_BLANK;
#endif

#if defined(TRACE_OUT_SHOW_DATE_TIME) && defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << ' ';
#endif

#if defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << FILE_LINE_BLANK;
#endif

#if defined(TRACE_OUT_SHOW_DATE_TIME) || defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << styles::COMMENT << TIME_SPACE_CONTEXT_DELIMITER << styles::NORMAL;
#endif

	set_paragraph_broken(false);

	return stream << indentation();
}

std::ostream &operator <<(std::ostream &stream, break_paragraph_t)
{
	if (is_paragraph_broken())
	{
		return stream;
	}

	stream << MARKER;

#if defined(TRACE_OUT_SHOW_DATE_TIME)
	stream << DATE_TIME_BLANK;
#endif

#if defined(TRACE_OUT_SHOW_DATE_TIME) && defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << ' ';
#endif

#if defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << FILE_LINE_BLANK;
#endif

#if defined(TRACE_OUT_SHOW_DATE_TIME) || defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << styles::COMMENT << TIME_SPACE_CONTEXT_DELIMITER << styles::NORMAL;
#endif

	set_paragraph_broken(true);

	return stream << std::endl;
}

bool is_header_printed()
{
	autolock<system::mutex> lock(_is_header_printed_mutex);
	return _is_header_printed;
}

void set_header_printed()
{
	autolock<system::mutex> lock(_is_header_printed_mutex);
	_is_header_printed = true;
}

bool is_paragraph_broken()
{
	return _is_paragraph_broken.get(false);
}

void set_paragraph_broken(bool value)
{
	_is_paragraph_broken.set(value);
}

const std::string filename_from_path(const char *path)
{
	std::string file_path(path);
	return file_path.substr(file_path.rfind(FILE_PATH_COMPONENT_DELIMITER) + 1);
}

}

