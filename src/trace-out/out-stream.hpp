#pragma once

#include "trace-out/filename-line.hpp"
#include "trace-out/has-member.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/mutex.hpp"
#include "trace-out/platform-detection.hpp"
#include "trace-out/pretty.hpp"
#include "trace-out/printfamily.hpp"
#include "trace-out/template-magic.hpp"
#include "trace-out/thread-local-storage.hpp"
#include "trace-out/thread.hpp"
#include "trace-out/to-string.hpp"
#include <bitset>
#include <cstdarg>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <string>

#if TRACE_OUT_CPP_VERSION >= 201103L
	#include <tuple> // [amalgamate:leave]
#endif

#if !defined(TRACE_OUT_STREAM) && !defined(TRACE_OUT_TO_FILE) && !defined(TRACE_OUT_TO_WDO)
	#define TRACE_OUT_TO_STDOUT
#endif

#if defined(TRACE_OUT_STREAM)
	#include TRACE_OUT_STREAM
#elif defined(TRACE_OUT_TO_FILE)
	#include "trace-out/trace-out-to-file.hpp"
#elif defined(TRACE_OUT_TO_WDO)
	#include "trace-out/trace-out-to-wdo.hpp"
#elif defined(TRACE_OUT_TO_NETWORK)
	#include "trace-out/trace-out-to-network.hpp"
#else
	#include "trace-out/trace-out-to-stdout.hpp"
#endif

//
// Public

namespace trace_out
{

	static const class continue_tag {} CONTINUE = continue_tag();
	static const class newline_manipulator {} NEWLINE = newline_manipulator();
	static const class endline_manipulator {} ENDLINE = endline_manipulator();
	static const class flush_manipulator {} FLUSH = flush_manipulator();

	class out_stream
	{
	public:
		inline out_stream(const std::string &filename_line);
		inline out_stream();
		inline out_stream(const continue_tag &);
		inline ~out_stream();

		inline out_stream &operator <<(char character);
		inline out_stream &operator <<(const char *string);
		inline out_stream &operator <<(const std::string &string);
		inline out_stream &operator <<(const newline_manipulator &);
		inline out_stream &operator <<(const endline_manipulator &);
		inline out_stream &operator <<(const flush_manipulator &);
		inline standard::size_t width_left() const;
		inline void printf(const char *format, ...);
		inline void flush();

		inline static standard::size_t width();

	private:
		standard::size_t _current_line_length;
	};

	inline out_stream &operator <<(out_stream &stream, const pretty<bool> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<char> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<wchar_t> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<unsigned char> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<const char *> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<std::string> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<short> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<unsigned short> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<int> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<unsigned int> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<long> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<unsigned long> &value);

#if TRACE_OUT_CPP_VERSION >= 201103L

	inline out_stream &operator <<(out_stream &stream, const pretty<long long> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<unsigned long long> &value);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	inline out_stream &operator <<(out_stream &stream, const pretty<float> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<double> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<long double> &value);
	inline out_stream &operator <<(out_stream &stream, const pretty<const void *> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<const Type_t *> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t *> &value);

	template <typename Type_t, standard::size_t Size>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t[Size]> &value);

	//
	// Common member combinations

	template <typename Type_t>
	typename enable_if<has_members_x_y<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_X_Y<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_x_y_z<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_X_Y_Z<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_x_y_z_w<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_X_Y_Z_W<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_width_height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_x_y_width_height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_x_y_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_X_Y_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_origin_size<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_real_imag<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	//
	// WinApi

	template <typename Type_t>
	typename enable_if<has_members_cx_cy<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_left_top_right_bottom<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	//
	// Unreal Engine

	template <typename Type_t>
	typename enable_if<has_members_v1_v2<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Origin_Direction<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Vertex_Count<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Pitch_Roll_Yaw<Type_t>::value, out_stream>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_GetLowerBound_GetUpperBound<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_GetValue_IsExclusive_IsInclusive_IsOpen<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Min_Max_bIsValid<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Center_W<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Center_Radius_Orientation_Length<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_Origin_BoxExtent_SphereRadius<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_members_GetCharArray<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

#if TRACE_OUT_CPP_VERSION < 201703L

