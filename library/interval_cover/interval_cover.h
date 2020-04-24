
#include <vector>
#include <utility>
#include <limits>

#ifndef INTERVAL_COVER
#define INTERVAL_COVER
/**
 * Author: Daniel Thorén
 *
 * Class with functionality for interval cover. The internal vector
 * "intervals" contains the intervals operated on.
 */
template <typename T>
class Interval_cover
{
private:

    /**
     * Comparator used to sort the intervals
     */
    struct
    {
	bool operator()(std::pair<T,T> const& i1, std::pair<T,T> const& i2)
	    {
		if (i1.first == i2.first)
		    return i1.second > i2.second;
		return i1.first < i2.first;
	    }
    } interval_sort;
    
public:

    Interval_cover() = default;

    Interval_cover(std::vector<std::pair<T, T>> const& intervals) : intervals(intervals)
	{	    
	    sort(this->intervals.begin(), this->intervals.end(), interval_sort);
	}

    /**
     * Adds a new interval keeping the internal vector sorted
     *
     * interval: The interval to be inserted
     */
    void add_interval(std::pair<T, T> const& interval)
	{
	    auto it = std::lower_bound<std::pair<T,T>>(intervals.begin(), intervals.end(), interval, interval_sort);

	    intervals.insert(it, interval);
	}

    /**
     * Gets the interval needed to cover a point
     *
     * Complexity: O(n)
     *
     * target: The point to cover
     *
     * return: Returns the interval that covers the point
     */
    std::pair<T,T> cover_point(T target)
	{	    
	    for (auto it = intervals.begin(); it != intervals.end(); it++)
	    {
		if (it->first <= target && it->second >= target)
		{
		    return *it;
		}
	    }
	    return {};
	}

    /**
     * Calculates the minimum amount of intervals that covers the target
     * and then returns those intervals
     *
     * Complexity: O(n)
     *
     * target   : The interval to cover
     * intervals: The intervals to cover target with 
     */
    std::vector<std::pair<T,T>> cover_interval(std::pair<T, T> const& target)
	{	    
	    if (intervals.size() == 0)
		return {};

	    if (target.first == target.second)
		return std::vector<std::pair<T,T>>{cover_point(target.first)};

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
    
private:
    std::vector<std::pair<T,T>> intervals;
};



#include "interval_cover.tcc"

#endif
