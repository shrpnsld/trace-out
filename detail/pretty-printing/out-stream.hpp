#pragma once

#include <memory>
#include <string>
#include <bitset>

#include "trace-out/detail/stuff/platform-detection.hpp"
#if defined(TRACE_OUT_CPP11)
	#include <tuple>
#endif

#include "trace-out/detail/standard/integer.hpp"
#include "trace-out/detail/stuff/stuff.hpp"
#include "trace-out/detail/pretty-printing/pretty.hpp"


namespace trace_out { namespace detail
{

	const std::string &indentation();
	void indentation_add();
	void indentation_remove();

	void set_current_thread_name(const std::string &name);

	class newline_manipulator;
	class endline_manipulator;
	class flush_manipulator;

	extern const newline_manipulator NEWLINE;
	extern const endline_manipulator ENDLINE;
	extern const flush_manipulator FLUSH;


	class out_stream
	{
	public:
		out_stream(const std::string &filename_line);
		out_stream();
		~out_stream();

		out_stream &operator <<(char character);
		out_stream &operator <<(const char *string);
		out_stream &operator <<(const std::string &string);
		out_stream &operator <<(const newline_manipulator &);
		out_stream &operator <<(const endline_manipulator &);
		out_stream &operator <<(const flush_manipulator &);
		standard::size_t width_left() const;
		void printf(const char *format, ...);
		void flush();

		static standard::size_t width();

	private:
		standard::size_t _current_line_length;
	};


	out_stream &operator <<(out_stream &stream, const pretty<bool> &value);
	out_stream &operator <<(out_stream &stream, const pretty<char> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned char> &value);
	out_stream &operator <<(out_stream &stream, const pretty<const char *> &value);
	out_stream &operator <<(out_stream &stream, const pretty<std::string> &value);
	out_stream &operator <<(out_stream &stream, const pretty<short> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned short> &value);
	out_stream &operator <<(out_stream &stream, const pretty<int> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned int> &value);
	out_stream &operator <<(out_stream &stream, const pretty<long> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned long> &value);

#if defined(TRACE_OUT_CPP11)

	out_stream &operator <<(out_stream &stream, const pretty<long long> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned long long> &value);

#endif // defined(TRACE_OUT_CPP11)

	out_stream &operator <<(out_stream &stream, const pretty<float> &value);
	out_stream &operator <<(out_stream &stream, const pretty<double> &value);
	out_stream &operator <<(out_stream &stream, const pretty<long double> &value);
	out_stream &operator <<(out_stream &stream, const pretty<const void *> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<const Type_t *> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t *> &value);

	template <typename Type_t, standard::size_t Size>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t[Size]> &value);

	template <typename Type_t>
	typename enable_if<has_member_x<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_member_X<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_member_width<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_member_Width<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_member_WIDTH<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_member_origin<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_member_Origin<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_member_ORIGIN<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_member_real<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_member_Real<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

	template <typename Type_t>
	typename enable_if<has_member_REAL<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value);

#if defined(TRACE_OUT_GCC)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::auto_ptr<Type_t> > &value);

#if defined(TRACE_OUT_GCC)
	#pragma GCC diagnostic pop
#endif

#if defined(TRACE_OUT_CPP11)

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::unique_ptr<Type_t> > &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::shared_ptr<Type_t> > &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::weak_ptr<Type_t> > &value);

#endif // defined(TRACE_OUT_CPP11)

	template <typename First_t, typename Second_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::pair<First_t, Second_t> > &value);

#if defined(TRACE_OUT_CPP11)

	template <typename ...Types_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::tuple<Types_t ...> > &value);

