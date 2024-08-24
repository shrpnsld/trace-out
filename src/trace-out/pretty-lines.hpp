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
#include "trace-out/template-magic.hpp"
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
static struct thread_info_t {} THREAD_INFO;
static struct marker_t {} MARKER;
static const char DATE_TIME_BLANK[] = "                   ";
static const std::string FILE_LINE_BLANK = file_line_t::blank();
static struct continue_paragraph_t {} CONTINUE_PARAGRAPH;
static struct break_paragraph_t {} BREAK_PARAGRAPH;

inline system::mutex &stream_mutex();
inline void print_start_header(std::ostream &stream, const char *message = NULL);
inline std::ostream &operator <<(std::ostream &stream, reset_flags_t);
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

#if defined(TRACE_OUT_MARKER)
static const standard::size_t MARKER_WIDTH = c_str_arr_size(TRACE_OUT_MARKER);
#endif // defined(TRACE_OUT_MARKER)

static const standard::size_t DATE_TIME_FIELD_WIDTH = c_str_arr_size(DATE_TIME_BLANK);
static const standard::size_t FILENAME_FIELD_WIDTH = 20;
static const standard::size_t LINE_FIELD_WIDTH = 4;
static const standard::size_t FILENAME_LINE_FIELD_WIDTH = FILENAME_FIELD_WIDTH + 1 + LINE_FIELD_WIDTH;
static const char TIME_SPACE_CONTEXT_DELIMITER[] = " | ";
static const standard::size_t TIME_SPACE_CONTEXT_DELIMITER_WIDTH = c_str_arr_size(TIME_SPACE_CONTEXT_DELIMITER);

static const char FILENAME_FIELD_EXCESS_PADDING[] = "~";
static const standard::size_t FILENAME_FIELD_EXCESS_PADDING_SIZE = c_str_arr_size(FILENAME_FIELD_EXCESS_PADDING);

static const char FILE_PATH_COMPONENT_DELIMITER =
#if defined(TRACE_OUT_POSIX)
	'/'
#elif defined(TRACE_OUT_WINDOWS)
	'\\'
#endif
	;

static system::tls<bool> _is_paragraph_broken;
inline bool is_paragraph_broken();
inline void set_paragraph_broken(bool value);
inline const std::string filename_from_path(const char *path);

}

//
// Implementation

namespace trace_out
{

void print_start_header(std::ostream &stream, const char *message)
{
	standard::size_t header_width = 0;

	stream << MARKER;
#if defined(TRACE_OUT_MARKER)
	header_width += MARKER_WIDTH + 1;
#endif // defined(TRACE_OUT_MARKER)

#if defined(TRACE_OUT_SHOW_DATE_TIME)
	stream << std::setfill('#') << std::setw(DATE_TIME_FIELD_WIDTH) << "" << RESET_FLAGS;
	header_width += DATE_TIME_FIELD_WIDTH;
#endif // defined(TRACE_OUT_SHOW_FILE_LINE)

#if defined(TRACE_OUT_SHOW_DATE_TIME) && defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << '#';
	header_width += 1;
#endif // defined(TRACE_OUT_SHOW_DATE_TIME) && defined(TRACE_OUT_SHOW_FILE_LINE)

#if defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << std::setfill('#') << std::setw(FILENAME_LINE_FIELD_WIDTH) << "" << RESET_FLAGS;
	header_width += FILENAME_LINE_FIELD_WIDTH;
#endif // defined(TRACE_OUT_SHOW_FILE_LINE)

#if defined(TRACE_OUT_SHOW_DATE_TIME) || defined(TRACE_OUT_SHOW_FILE_LINE)
	stream << std::setfill('#') << std::setw(TIME_SPACE_CONTEXT_DELIMITER_WIDTH) << "" << RESET_FLAGS;
	header_width += TIME_SPACE_CONTEXT_DELIMITER_WIDTH;
#endif // defined(TRACE_OUT_SHOW_DATE_TIME) || defined(TRACE_OUT_SHOW_FILE_LINE)

	std::string date_time = date_time_now();
	stream << "#### [ " << styles::STRING << date_time << styles::NORMAL;
	header_width += 7 + date_time.size();

	if (message != NULL)
	{
		stream << ' ' << styles::SUBJECT << message << styles::NORMAL;
		header_width += 1 + std::strlen(message);
	}
	else
	{
#if defined(TRACE_OUT_START_MESSAGE)
		message = TRACE_OUT_START_MESSAGE;
		stream << ' ' << styles::SUBJECT << message << styles::NORMAL;
		header_width += 1 + std::strlen(message);
#endif // defined(TRACE_OUT_START_MESSAGE)
	}

	stream << " ] ";
	header_width += 3;

	standard::size_t console_width = system::console_width();
	standard::size_t rest_fill_width = console_width > header_width ? console_width - header_width : 4;
	stream << std::setw(rest_fill_width) << std::setfill('#') << "" << RESET_FLAGS << '\n' << BREAK_PARAGRAPH;
}

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

