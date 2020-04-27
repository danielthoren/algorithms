
#include <vector>
#include <utility>

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
    struct interval_sort
    {
 	bool operator()(std::pair<T,T> const& i1, std::pair<T,T> const& i2);
    };
    
public:

    Interval_cover() = default;

    Interval_cover(std::vector<std::pair<T, T>> const& intervals) : intervals(intervals)
	{	    
	    sort(this->intervals.begin(), this->intervals.end(), interval_sort());
	}

    /**
     * Adds a new interval keeping the internal vector sorted
     *
     * interval: The interval to be inserted
     */
    void add_interval(std::pair<T, T> const& interval);

    /**
     * Gets the interval needed to cover a point
     *
     * Complexity: O(n)
     *
     * target: The point to cover
     *
     * return: Returns the interval that covers the point. If no
     *         interval covers the point then returns 
     *         { numeric_limits<T>::max(), numeric_limits<T>::max() }
     */
    std::pair<T,T> cover_point(T target);

    /**
     * Calculates the minimum amount of intervals that covers the target
     * and then returns those intervals
     *
     * Complexity: O(n)
     *
     * target   : The interval to cover
     * intervals: The intervals to cover target with. 
     *            If it cant be covered then returns an empty vector
     */
    std::vector<std::pair<T,T>> cover_interval(std::pair<T, T> const& target);
    
private:
    std::vector<std::pair<T,T>> intervals;
};

#include "interval_cover.tcc"

#endif
