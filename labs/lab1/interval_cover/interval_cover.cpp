#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

/**
 * Structure used for keeping track of original index meaning the
 * index in the original vector
 */
struct Interval
{
    double first, second;
    int orig_index;
};

/**
 * Gets the interval needed to cover a point
 *
 * Complexity: O(n)
 *
 * target          : The point to cover
 * sorted_intervals: The intervals to cover the point with. Must be sorted
 */
vector<int> cover_point(double target, vector<Interval> sorted_intervals)
{
    for (auto it = sorted_intervals.begin(); it != sorted_intervals.end(); it++)
	if (it->first <= target && it->second >= target)
	    return {it->orig_index};
    return {};
}

/**
 * Calculates the minimum amount of intervals that covers the target and then returns
 *
 * Complexity: O(n)
 *
 * target   : The interval to cover
 * intervals: The intervals to cover target with 
 */
vector<int> cover(pair<double, double>& target,
		  vector<pair<double, double>>& intervals)
{

    if (intervals.size() == 0)
	return {};
    
    vector<Interval> intervals_copy;
    for (int i = 0; i < (int) intervals.size(); i++)
    {
	intervals_copy.push_back(
	    Interval{intervals[i].first, intervals[i].second, i});
    }

    sort(intervals_copy.begin(), intervals_copy.end(),
	 [] (Interval& i1, Interval& i2)
	 {
	     if (i1.first == i2.first)
		 return i1.second > i2.second;
	     return i1.first < i2.first;
	 });

    if (target.first == target.second)
    	return cover_point(target.first, intervals_copy);

    double position{target.first};
    Interval best{};
    best.orig_index = -1;
    vector<int> result{};
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
    	(result.size() > 0 && intervals[result[0]].first > target.first))
    	return {};

    return result;
}

int main()
{
    pair<double, double> target_interval;


    while (cin >> target_interval.first >> target_interval.second)
    {

	int count;
	cin >> count;

	vector<pair<double, double>> intervals;
	for (int i = 0; i < count; i++)
	{
	    pair<double, double> interval;
	    cin >> interval.first >> interval.second;
	    intervals.push_back(interval);	
	}

	vector<int> res = cover(target_interval, intervals);
    
	if (res.size() == 0)
	{
	    cout << "impossible" << endl;
	}
	else
	{
	    cout << res.size() << endl;

	    for (unsigned int i{0}; i < (res.size()- 1); i++)
	    {
		cout << res[i] << " ";
	    }
	    cout << res[res.size() - 1] << endl;
	}
    }
}

