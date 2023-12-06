#pragma once

//
// Public

namespace trace_out
{

template <typename Type_t>
struct is_floating_point;

}

//
// Implementation

namespace trace_out
{

template <typename Type_t>
struct is_floating_point
{
	enum
	{
		value = 0
	};
};

#define trace_out_private__define_is_floating_point(type) \
	template <> \
	struct is_floating_point<type> \
	{ \
		enum \
		{ \
			value = 1 \
		}; \
	}

trace_out_private__define_is_floating_point(float);
trace_out_private__define_is_floating_point(double);
trace_out_private__define_is_floating_point(long double);

#undef trace_out_private__define_is_floating_point

}

