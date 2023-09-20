#include <cstdarg>
#include <cstdlib>
#include <sstream>

#include "trace-out/standard/printfamily.hpp"
#include "trace-out/system/thread-local-storage.hpp"
#include "trace-out/system/mutex.hpp"
#include "trace-out/system/thread.hpp"

#include "trace-out/pretty-printing/out-stream.hpp"


#if defined(TRACE_OUT_REDIRECTION)
	#define TRACE_OUT_REDIRECTION_NAMESPACE TRACE_OUT_REDIRECTION
#else
	#define TRACE_OUT_REDIRECTION_NAMESPACE trace_out_to_stdout
#endif


namespace TRACE_OUT_REDIRECTION_NAMESPACE
{

	void print(const char *string);
	void flush();
	trace_out::detail::standard::size_t width();

}


namespace trace_out { namespace detail
{

#if defined(TRACE_OUT_INDENTATION)
	const char INDENTATION[] = TRACE_OUT_INDENTATION;
#else
	const char INDENTATION[] = "    ";
#endif

#if defined(TRACE_OUT_MARKER)
	const char MARKER[] = TRACE_OUT_MARKER " ";
#else
	const char MARKER[] = "";
#endif

	const char THREAD_HEADER_SEPARATOR = '~';
	const char DELIMITER[] = " |  ";
	const standard::size_t INDENTATION_WIDTH = sizeof(INDENTATION) - 1;

}
}


namespace trace_out { namespace detail
{

	const class newline_manipulator {} NEWLINE = newline_manipulator();
	const class endline_manipulator {} ENDLINE = endline_manipulator();
	const class flush_manipulator {} FLUSH = flush_manipulator();


	const std::string current_thread_name();
	bool is_running_same_thread();

	void lock_output();
	void unlock_output();

	const std::string thread_id_field(standard::uint64_t thread_id);
	const std::string thread_header(const std::string &thread_id, const std::string &thread_name);


	standard::uint64_t _current_thread_id;
	system::tls<std::string> _thread_name;
	system::mutex _output_mutex;
	system::tls<std::string> _indentation;

}
}


namespace trace_out { namespace detail
{

	const std::string current_thread_name()
	{
		return _thread_name.get();
	}


	bool is_running_same_thread()
	{
		if (_current_thread_id != system::current_thread_id())
		{
			_current_thread_id = system::current_thread_id();
			return false;
		}

		return true;
	}


	void lock_output()
	{
#if defined(TRACE_OUT_OUTPUT_SYNC_ON)

		_output_mutex.lock();

#endif // defined(TRACE_OUT_OUTPUT_SYNC_ON)
	}


	void unlock_output()
	{
#if defined(TRACE_OUT_OUTPUT_SYNC_ON)

		_output_mutex.unlock();

#endif // defined(TRACE_OUT_OUTPUT_SYNC_ON)
	}


	const std::string thread_id_field(standard::uint64_t thread_id)
	{
		std::stringstream stream;
		stream << reinterpret_cast<void *>(thread_id);

		return stream.str();
	}


	void set_current_thread_name(const std::string &name)
	{
		_thread_name.set(name);
	}


	const std::string thread_header(const std::string &thread_id, const std::string &thread_name, standard::size_t header_width)
	{
		std::stringstream stream;
		stream.fill(THREAD_HEADER_SEPARATOR);
		stream.flags(std::ios::left);
		stream.width(static_cast<std::streamsize>(header_width));
		stream << ("[Thread: " + thread_id + (!thread_name.empty() ? " " : "") + thread_name + "]");

		return stream.str();
	}


	const std::string &indentation()
	{
		return _indentation.get();
	}


	void indentation_add()
	{
		_indentation.set(_indentation.get() + INDENTATION);
	}


	void indentation_remove()
	{
		const std::string &old_indentation = _indentation.get();
		_indentation.set(old_indentation.substr(0, old_indentation.length() - INDENTATION_WIDTH));
	}


	out_stream::out_stream(const std::string &filename_line)
		:
		_current_line_length(0)
	{
		lock_output();

		(void)filename_line; // eliminating 'not used' warning

		*this << MARKER;

#if defined(TRACE_OUT_SHOW_THREAD)
		if (!is_running_same_thread())
		{
			std::string thread_id = thread_id_field(system::current_thread_id());
			const std::string &thread_name = current_thread_name();
			standard::size_t header_width = out_stream::width() - std::strlen(MARKER);
			const std::string &header = thread_header(thread_id, thread_name, header_width);

			*this << header << ENDLINE << MARKER;
		}
#endif // defined(TRACE_OUT_SHOW_THREAD)

#if defined(TRACE_OUT_SHOW_FILE_LINE)
		*this << filename_line << DELIMITER;
#endif // defined(TRACE_OUT_SHOW_FILE_LINE)

        *this << indentation();
	}


	out_stream::out_stream()
		:
		_current_line_length(0)
	{
		lock_output();

		*this << MARKER;

#if defined(TRACE_OUT_SHOW_FILE_LINE)
		std::stringstream stream;
		stream.fill(' ');
		stream.width(FILENAME_FIELD_WIDTH + 1 + LINE_FIELD_WIDTH);
		stream << "";
		*this << stream.str() << DELIMITER;
#endif // defined(TRACE_OUT_SHOW_FILE_LINE)

		*this << indentation();
	}


