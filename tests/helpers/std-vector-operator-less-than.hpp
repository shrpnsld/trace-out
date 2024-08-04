#include <algorithm>
#include <vector>

template <typename Type_t>
bool operator <(const std::vector<Type_t> &first, const std::vector<Type_t> &second)
{
	auto first_itr {first.begin()};
	auto second_itr {second.begin()};
	for ( ; first_itr != first.end() && second_itr != second.end(); ++first_itr, ++second_itr)
	{
		const Type_t &first_value {*first_itr};
		const Type_t &second_value {*second_itr};
		if (first_value >= second_value)
		{
			return false;
		}
	}

	if (first_itr != first.end())
	{
		return false;
	}

	return true;
}