#if defined(TRACE_OUT_GCC)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::auto_ptr<Type_t> > &value);

#if defined(TRACE_OUT_GCC)
	#pragma GCC diagnostic pop
#endif

#endif // TRACE_OUT_CPP_VERSION < 201703L

#if TRACE_OUT_CPP_VERSION >= 201103L

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::unique_ptr<Type_t> > &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::shared_ptr<Type_t> > &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::weak_ptr<Type_t> > &value);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	template <typename First_t, typename Second_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::pair<First_t, Second_t> > &value);

#if TRACE_OUT_CPP_VERSION >= 201103L

	template <typename ...Types_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::tuple<Types_t ...> > &value);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	template <std::size_t Size>
	out_stream &operator <<(out_stream &stream, const pretty<std::bitset<Size> > &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_iterable<Type_t> &value);

	template <typename Iterator_t>
	out_stream &operator <<(out_stream &stream, const pretty_range_closed<Iterator_t> &value);

	template <typename Iterator_t>
	out_stream &operator <<(out_stream &stream, const pretty_range_open<Iterator_t> &value);

	inline out_stream &operator <<(out_stream &stream, const pretty_condition<bool> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_condition<Type_t> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t> &value);

}

//
// Private

namespace trace_out
{

#if defined(TRACE_OUT_INDENTATION)
	static const char INDENTATION[] = TRACE_OUT_INDENTATION;
#else
	static const char INDENTATION[] = "    ";
#endif

#if defined(TRACE_OUT_MARKER)
	static const char MARKER[] = TRACE_OUT_MARKER " ";
#else
	static const char MARKER[] = "";
#endif

	static const char THREAD_HEADER_SEPARATOR = '~';
	static const char DELIMITER[] = " | ";
	static const standard::size_t INDENTATION_WIDTH = sizeof(INDENTATION) - 1;

	inline system::mutex &private_out_stream_mutex();
	inline void out_stream_mutex_lock();
	inline void out_stream_mutex_unlock();

	inline system::tls<std::string> &private_tls_thread_name();
	inline standard::uint64_t &private_current_thread_id();
	inline bool is_running_same_thread();
	inline const std::string current_thread_name();
	inline void set_current_thread_name(const std::string &name);

	inline system::tls<std::string> &private_tls_indentation();
	inline const std::string &indentation();
	inline void indentation_add();
	inline void indentation_remove();

	inline const std::string thread_id_field(standard::uint64_t thread_id);
	inline const std::string thread_header(const std::string &thread_id, const std::string &thread_name, standard::size_t header_width);

}

//
// Implementation

namespace trace_out
{

	system::mutex &private_out_stream_mutex()
	{
		static system::mutex _mutex;

		return _mutex;
	}

