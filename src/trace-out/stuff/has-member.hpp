#pragma once

#include "trace-out/stuff/template-magic.hpp"

namespace trace_out { namespace detail
{

#define trace_out_private__define_has_member(name) \
			template <typename Struct_t> \
			struct has_member_##name \
			{ \
				struct fallback \
				{ \
					int name; \
				}; \
				\
				struct dummy \
				{ \
				}; \
				\
				struct derived \
					: conditional<is_structural<Struct_t>::value, Struct_t, dummy>::type, fallback \
				{ \
					derived(const derived &) \
					{ \
					} \
					\
					derived &operator =(const derived &) \
					{ \
						return *this; \
					} \
				}; \
				\
				template <typename Type_t, Type_t> \
				struct do_check; \
				\
				template <typename Type_t> \
				static char (&function(do_check<int fallback::*, &Type_t::name> *))[1]; \
				\
				template <typename Type_t> \
				static char (&function(...))[2]; \
				\
				enum \
				{ \
					value = sizeof(function<derived>(0)) == 2 \
				}; \
			}

	//
	// Common members

	trace_out_private__define_has_member(x);
	trace_out_private__define_has_member(y);
	trace_out_private__define_has_member(z);
	trace_out_private__define_has_member(w);
	trace_out_private__define_has_member(X);
	trace_out_private__define_has_member(Y);
	trace_out_private__define_has_member(Z);
	trace_out_private__define_has_member(W);
	trace_out_private__define_has_member(width);
	trace_out_private__define_has_member(height);
	trace_out_private__define_has_member(Width);
	trace_out_private__define_has_member(Height);
	trace_out_private__define_has_member(origin);
	trace_out_private__define_has_member(size);
	trace_out_private__define_has_member(real);
	trace_out_private__define_has_member(imag);
	trace_out_private__define_has_member(begin);
	trace_out_private__define_has_member(end);


	//
	// WinApi

	trace_out_private__define_has_member(cx);
	trace_out_private__define_has_member(cy);
	trace_out_private__define_has_member(left);
	trace_out_private__define_has_member(top);
	trace_out_private__define_has_member(right);
	trace_out_private__define_has_member(bottom);


	//
	// Unreal Engine

	trace_out_private__define_has_member(Key);
	trace_out_private__define_has_member(Value);
	trace_out_private__define_has_member(v1);
	trace_out_private__define_has_member(v2);
	trace_out_private__define_has_member(Origin);
	trace_out_private__define_has_member(Direction);
	trace_out_private__define_has_member(Pitch);
	trace_out_private__define_has_member(Roll);
	trace_out_private__define_has_member(Yaw);
	trace_out_private__define_has_member(GetLowerBound);
	trace_out_private__define_has_member(GetUpperBound);
	trace_out_private__define_has_member(GetValue);
	trace_out_private__define_has_member(IsExclusive);
	trace_out_private__define_has_member(IsInclusive);
	trace_out_private__define_has_member(IsOpen);
	trace_out_private__define_has_member(Vertex);
	trace_out_private__define_has_member(Count);
	trace_out_private__define_has_member(Min);
	trace_out_private__define_has_member(Max);
	trace_out_private__define_has_member(Center);
	trace_out_private__define_has_member(Radius);
	trace_out_private__define_has_member(Orientation);
	trace_out_private__define_has_member(Length);
	trace_out_private__define_has_member(AxisX);
	trace_out_private__define_has_member(AxisY);
	trace_out_private__define_has_member(AxisZ);
	trace_out_private__define_has_member(ExtentX);
	trace_out_private__define_has_member(ExtentY);
	trace_out_private__define_has_member(ExtentZ);
	trace_out_private__define_has_member(bIsValid);
	trace_out_private__define_has_member(IsValid);
	trace_out_private__define_has_member(BoxExtent);
	trace_out_private__define_has_member(SphereRadius);
	trace_out_private__define_has_member(GetCharArray);

#undef trace_out_private__define_has_member


#define trace_out_private__define_has_members(name, template_parameter_name, ...) \
	template <typename template_parameter_name> \
	struct has_members_##name \
	{ \
		enum \
		{ \
			value = __VA_ARGS__ \
		}; \
	}


	//
	// Common member combinations

	trace_out_private__define_has_members(x_y, Type_t,
		has_member_x<Type_t>::value && has_member_y<Type_t>::value &&
		!has_member_z<Type_t>::value && !has_member_w<Type_t>::value && !has_member_width<Type_t>::value && !has_member_height<Type_t>::value && !has_member_Width<Type_t>::value && !has_member_Height<Type_t>::value);