	out_stream::~out_stream()
	{
		flush();

		unlock_output();
	}


	out_stream &out_stream::operator <<(char character)
	{
		char string[2] = {character, '\0'};
		TRACE_OUT_REDIRECTION_NAMESPACE::print(string);
		++_current_line_length;

		return *this;
	}


	out_stream &out_stream::operator <<(const char *string)
	{
		TRACE_OUT_REDIRECTION_NAMESPACE::print(string);
		_current_line_length += std::strlen(string);

		return *this;
	}


	out_stream &out_stream::operator <<(const std::string &string)
	{
		return *this << string.c_str();
	}


	out_stream &out_stream::operator <<(const newline_manipulator &)
	{
		*this << "\n";
		_current_line_length = 0;
		*this << MARKER;

#if defined(TRACE_OUT_SHOW_FILE_LINE)
		std::stringstream stream;
		stream.fill(' ');
		stream.width(FILENAME_FIELD_WIDTH + 1 + LINE_FIELD_WIDTH);
		stream << "";

		*this << stream.str() << DELIMITER;
#endif // defined(TRACE_OUT_SHOW_FILE_LINE)

		*this << indentation();

		return *this;
	}


	out_stream &out_stream::operator <<(const endline_manipulator &)
	{
		*this << "\n";
		_current_line_length = 0;

		return *this;
	}


	out_stream &out_stream::operator <<(const flush_manipulator &)
	{
		flush();
		return *this;
	}


	standard::size_t out_stream::width_left() const
	{
		return out_stream::width() - _current_line_length;
	}


	void out_stream::printf(const char *format, ...)
	{
		va_list arguments;
		va_list arguments_copy;

		va_start(arguments, format);
		va_start(arguments_copy, format);

		standard::size_t size = standard::vsnprintf_string_length(format, arguments_copy) + 1;

		resource<void *> buffer(std::malloc(size), std::free);
		standard::vsnprintf(static_cast<char *>(buffer.get()), size, format, arguments);
		*this << "// " << static_cast<char *>(buffer.get());

		va_end(arguments);
		va_end(arguments_copy);
	}


	void out_stream::flush()
	{
		TRACE_OUT_REDIRECTION_NAMESPACE::flush();
	}


	standard::size_t out_stream::width()
	{
#if defined(TRACE_OUT_WIDTH)

		return TRACE_OUT_WIDTH;

#else

		return TRACE_OUT_REDIRECTION_NAMESPACE::width();

#endif // defined(TRACE_OUT_WIDTH)
	}


	out_stream &operator <<(out_stream &stream, const pretty<bool> &value)
	{
		stream << FLUSH;
		return stream << (value.get() ? "true" : "false");
	}


	out_stream &operator <<(out_stream &stream, const pretty<char> &value)
	{
		stream << FLUSH;
		return stream << "'" << value.get() << "'";
	}


	out_stream &operator <<(out_stream &stream, const pretty<wchar_t> &value)
	{
		stream << FLUSH;
		return stream << "'" << value.get() << "'";
	}


	out_stream &operator <<(out_stream &stream, const pretty<unsigned char> &value)
	{
		stream << FLUSH;
		return stream << to_string(static_cast<unsigned int>(value.get()));
	}


	out_stream &operator <<(out_stream &stream, const pretty<const char *> &value)
	{
		stream << FLUSH;
		if (value.get() == NULL)
		{
			return stream << "<null>";
		}

		return stream << "\"" << value.get() << "\"";
	}


	out_stream &operator <<(out_stream &stream, const pretty<std::string> &value)
	{
		stream << FLUSH;
		return stream << "\"" << value.get() << "\"";
	}


	out_stream &operator <<(out_stream &stream, const pretty<short> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}


	out_stream &operator <<(out_stream &stream, const pretty<unsigned short> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}


	out_stream &operator <<(out_stream &stream, const pretty<int> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}


	out_stream &operator <<(out_stream &stream, const pretty<unsigned int> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}


	out_stream &operator <<(out_stream &stream, const pretty<long> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}


	out_stream &operator <<(out_stream &stream, const pretty<unsigned long> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}


#if TRACE_OUT_CPP_VERSION >= 201103L

	out_stream &operator <<(out_stream &stream, const pretty<long long> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}


	out_stream &operator <<(out_stream &stream, const pretty<unsigned long long> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}

#endif // TRACE_OUT_CPP_VERSION >= 201103L


	out_stream &operator <<(out_stream &stream, const pretty<float> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}


	out_stream &operator <<(out_stream &stream, const pretty<double> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}


	out_stream &operator <<(out_stream &stream, const pretty<long double> &value)
	{
		stream << FLUSH;
		return stream << to_string(value.get());
	}


	out_stream &operator <<(out_stream &stream, const pretty<const void *> &value)
	{
		stream << FLUSH;
		if (value.get() == NULL)
		{
			return stream << "<null>";
		}

		standard::uintptr_t numeric_value = reinterpret_cast<standard::uintptr_t>(value.get());
		return stream << to_string(numeric_value, std::hex, std::showbase);
	}


	out_stream &operator <<(out_stream &stream, const pretty_condition<bool> &value)
	{
		stream << FLUSH;
		return stream << (value.get() ? "true" : "false");
	}

}
}