	void out_stream_mutex_lock()
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		private_out_stream_mutex().lock();
#endif // defined(TRACE_OUT_SYNC_STREAM)
	}

	void out_stream_mutex_unlock()
	{
#if defined(TRACE_OUT_SYNC_STREAM)
		private_out_stream_mutex().unlock();
#endif // defined(TRACE_OUT_SYNC_STREAM)
	}

	inline system::tls<std::string> &private_tls_thread_name()
	{
		static system::tls<std::string> _thread_name;

		return _thread_name;
	}

	inline standard::uint64_t &private_current_thread_id()
	{
		static standard::uint64_t _current_thread_id;

		return _current_thread_id;
	}

	bool is_running_same_thread()
	{
		if (private_current_thread_id() != system::current_thread_id())
		{
			private_current_thread_id() = system::current_thread_id();
			return false;
		}

		return true;
	}

	const std::string current_thread_name()
	{
		return private_tls_thread_name().get();
	}

	void set_current_thread_name(const std::string &name)
	{
		private_tls_thread_name().set(name);
	}

	system::tls<std::string> &private_tls_indentation()
	{
		static system::tls<std::string> _indentation;

		return _indentation;
	}

	const std::string &indentation()
	{
		return private_tls_indentation().get();
	}

	void indentation_add()
	{
		private_tls_indentation().set(private_tls_indentation().get() + INDENTATION);
	}

	void indentation_remove()
	{
		const std::string &old_indentation = private_tls_indentation().get();
		private_tls_indentation().set(old_indentation.substr(0, old_indentation.length() - INDENTATION_WIDTH));
	}

	const std::string thread_id_field(standard::uint64_t thread_id)
	{
		std::stringstream stream;
		stream << reinterpret_cast<void *>(thread_id);

		return stream.str();
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

	out_stream::out_stream(const std::string &filename_line)
		:
		_current_line_length(0)
	{
		out_stream_mutex_lock();

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
		out_stream_mutex_lock();

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

	out_stream::out_stream(const continue_tag &)
		:
		_current_line_length(0)
	{
		out_stream_mutex_lock();
	}

	out_stream::~out_stream()
	{
		flush();

		out_stream_mutex_unlock();
	}

	out_stream &out_stream::operator <<(char character)
	{
		char string[2] = {character, '\0'};
		trace_out_stream::print(string);
		++_current_line_length;

		return *this;
	}

	out_stream &out_stream::operator <<(const char *string)
	{
		trace_out_stream::print(string);
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
		trace_out_stream::flush();
	}

	standard::size_t out_stream::width()
	{
#if defined(TRACE_OUT_WIDTH)

		return TRACE_OUT_WIDTH;

#else

		return trace_out_stream::width();

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

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<const Type_t *> &value)
	{
		stream << FLUSH;
		const Type_t *pointer = value.get();
		stream << make_pretty(static_cast<const void *>(pointer));
		if (pointer != NULL)
		{
			stream << FLUSH;
			stream << " -> " << make_pretty(*pointer);
		}

		return stream;
	}

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t *> &value)
	{
		stream << FLUSH;
		return stream << make_pretty(static_cast<const Type_t *>(value.get()));
	}

	template <typename Type_t, standard::size_t Size>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t[Size]> &value)
	{
		stream << FLUSH;
		const Type_t *c_array = value.get();

		stream << "[";
		standard::size_t index = 0;
		for ( ; index < Size - 1; ++index)
		{
			stream << make_pretty(c_array[index]) << ", ";
		}

		stream << make_pretty(c_array[index]) << "]";

		return stream;
	}

	template <typename Structure_t, typename Type_t>
	Type_t get_member_value(const Structure_t &instance, Type_t (Structure_t::*member_function)() const)
	{
		return (instance.*member_function)();
	}

	template <typename Structure_t, typename Type_t>
	Type_t get_member_value(const Structure_t &instance, Type_t Structure_t::*data_member)
	{
		return instance.*data_member;
	}

	//
	// Common member combinations

	template <typename Type_t>
	typename enable_if<has_members_x_y<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "{" << make_pretty(get_member_value(point, &Type_t::x)) << ", " << make_pretty(get_member_value(point, &Type_t::y)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_X_Y<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "{" << make_pretty(get_member_value(point, &Type_t::X)) << ", " << make_pretty(get_member_value(point, &Type_t::Y)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_x_y_z<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "{" << make_pretty(get_member_value(point, &Type_t::x)) << ", " << make_pretty(get_member_value(point, &Type_t::y)) << ", " << make_pretty(get_member_value(point, &Type_t::z)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_X_Y_Z<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "{" << make_pretty(get_member_value(point, &Type_t::X)) << ", " << make_pretty(get_member_value(point, &Type_t::Y)) << ", " << make_pretty(get_member_value(point, &Type_t::Z)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_x_y_z_w<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "{" << make_pretty(get_member_value(point, &Type_t::x)) << ", " << make_pretty(get_member_value(point, &Type_t::y)) << ", " << make_pretty(get_member_value(point, &Type_t::z)) << ", " << make_pretty(get_member_value(point, &Type_t::w)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_X_Y_Z_W<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "{" << make_pretty(get_member_value(point, &Type_t::X)) << ", " << make_pretty(get_member_value(point, &Type_t::Y)) << ", " << make_pretty(get_member_value(point, &Type_t::Z)) << ", " << make_pretty(get_member_value(point, &Type_t::W)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_width_height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "{" << make_pretty(get_member_value(size, &Type_t::width)) << " x " << make_pretty(get_member_value(size, &Type_t::height)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "{" << make_pretty(get_member_value(size, &Type_t::Width)) << " x " << make_pretty(get_member_value(size, &Type_t::Height)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_x_y_width_height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t origin_size = value.get();
		stream << "{" << make_pretty(get_member_value(origin_size, &Type_t::x)) << ", " << make_pretty(get_member_value(origin_size, &Type_t::y)) << "} {" << make_pretty(get_member_value(origin_size, &Type_t::width)) << " x " << make_pretty(get_member_value(origin_size, &Type_t::height)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_x_y_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t origin_size = value.get();
		stream << "{" << make_pretty(get_member_value(origin_size, &Type_t::x)) << ", " << make_pretty(get_member_value(origin_size, &Type_t::y)) << "} {" << make_pretty(get_member_value(origin_size, &Type_t::Width)) << " x " << make_pretty(get_member_value(origin_size, &Type_t::Height)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_X_Y_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t origin_size = value.get();
		stream << "{" << make_pretty(get_member_value(origin_size, &Type_t::X)) << ", " << make_pretty(get_member_value(origin_size, &Type_t::Y)) << "} {" << make_pretty(get_member_value(origin_size, &Type_t::Width)) << " x " << make_pretty(get_member_value(origin_size, &Type_t::Height)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_origin_size<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &rect = value.get();
		stream << make_pretty(get_member_value(rect, &Type_t::origin)) << " " << make_pretty(get_member_value(rect, &Type_t::size));
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_real_imag<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &complex = value.get();
		stream << "{" << make_pretty(get_member_value(complex, &Type_t::real)) << ", " << make_pretty(get_member_value(complex, &Type_t::imag)) << "}";
		return stream;
	}

	//
	// WinApi

	template <typename Type_t>
	typename enable_if<has_members_cx_cy<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "{" << make_pretty(get_member_value(size, &Type_t::cx)) << " x " << make_pretty(get_member_value(size, &Type_t::cy)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_left_top_right_bottom<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t origin_size = value.get();
		stream << "{" << make_pretty(get_member_value(origin_size, &Type_t::left)) << ", " << make_pretty(get_member_value(origin_size, &Type_t::top)) << "} {" << make_pretty(get_member_value(origin_size, &Type_t::right)) << " x " << make_pretty(get_member_value(origin_size, &Type_t::bottom)) << "}";
		return stream;
	}

	//
	// Unreal Engine

	template <typename Type_t>
	typename enable_if<has_members_Key_Value<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &key_value = value.get();
		//stream << "{" << make_pretty(get_member_value(key_value, &Type_t::Key)) << ": " << make_pretty(get_member_value(key_value, &Type_t::Value)) << "}";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_v1_v2<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &vectors = value.get();
		stream << make_pretty(vectors.v1) << ", " << make_pretty(vectors.v2);
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_Origin_Direction<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &ray = value.get();
		stream << "O:" << make_pretty(ray.Origin) << ", D:" << make_pretty(ray.Direction);
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_Vertex_Count<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &edge = value.get();
		stream << make_pretty(edge.Vertex[0]) << ", " << make_pretty(edge.Vertex[1]);
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_Pitch_Roll_Yaw<Type_t>::value, out_stream>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &rotator = value.get();
		stream << "(" << make_pretty(rotator.Pitch) << ", " << make_pretty(rotator.Roll) << ", " << make_pretty(rotator.Yaw) << ")";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_GetLowerBound_GetUpperBound<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &range = value.get();

		if (range.GetLowerBound().IsOpen())
		{
			stream << "(-inf";
		}
		else if (range.GetLowerBound().IsExclusive())
		{
			stream << "(" << make_pretty(range.GetLowerBound().GetValue());
		}
		else
		{
			stream << "[" << make_pretty(range.GetLowerBound().GetValue());
		}

		stream << ", ";

		if (range.GetUpperBound().IsOpen())
		{
			stream << "+inf)";
		}
		else if (range.GetUpperBound().IsExclusive())
		{
			stream << make_pretty(range.GetUpperBound().GetValue()) << ")";
		}
		else
		{
			stream << make_pretty(range.GetUpperBound().GetValue()) << "]";
		}

		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_GetValue_IsExclusive_IsInclusive_IsOpen<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &bound_range = value.get();
		if (bound_range.IsOpen())
		{
			stream << "Open";
		}
		else
		{
			stream << make_pretty(bound_range.GetValue()) << "|";
			if (bound_range.IsExclusive())
			{
				stream << "Exclusive";
			}
			else if (bound_range, &Type_t::IsInclusive)
			{
				stream << "Inclusive";
			}
		}

		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_Min_Max_bIsValid<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &box = value.get();
		stream << make_pretty(box.Min) << ", " << make_pretty(box.Max);
		bool validity = box.bIsValid;
		if (!validity)
		{
			stream << " - invalid";
		}
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_Min_Max_IsValid<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &box = value.get();
		stream << make_pretty(box.Min) << ", " << make_pretty(box.Max);
		bool validity = static_cast<bool>(box.IsValid);
		if (!validity)
		{
			stream << " - invalid";
		}

		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_Center_W<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &sphere = value.get();
		stream << "C:" << make_pretty(sphere.Center) << ", R:" << make_pretty(sphere.W);
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_Center_Radius_Orientation_Length<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &capsule = value.get();
		stream << "C:" << make_pretty(capsule.Center) << ", R:" << make_pretty(capsule.Radius) << ", O:" << make_pretty(capsule.Orientation) << ", L:" << make_pretty(capsule.Length);
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &box = value.get();
		stream << "C:" << make_pretty(box.Center) << ", A:(" << make_pretty(box.AxisX) << ", " << make_pretty(box.AxisY) << ", " << make_pretty(box.AxisZ) << "), E:(" << make_pretty(box.ExtentX) << ", " << make_pretty(box.ExtentY) << ", " << make_pretty(box.ExtentZ) << ")";
		return stream;
	}

	template <typename Type_t>
	typename enable_if<has_members_Origin_BoxExtent_SphereRadius<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &bounds = value.get();
		stream << "O:" << make_pretty(bounds.Origin) << ", E:" << make_pretty(bounds.BoxExtent) << ", R:" << make_pretty(bounds.SphereRadius);
		return stream;
	}

	template <typename Iterator_t>
	void print_string(out_stream &stream, Iterator_t begin, Iterator_t end)
	{
		for ( ; begin != end; ++begin)
		{
			stream << *begin;
		}
	}

	template <typename Type_t>
	typename enable_if<has_members_GetCharArray<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &str = value.get();
		stream << "\"";
		print_string(stream, str.begin(), str.end());
		stream << "\"";
		return stream;
	}

#if TRACE_OUT_CPP_VERSION < 201703L

#if defined(TRACE_OUT_GCC)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations" // seems it does not turn off the warning if there's no C++11
#endif

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::auto_ptr<Type_t> > &value)
	{
		stream << FLUSH;
		const std::auto_ptr<Type_t> &pointer = value.get();
		return stream << make_pretty(static_cast<const Type_t *>(pointer.get()));
	}

#if defined(TRACE_OUT_GCC)
	#pragma GCC diagnostic pop
#endif

#endif // TRACE_OUT_CPP_VERSION < 201703L

#if TRACE_OUT_CPP_VERSION >= 201103L

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::unique_ptr<Type_t> > &value)
	{
		stream << FLUSH;
		const std::unique_ptr<Type_t> &pointer = value.get();
		return stream << make_pretty(static_cast<const Type_t *>(pointer.get()));
	}

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::shared_ptr<Type_t> > &value)
	{
		stream << FLUSH;
		const std::shared_ptr<Type_t> &pointer = value.get();
		stream << make_pretty(static_cast<const void *>(pointer.get())) << " (use_count: " << to_string(pointer.use_count()) << ")";
		if (pointer.get() != NULL)
		{
			stream << " -> " << FLUSH;
			stream << make_pretty(*(value.get()));
		}

		return stream;
	}

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::weak_ptr<Type_t> > &value)
	{
		stream << FLUSH;
		const std::weak_ptr<Type_t> &pointer = value.get();
		stream << "(use_count: " << to_string(pointer.use_count()) << ")";

		return stream;
	}

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	template <typename First_t, typename Second_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::pair<First_t, Second_t> > &value)
	{
		stream << FLUSH;
		const std::pair<First_t, Second_t> &pair = value.get();
		stream << "{";
		stream << make_pretty(pair.first) << ", ";
		stream << make_pretty(pair.second) << "}";
		return stream;
	}

#if TRACE_OUT_CPP_VERSION >= 201103L

	template <standard::size_t Index, typename ...Types_t>
	typename enable_if<Index == sizeof_pack<Types_t...>::value - 1, out_stream &>::type print_tuple(out_stream &stream, const std::tuple<Types_t...> &tuple)
	{
		return stream << make_pretty(std::get<Index>(tuple)) << "}";
	}

#if defined(TRACE_OUT_MVS)

	#pragma warning(push)
	#pragma warning(disable:4296) // "expression is always false"

#endif

	template <standard::size_t Index, typename ...Types_t>
	typename enable_if<Index < sizeof_pack<Types_t...>::value - 1, out_stream &>::type print_tuple(out_stream &stream, const std::tuple<Types_t...> &tuple)
	{
		stream << make_pretty(std::get<Index>(tuple)) << ", ";
		return print_tuple<Index + 1>(stream, tuple);
	}

#if defined(TRACE_OUT_MVS)

	#pragma warning(pop)

#endif

	template <typename ...Types_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::tuple<Types_t ...> > &value)
	{
		stream << FLUSH;
		const std::tuple<Types_t ...> &tuple = value.get();
		stream << "{";
		return print_tuple<0>(stream, tuple);
	}

#endif // TRACE_OUT_CPP_VERSION >= 201103L

	template <std::size_t Size>
	out_stream &operator <<(out_stream &stream, const pretty<std::bitset<Size> > &value)
	{
		stream << FLUSH;
		const std::bitset<Size> &bits = value.get();
		return stream << bits.to_string();
	}

	template <typename Type_t>
	Type_t next_itr(Type_t iterator)
	{
		++iterator;
		return iterator;
	}

	// Using this to infer type of iterator in a pre C++11 way
	template <typename Iterator_t>
	void print_begin_end(out_stream &stream, Iterator_t begin, Iterator_t end)
	{
		// Unreal Engine has only 'operator !=' overloaded for its iterators,
		// and I want this to be an early return
		if (!(begin != end))
		{
			return;
		}

		Iterator_t iterator = begin;
		stream << make_pretty(*iterator);
		for (++iterator; iterator != end; ++iterator)
		{
			stream << ", " << make_pretty(*iterator);
		}
	}

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_iterable<Type_t> &value)
	{
		stream << FLUSH << "[";

		const Type_t &container = value.get();
		print_begin_end(stream, container.begin(), container.end());

		stream << "]";
		return stream;
	}

	template <typename Iterator_t>
	out_stream &operator <<(out_stream &stream, const pretty_range_closed<Iterator_t> &value)
	{
		stream << FLUSH << "[";

		Iterator_t iterator = value.get_begin();
		Iterator_t end = value.get_end();
		if (iterator != end)
		{
			stream << make_pretty(*iterator);
			for (++iterator; iterator != end; ++iterator)
			{
				stream << ", " << make_pretty(*iterator);
			}
		}

		stream << "]";
		return stream;
	}

	template <typename Iterator_t>
	out_stream &operator <<(out_stream &stream, const pretty_range_open<Iterator_t> &value)
	{
		stream << FLUSH << "[";

		Iterator_t iterator = value.get_begin();
		std::size_t how_much = value.get_how_much();
		if (how_much > 0)
		{
			stream << make_pretty(*iterator);
			for (++iterator, --how_much; how_much > 0; ++iterator, --how_much)
			{
				stream << ", " << make_pretty(*iterator);
			}
		}

		stream << "]";
		return stream;
	}

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_condition<Type_t> &value)
	{
		stream << FLUSH;
		stream << (value.get() ? "true" : "false") << " (" << FLUSH;
		stream << make_pretty(value.get()) << ")";
		return stream;
	}

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t> &value)
	{
		stream << FLUSH;
		value.get();
		return stream << "<unknown-type>";
	}

}

