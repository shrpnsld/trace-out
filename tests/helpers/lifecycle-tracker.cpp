#include "lifecycle-tracker.hpp"
#include <cassert>

std::unordered_map<const lifecycle_tracker *, typename lifecycle_tracker::statistics> lifecycle_tracker::_all_statistics;

lifecycle_tracker::lifecycle_tracker()
{
	++_all_statistics[this].default_constructed;
}

lifecycle_tracker::lifecycle_tracker(const lifecycle_tracker &)
{
	++_all_statistics[this].copy_constructed;
}

lifecycle_tracker::lifecycle_tracker(lifecycle_tracker &&)
{
	++_all_statistics[this].move_constructed;
}


lifecycle_tracker::~lifecycle_tracker()
{
	++_all_statistics[this].destructed;
}

lifecycle_tracker &lifecycle_tracker::operator =(const lifecycle_tracker &)
{
	++_all_statistics[this].copy_assigned;
	return *this;
}

lifecycle_tracker &lifecycle_tracker::operator =(lifecycle_tracker &&)
{
	++_all_statistics[this].move_assigned;
	return *this;
}

const lifecycle_tracker::statistics &lifecycle_tracker::statistics_for(const lifecycle_tracker *object)
{
	auto place {_all_statistics.find(object)};
	if (place == _all_statistics.end())
	{
		bool ok;
		std::tie(place, ok) = _all_statistics.emplace(object, statistics {});
		assert(ok);
	}

	return place->second;
}

lifecycle_tracker::statistics::statistics()
	:
	default_constructed {0},
	copy_constructed {0},
	move_constructed {0},
	destructed {0},
	copy_assigned {0},
	move_assigned {0}
{
}

