#pragma once

#include <cassert>
#include <utility>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <vector>

#include "trace-out/standard/integer.hpp"


namespace trace_out { namespace detail
{

	template <typename Type_t>
	struct valdist_t
	{
		Type_t value;
		unsigned int occurances;

		valdist_t(Type_t value, unsigned int occurances);
	};


	template <typename Type_t>
	struct compare_distributions
	{
		bool operator ()(const valdist_t<Type_t> &first, const valdist_t<Type_t> &second);
	};


	template <typename Type_t, typename Iterator_t>
	Type_t average_value(Iterator_t begin, Iterator_t end);

	template <typename Type_t, typename Iterator_t>
	Type_t median_value(Iterator_t begin, Iterator_t end);

	template <typename Type_t, typename Iterator_t>
	std::vector<valdist_t<Type_t> > values_distribution(Iterator_t begin, Iterator_t end);

	template <typename Type_t, typename Iterator_t>
	std::pair<std::vector<Type_t>, unsigned int> mode_values(Iterator_t begin, Iterator_t end);

}
}


namespace trace_out { namespace detail
{

	template <typename Type_t>
	valdist_t<Type_t>::valdist_t(Type_t value, unsigned int occurances)
		:
		value(value),
		occurances(occurances)
	{
	}


	template <typename Type_t>
	bool compare_distributions<Type_t>::operator ()(const valdist_t<Type_t> &first, const valdist_t<Type_t> &second)
	{
		return first.occurances < second.occurances;
	}


	template <typename Type_t, typename Iterator_t>
	Type_t average_value(Iterator_t begin, Iterator_t end)
	{
		Type_t full_time = std::accumulate(begin, end, Type_t(0));
		return static_cast<Type_t>(full_time) / static_cast<Type_t>(std::distance(begin, end));
	}


	template <typename Type_t, typename Iterator_t>
	Type_t median_value(Iterator_t begin, Iterator_t end)
	{
		assert(begin != end);

		typename Iterator_t::difference_type size = std::distance(begin, end);
		assert(size > 0);

		std::size_t half_size = static_cast<std::size_t>(size / 2);
		if (size % 2 == 0)
		{
			Iterator_t next = begin;
			std::advance(begin, half_size - 1);
			std::advance(next, half_size);
			return static_cast<Type_t>(*begin + *next) / Type_t(2);
		}
		else
		{
			std::advance(begin, half_size);
			return static_cast<Type_t>(*begin);
		}
	}


	template <typename Type_t, typename Iterator_t>
	std::vector<valdist_t<Type_t> > values_distribution(Iterator_t begin, Iterator_t end)
	{
		if (begin == end)
		{
			return std::vector<valdist_t<Type_t> >();
		}

		std::vector<valdist_t<Type_t> > distributions;
		Type_t current_value = *begin;
		distributions.push_back(valdist_t<Type_t>(current_value, 1));

		for (++begin; begin != end; ++begin)
		{
			if (*begin != current_value)
			{
				current_value = *begin;
				distributions.push_back(valdist_t<Type_t>(current_value, 1));
				continue;
			}

			++(distributions.back().occurances);
		}

		return distributions;
	}


	template <typename Type_t, typename Iterator_t>
	std::pair<std::vector<Type_t>, unsigned int> mode_values(Iterator_t begin, Iterator_t end)
	{
		std::vector<valdist_t<standard::uint64_t> > distributions = values_distribution<standard::uint64_t>(begin, end);

		unsigned int max_occurances = std::max_element(distributions.begin(), distributions.end(), compare_distributions<Type_t>())->occurances;
		std::vector<Type_t> modes;
		for (typename std::vector<valdist_t<Type_t> >::const_iterator itr = distributions.cbegin(); itr != distributions.cend(); ++itr)
		{
			if (itr->occurances == max_occurances)
			{
				modes.push_back(itr->value);
			}
		}

		return std::pair<std::vector<Type_t>, unsigned int>(modes, max_occurances);
	}

}
}