	trace_out_private__define_has_members(X_Y, Type_t,
		has_member_X<Type_t>::value && has_member_Y<Type_t>::value &&
		!has_member_Z<Type_t>::value && !has_member_W<Type_t>::value && !has_member_Width<Type_t>::value && !has_member_Height<Type_t>::value);

	trace_out_private__define_has_members(x_y_z, Type_t,
		has_member_x<Type_t>::value && has_member_y<Type_t>::value && has_member_z<Type_t>::value &&
		!has_member_w<Type_t>::value);

	trace_out_private__define_has_members(X_Y_Z, Type_t,
		has_member_X<Type_t>::value && has_member_Y<Type_t>::value && has_member_Z<Type_t>::value &&
		!has_member_W<Type_t>::value);

	trace_out_private__define_has_members(x_y_z_w, Type_t,
		has_member_x<Type_t>::value && has_member_y<Type_t>::value && has_member_z<Type_t>::value && has_member_w<Type_t>::value);

	trace_out_private__define_has_members(X_Y_Z_W, Type_t,
		has_member_X<Type_t>::value && has_member_Y<Type_t>::value && has_member_Z<Type_t>::value && has_member_W<Type_t>::value);

	trace_out_private__define_has_members(width_height, Type_t,
		has_member_width<Type_t>::value && has_member_height<Type_t>::value &&
		!has_member_x<Type_t>::value && !has_member_y<Type_t>::value && !has_member_X<Type_t>::value && !has_member_Y<Type_t>::value);

	trace_out_private__define_has_members(Width_Height, Type_t,
		has_member_Width<Type_t>::value && has_member_Height<Type_t>::value &&
		!has_member_x<Type_t>::value && !has_member_y<Type_t>::value && !has_member_X<Type_t>::value && !has_member_Y<Type_t>::value);

	trace_out_private__define_has_members(x_y_width_height, Type_t,
		has_member_x<Type_t>::value && has_member_y<Type_t>::value && has_member_width<Type_t>::value && has_member_height<Type_t>::value);

	trace_out_private__define_has_members(x_y_Width_Height, Type_t,
		has_member_x<Type_t>::value && has_member_y<Type_t>::value && has_member_Width<Type_t>::value && has_member_Height<Type_t>::value);

	trace_out_private__define_has_members(X_Y_Width_Height, Type_t,
		has_member_X<Type_t>::value && has_member_Y<Type_t>::value && has_member_Width<Type_t>::value && has_member_Height<Type_t>::value);

	trace_out_private__define_has_members(origin_size, Type_t,
		has_member_origin<Type_t>::value && has_member_size<Type_t>::value);

	trace_out_private__define_has_members(real_imag, Type_t,
		has_member_real<Type_t>::value && has_member_imag<Type_t>::value);

	trace_out_private__define_has_members(begin_end, Type_t,
		has_member_begin<Type_t>::value && has_member_end<Type_t>::value &&
		!has_member_GetCharArray<Type_t>::value);


	//
	// WinApi

	// SIZE
	trace_out_private__define_has_members(cx_cy, Type_t,
		has_member_cx<Type_t>::value && has_member_cy<Type_t>::value);

	// RECTs
	trace_out_private__define_has_members(left_top_right_bottom, Type_t,
		has_member_left<Type_t>::value && has_member_top<Type_t>::value && has_member_right<Type_t>::value && has_member_bottom<Type_t>::value);


	//
	// Unreal Engine

	trace_out_private__define_has_members(Key_Value, Type_t,
		has_member_Key<Type_t>::value && has_member_Value<Type_t>::value);

	// FTwoVectors
	trace_out_private__define_has_members(v1_v2, Type_t,
		has_member_v1<Type_t>::value && has_member_v2<Type_t>::value);

	// FRay
	trace_out_private__define_has_members(Origin_Direction, Type_t,
		has_member_Origin<Type_t>::value && has_member_Direction<Type_t>::value);

	// FEdge
	trace_out_private__define_has_members(Vertex_Count, Type_t,
		has_member_Vertex<Type_t>::value && has_member_Count<Type_t>::value);

	// FRotator
	trace_out_private__define_has_members(Pitch_Roll_Yaw, Type_t,
		has_member_Pitch<Type_t>::value && has_member_Roll<Type_t>::value && has_member_Yaw<Type_t>::value);