#endif // defined(TRACE_OUT_CPP11)


	template <std::size_t Size>
	out_stream &operator <<(out_stream &stream, const pretty<std::bitset<Size> > &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_iterable<Type_t> &value);

	template <typename Iterator_t>
	out_stream &operator <<(out_stream &stream, const pretty_range_closed<Iterator_t> &value);

	template <typename Iterator_t>
	out_stream &operator <<(out_stream &stream, const pretty_range_open<Iterator_t> &value);

	out_stream &operator <<(out_stream &stream, const pretty_condition<bool> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_condition<Type_t> &value);

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<Type_t> &value);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty<const Type_t *> &value)
	{
		stream << FLUSH;
		const Type_t *pointer = value.get();
		stream << make_pretty(static_cast<const void *>(pointer)) << " ";
		if (pointer != NULL)
		{
			stream << FLUSH;
			stream << "-> " << make_pretty(*pointer);
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
	void print_member_value(out_stream &stream, const Structure_t &instance, Type_t (Structure_t::*member_function)() const)
	{
		Type_t value = (instance.*member_function)();
		stream << make_pretty(value);
	}


	template <typename Structure_t, typename Type_t>
	void print_member_value(out_stream &stream, const Structure_t &instance, Type_t Structure_t::*data_member)
	{
		Type_t value = instance.*data_member;
		stream << make_pretty(value);
	}


	template <typename Type_t>
	typename enable_if<has_member_w<Type_t>::value, out_stream &>::type print_w(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.unsafe_get();
		stream << ", ";
		print_member_value(stream, point, &Type_t::w);
		return stream << ")";
	}


	template <typename Type_t>
	typename enable_if<has_member_W<Type_t>::value, out_stream &>::type print_w(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.unsafe_get();
		stream << ", ";
		print_member_value(stream, point, &Type_t::W);
		return stream << ")";
	}


	template <typename Type_t>
	typename enable_if<!(has_member_w<Type_t>::value || has_member_W<Type_t>::value), out_stream &>::type print_w(out_stream &stream, const pretty_structural<Type_t> &)
	{
		return stream << ")";
	}


	template <typename Type_t>
	typename enable_if<has_member_z<Type_t>::value, out_stream &>::type print_z(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.unsafe_get();
		stream << ", ";
		print_member_value(stream, point, &Type_t::z);
		return print_w(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_Z<Type_t>::value, out_stream &>::type print_z(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.unsafe_get();
		stream << ", ";
		print_member_value(stream, point, &Type_t::Z);
		return print_w(stream, value);
	}


	template <typename Type_t>
	typename enable_if<!(has_member_z<Type_t>::value || has_member_Z<Type_t>::value), out_stream &>::type print_z(out_stream &stream, const pretty_structural<Type_t> &)
	{
		return stream << ")";
	}


	template <typename Type_t>
	typename enable_if<has_member_y<Type_t>::value, out_stream &>::type print_y(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.unsafe_get();
		stream << ", ";
		print_member_value(stream, point, &Type_t::y);
		return print_z(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_Y<Type_t>::value, out_stream &>::type print_y(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.unsafe_get();
		stream << ", ";
		print_member_value(stream, point, &Type_t::Y);
		return print_z(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_x<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(";
		print_member_value(stream, point, &Type_t::x);
		return print_y(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_X<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(";
		print_member_value(stream, point, &Type_t::X);
		return print_y(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_height<Type_t>::value, out_stream &>::type print_height(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.unsafe_get();
		stream << " x ";
		print_member_value(stream, size, &Type_t::height);
		return stream << ")";
	}


	template <typename Type_t>
	typename enable_if<has_member_Height<Type_t>::value, out_stream &>::type print_height(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.unsafe_get();
		stream << " x ";
		print_member_value(stream, size, &Type_t::Height);
		return stream << ")";
	}


	template <typename Type_t>
	typename enable_if<has_member_HEIGHT<Type_t>::value, out_stream &>::type print_height(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.unsafe_get();
		stream << " x ";
		print_member_value(stream, size, &Type_t::HEIGHT);
		return stream << ")";
	}


	template <typename Type_t>
	typename enable_if<has_member_width<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "(";
		print_member_value(stream, size, &Type_t::width);
		return print_height(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_Width<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "(";
		print_member_value(stream, size, &Type_t::Width);
		return print_height(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_WIDTH<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "(";
		print_member_value(stream, size, &Type_t::WIDTH);
		return print_height(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_size<Type_t>::value, out_stream &>::type print_size(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &rect = value.unsafe_get();
		stream << " ";
		print_member_value(stream, rect, &Type_t::size);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_member_Size<Type_t>::value, out_stream &>::type print_size(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &rect = value.unsafe_get();
		stream << " ";
		print_member_value(stream, rect, &Type_t::Size);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_member_SIZE<Type_t>::value, out_stream &>::type print_size(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &rect = value.unsafe_get();
		stream << " ";
		print_member_value(stream, rect, &Type_t::SIZE);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_member_origin<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &rect = value.get();
		print_member_value(stream, rect, &Type_t::origin);
		return print_size(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_Origin<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &rect = value.get();
		print_member_value(stream, rect, &Type_t::Origin);
		return print_size(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_ORIGIN<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &rect = value.get();
		print_member_value(stream, rect, &Type_t::ORIGIN);
		return print_size(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_imag<Type_t>::value, out_stream &>::type print_size(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &complex = value.unsafe_get();
		stream << " ";
		print_member_value(stream, complex, &Type_t::imag);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_member_Imag<Type_t>::value, out_stream &>::type print_size(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &complex = value.unsafe_get();
		stream << " ";
		print_member_value(stream, complex, &Type_t::Imag);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_member_IMAG<Type_t>::value, out_stream &>::type print_size(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &complex = value.unsafe_get();
		stream << " ";
		print_member_value(stream, complex, &Type_t::IMAG);
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_member_real<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &complex = value.get();
		print_member_value(stream, complex, &Type_t::real);
		return print_size(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_Real<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &complex = value.get();
		print_member_value(stream, complex, &Type_t::Real);
		return print_size(stream, value);
	}


	template <typename Type_t>
	typename enable_if<has_member_REAL<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &complex = value.get();
		print_member_value(stream, complex, &Type_t::REAL);
		return print_size(stream, value);
	}


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


#if defined(TRACE_OUT_CPP11)

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

#endif // defined(TRACE_OUT_CPP11)


	template <typename First_t, typename Second_t>
	out_stream &operator <<(out_stream &stream, const pretty<std::pair<First_t, Second_t> > &value)
	{
		stream << FLUSH;
		const std::pair<First_t, Second_t> &pair = value.get();
		stream << "{";
		stream << make_pretty(pair.first) << ": ";
		stream << make_pretty(pair.second) << "}";
		return stream;
	}


#if defined(TRACE_OUT_CPP11)

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

#endif // defined(TRACE_OUT_CPP11)


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


	template <typename Type_t>
	out_stream &operator <<(out_stream &stream, const pretty_iterable<Type_t> &value)
	{
		stream << FLUSH << "[";

		const Type_t &container = value.get();
		if (!container.empty())
		{
			typename Type_t::const_iterator iterator = container.begin();
			stream << make_pretty(*iterator);
			for (++iterator; iterator != container.end(); ++iterator)
			{
				stream << ", " << make_pretty(*iterator);
			}
		}

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
}
