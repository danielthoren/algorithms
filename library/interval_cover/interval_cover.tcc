#include <limits>

#ifndef INTERVAL_COVER
#error 'interval_cover.tcc' is not supposed to be included directly. Include 'interval_cover.h' instead.
#endif

template <typename T>
bool Interval_cover<T>::interval_sort::operator()(std::pair<T,T> const& i1, std::pair<T,T> const& i2)
{
    if (i1.first == i2.first)
	return i1.second > i2.second;
    return i1.first < i2.first;
}

template <typename T>
void Interval_cover<T>::add_interval(std::pair<T, T> const& interval)
{
    auto it = std::lower_bound<std::pair<T,T>>(intervals.begin(), intervals.end(), interval, interval_sort());
    
    intervals.insert(it, interval);
}

template <typename T>
std::pair<T,T> Interval_cover<T>::cover_point(T target)
{	    
    for (auto it = intervals.begin(); it != intervals.end(); it++)
    {
	if (it->first <= target && it->second >= target)
	{
	    return *it;
	}
    }
    return {std::numeric_limits<T>::max(), std::numeric_limits<T>::max()};
}

template <typename T>
std::vector<std::pair<T,T>> Interval_cover<T>::cover_interval(std::pair<T, T> const& target)
{
    if (intervals.size() == 0)
	return {};

    if (target.first == target.second)
    {
	std::pair<T,T> result = {cover_point(target.first)};
	if (result.first == std::numeric_limits<T>::max() &&
	    result.second == std::numeric_limits<T>::max())
	{
	    return {};
	}
	return {result};
    }

    T position{target.first};
    std::pair<T,T> best{std::numeric_limits<T>::max(), std::numeric_limits<T>::max()};
    std::vector<std::pair<T,T>> result{};
    int index = 0;

    if (intervals[0].first > target.first)
	return {};

    do
    {
	for (unsigned int i = index;
	     i < intervals.size() && intervals[i].first <= position;
	     i++)
	{
	    if (best.first == std::numeric_limits<T>::max() || (intervals[i].second > position &&
								(intervals[i].second - position) > (best.second - position)))
	    {
		best = intervals[i];
		index = i;

		if (best.second >= target.second)
		{
		    result.push_back(best);
		    return result;
		}
	    }
	}

	if (result.size() == 0 || (result.size() != 0 && best != result[result.size() - 1]))
	{
	    result.push_back(best);
	    position = best.second;
	}
	else
	    return {};
	
    } while (position < target.second);

    if (best.second < target.second ||
	(result.size() > 0 && result[0].first > target.first))
	return {};

    return result;	    
}