	// TRange
	trace_out_private__define_has_members(GetLowerBound_GetUpperBound, Type_t,
		has_member_GetLowerBound<Type_t>::value && has_member_GetUpperBound<Type_t>::value);

	// TRangeBound
	trace_out_private__define_has_members(GetValue_IsExclusive_IsInclusive_IsOpen, Type_t,
		has_member_GetValue<Type_t>::value && has_member_IsExclusive<Type_t>::value && has_member_IsInclusive<Type_t>::value && has_member_IsOpen<Type_t>::value);

	// FBox2D
	trace_out_private__define_has_members(Min_Max_bIsValid, Type_t,
		has_member_Min<Type_t>::value && has_member_Max<Type_t>::value && has_member_bIsValid<Type_t>::value);

	// FBox
	trace_out_private__define_has_members(Min_Max_IsValid, Type_t,
		has_member_Min<Type_t>::value && has_member_Max<Type_t>::value && has_member_IsValid<Type_t>::value);

	// FSphere
	trace_out_private__define_has_members(Center_W, Type_t,
		has_member_Center<Type_t>::value && has_member_W<Type_t>::value);

	// FCapsuleShape
	trace_out_private__define_has_members(Center_Radius_Orientation_Length, Type_t,
		has_member_Center<Type_t>::value && has_member_Radius<Type_t>::value && has_member_Orientation<Type_t>::value && has_member_Length<Type_t>::value);

	// FOrientedBox
	trace_out_private__define_has_members(Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ, Type_t,
		has_member_Center<Type_t>::value && has_member_AxisX<Type_t>::value && has_member_AxisY<Type_t>::value && has_member_AxisZ<Type_t>::value && has_member_ExtentX<Type_t>::value && has_member_ExtentY<Type_t>::value && has_member_ExtentZ<Type_t>::value);

	// FBoxSphereBounds
	trace_out_private__define_has_members(Origin_BoxExtent_SphereRadius, Type_t,
		has_member_Origin<Type_t>::value && has_member_BoxExtent<Type_t>::value && has_member_SphereRadius<Type_t>::value);

	// FString
	trace_out_private__define_has_members(GetCharArray, Type_t,
		has_member_GetCharArray<Type_t>::value);

#undef trace_out_private__define_has_members


	template <typename Type_t>
	struct has_supported_members
	{
		enum
		{
			value =
				has_members_x_y<Type_t>::value ||
				has_members_X_Y<Type_t>::value ||
				has_members_x_y_z<Type_t>::value ||
				has_members_X_Y_Z<Type_t>::value ||
				has_members_x_y_z_w<Type_t>::value ||
				has_members_X_Y_Z_W<Type_t>::value ||
				has_members_width_height<Type_t>::value ||
				has_members_Width_Height<Type_t>::value ||
				has_members_x_y_width_height<Type_t>::value ||
				has_members_x_y_Width_Height<Type_t>::value ||
				has_members_X_Y_Width_Height<Type_t>::value ||
				has_members_origin_size<Type_t>::value ||
				has_members_real_imag<Type_t>::value ||
				has_members_cx_cy<Type_t>::value ||
				has_members_left_top_right_bottom<Type_t>::value ||
				has_members_Key_Value<Type_t>::value ||
				has_members_v1_v2<Type_t>::value ||
				has_members_Origin_Direction<Type_t>::value ||
				has_members_Vertex_Count<Type_t>::value ||
				has_members_Pitch_Roll_Yaw<Type_t>::value ||
				has_members_GetLowerBound_GetUpperBound<Type_t>::value ||
				has_members_GetValue_IsExclusive_IsInclusive_IsOpen<Type_t>::value ||
				has_members_Min_Max_bIsValid<Type_t>::value ||
				has_members_Min_Max_IsValid<Type_t>::value ||
				has_members_Center_W<Type_t>::value ||
				has_members_Center_Radius_Orientation_Length<Type_t>::value ||
				has_members_Center_AxisX_AxisY_AxisZ_ExtentX_ExtentY_ExtentZ<Type_t>::value ||
				has_members_Origin_BoxExtent_SphereRadius<Type_t>::value ||
				has_members_GetCharArray<Type_t>::value
		};
	};


	template <typename Type_t>
	struct is_iterable
	{
		enum
		{
			value = has_members_begin_end<Type_t>::value && !is_same<Type_t, std::string>::value
		};
	};

}
}

