#pragma once

#include <memory>
#include <string>
#include <bitset>

#include "trace-out/detail/stuff/platform-detection.hpp"
#if TRACE_OUT_CPP_VERSION >= 201103L
	#include <tuple> // [amalgamate:leave]
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
	out_stream &operator <<(out_stream &stream, const pretty<wchar_t> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned char> &value);
	out_stream &operator <<(out_stream &stream, const pretty<const char *> &value);
	out_stream &operator <<(out_stream &stream, const pretty<std::string> &value);
	out_stream &operator <<(out_stream &stream, const pretty<short> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned short> &value);
	out_stream &operator <<(out_stream &stream, const pretty<int> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned int> &value);
	out_stream &operator <<(out_stream &stream, const pretty<long> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned long> &value);

#if TRACE_OUT_CPP_VERSION >= 201103L

	out_stream &operator <<(out_stream &stream, const pretty<long long> &value);
	out_stream &operator <<(out_stream &stream, const pretty<unsigned long long> &value);

#endif // TRACE_OUT_CPP_VERSION >= 201103L

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
		stream << "(" << make_pretty(get_member_value(point, &Type_t::x)) << ", " << make_pretty(get_member_value(point, &Type_t::y)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_X_Y<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::X)) << ", " << make_pretty(get_member_value(point, &Type_t::Y)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_x_y_z<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::x)) << ", " << make_pretty(get_member_value(point, &Type_t::y)) << ", " << make_pretty(get_member_value(point, &Type_t::z)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_X_Y_Z<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::X)) << ", " << make_pretty(get_member_value(point, &Type_t::Y)) << ", " << make_pretty(get_member_value(point, &Type_t::Z)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_x_y_z_w<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::x)) << ", " << make_pretty(get_member_value(point, &Type_t::y)) << ", " << make_pretty(get_member_value(point, &Type_t::z)) << ", " << make_pretty(get_member_value(point, &Type_t::w)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_X_Y_Z_W<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &point = value.get();
		stream << "(" << make_pretty(get_member_value(point, &Type_t::X)) << ", " << make_pretty(get_member_value(point, &Type_t::Y)) << ", " << make_pretty(get_member_value(point, &Type_t::Z)) << ", " << make_pretty(get_member_value(point, &Type_t::W)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_width_height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "(" << make_pretty(get_member_value(size, &Type_t::width)) << " x " << make_pretty(get_member_value(size, &Type_t::height)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "(" << make_pretty(get_member_value(size, &Type_t::Width)) << " x " << make_pretty(get_member_value(size, &Type_t::Height)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_x_y_width_height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t origin_size = value.get();
		stream << "(" << make_pretty(get_member_value(origin_size, &Type_t::x)) << ", " << make_pretty(get_member_value(origin_size, &Type_t::y)) << ") (" << make_pretty(get_member_value(origin_size, &Type_t::width)) << " x " << make_pretty(get_member_value(origin_size, &Type_t::height)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_X_Y_Width_Height<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t origin_size = value.get();
		stream << "(" << make_pretty(get_member_value(origin_size, &Type_t::X)) << ", " << make_pretty(get_member_value(origin_size, &Type_t::Y)) << ") (" << make_pretty(get_member_value(origin_size, &Type_t::Width)) << " x " << make_pretty(get_member_value(origin_size, &Type_t::Height)) << ")";
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
		stream << "(" << make_pretty(get_member_value(complex, &Type_t::real)) << ", " << make_pretty(get_member_value(complex, &Type_t::imag)) << ")";
		return stream;
	}


	//
	// WinApi

	template <typename Type_t>
	typename enable_if<has_members_cx_cy<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t &size = value.get();
		stream << "(" << make_pretty(get_member_value(size, &Type_t::cx)) << " x " << make_pretty(get_member_value(size, &Type_t::cy)) << ")";
		return stream;
	}


	template <typename Type_t>
	typename enable_if<has_members_left_top_right_bottom<Type_t>::value, out_stream &>::type operator <<(out_stream &stream, const pretty_structural<Type_t> &value)
	{
		stream << FLUSH;
		const Type_t origin_size = value.get();
		stream << "(" << make_pretty(get_member_value(origin_size, &Type_t::left)) << ", " << make_pretty(get_member_value(origin_size, &Type_t::top)) << ") (" << make_pretty(get_member_value(origin_size, &Type_t::right)) << " x " << make_pretty(get_member_value(origin_size, &Type_t::bottom)) << ")";
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

		if (range.GetLowerBound().IsOopen())
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

		if (range.GetUpperBound().IsOopen())
		{
			stream << "(-inf";
		}
		else if (range.GetUpperBound().IsExclusive())
		{
			stream << "(" << make_pretty(range.GetUpperBound().GetValue());
		}
		else
		{
			stream << "[" << make_pretty(range.GetUpperBound().GetValue());
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
		stream << "C:" << make_pretty(box.Center) << " A:(" << make_pretty(box.AxisX) << ", " << make_pretty(box.AxisY) << ", " << make_pretty(box.AxisZ) << "), E:(" << make_pretty(box.ExtentX) << ", " << make_pretty(box.ExtentY) << ", " << make_pretty(box.ExtentZ) << ")";
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
}

