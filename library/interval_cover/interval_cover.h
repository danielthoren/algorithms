
#include <vector>
#include <utility>

#ifndef INTERVAL_COVER
#define INTERVAL_COVER
/**
 * Author: Daniel Thorén
 */
template <typename T>
class Interval_cover
{
private:
    /**
     * Structure used for keeping track of original index meaning the
     * index in the original vector
     */
    struct Interval
    {
	T first, second;
	int orig_index;
    };

    /**
     * Comparator used to sort the intervals
     */
    struct
    {
	bool operator()(Interval& i1, Interval& i2)
	    {
		if (i1.first == i2.first)
		    return i1.second > i2.second;
		return i1.first < i2.first;
	    }
    } interval_sort;
    
public:

    Interval_cover() = default;

    Interval_cover(std::vector<std::pair<T, T>> const& intervals) : intervals_copy{}
	{
	    for (int i = 0; i < (int) intervals.size(); i++)
	    {
		intervals_copy.push_back(
		    Interval{intervals[i].first, intervals[i].second, i});
	    }
	    sort_intervals();
	}

    /**
     * Adds a new interval keeping the internal vector sorted. The new
     * interval is assumed to be last in the original list and thus
     * will be indexed as such in the answer. This value is returned
     * by the function
     *
     * interval: The interval to be inserted
     *
     * return : The index in the original list that will be used to
     *          reference the interval in the answer(last index in the list)
     */
    int add_interval(std::pair<T, T> const& interval)
	{
	    int orig = intervals_copy.size();
	    Interval add{interval.first, interval.second, orig};
	    auto it = std::lower_bound<Interval>(intervals_copy.begin(), intervals_copy.end(), add, interval_sort);

	    intervals_copy.insert(it, add);
	    return orig;
	}

    /**
     * Gets the interval needed to cover a point
     *
     * Complexity: O(n)
     *
     * target: The point to cover
     *
     * return: Returns a vector containing the original index of the
     *         first interval that covers the point.
     */
    std::vector<int> cover_point(T target)
	{	    
	    for (auto it = intervals_copy.begin(); it != intervals_copy.end(); it++)
	    {
		if (it->first <= target && it->second >= target)
		{
		    return {it->orig_index};
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
    std::vector<int> cover_interval(std::pair<T, T> const& target)
	{	    
	    if (intervals_copy.size() == 0)
		return {};

	    if (target.first == target.second)
		return cover_point(target.first);

	    T position{target.first};
	    Interval best{};
	    best.orig_index = -1;
	    std::vector<int> result{};
	    int index = 0;

	    if (intervals_copy[0].first > target.first)
		return {};

	    do
	    {
		for (unsigned int i = index;
		     i < intervals_copy.size() && intervals_copy[i].first <= position;
		     i++)
		{
		    if (best.orig_index == -1 || (intervals_copy[i].second > position &&
						  (intervals_copy[i].second - position) > (best.second - position)))
		    {
			best = intervals_copy[i];
			index = i;

			if (best.second >= target.second)
			{
			    result.push_back(best.orig_index);
			    return result;
			}
		    }
		}

		if (result.size() == 0 || (result.size() != 0 && best.orig_index != result[result.size() - 1]))
		{
		    result.push_back(best.orig_index);
		    position = best.second;
		}
		else
		    return {};
	
	    } while (position < target.second);

	    if (best.second < target.second ||
		(result.size() > 0 && get_by_orig_index(result[0]).first > target.first))
		return {};

	    return result;	    
	}

    /**
     * Fetches a interval using the index in the original list.
     */
    std::pair<T,T> get_by_orig_index(int index)
	{
	    for (Interval& in : intervals_copy)
	    {
		if (in.orig_index == index)
		    return {in.first, in.second};
	    }
	    return {};
	}
    
private:

    /**
     * Sorts the intervals in increasing order. Intervals must be
     * sorted before using cover_point and cover_interval. The class
     * keeps track of weather the intervals are sorted or not using a
     * bool. This method is automatically called if needed.
     */
    void sort_intervals()
	{
	    sort(intervals_copy.begin(), intervals_copy.end(), interval_sort);	   
	}
    std::vector<Interval> intervals_copy;
};



#include "interval_cover.tcc"

#endif
