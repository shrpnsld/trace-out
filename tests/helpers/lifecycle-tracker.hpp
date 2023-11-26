#pragma once

#include <cstdint>
#include <unordered_map>

class lifecycle_tracker
{
public:
	class statistics
	{
		friend class lifecycle_tracker;

	public:
		statistics();

		std::uint32_t default_constructed;
		std::uint32_t copy_constructed;
		std::uint32_t move_constructed;
		std::uint32_t destructed;
		std::uint32_t copy_assigned;
		std::uint32_t move_assigned;
	};

public:
    lifecycle_tracker();
    lifecycle_tracker(const lifecycle_tracker &);
    lifecycle_tracker(lifecycle_tracker &&);
    ~lifecycle_tracker();

    lifecycle_tracker &operator =(const lifecycle_tracker &);
    lifecycle_tracker &operator =(lifecycle_tracker &&);

	static const statistics &statistics_for(const lifecycle_tracker *object);

private:
	static std::unordered_map<const lifecycle_tracker *, statistics> _all_statistics;
};

