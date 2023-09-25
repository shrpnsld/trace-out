#pragma once

struct fit
{
	template <typename Type_t>
	operator Type_t () const
	{
		return Type_t();
	}
};
