#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;
#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

vector<int> cover(pair<double, double>& target,
		  vector<pair<double, double>>& intervals)
{

    if (intervals.size() == 0)
	return {};
    
    vector<vector<double>> intervals_copy;
    for (int i = 0; i < (int) intervals.size(); i++)
    {
	intervals_copy.push_back(
	    vector<double>{intervals[i].first, intervals[i].second, (double) i});
    }

    sort(intervals_copy.begin(), intervals_copy.end(),
	 [] (vector<double>& vec1, vector<double>& vec2)
	 {
	     if (vec1[0] == vec2[0])
		 return vec1[1] > vec2[1];
	     return vec1[0] < vec2[0];
	 });

    double position{target.first};
    vector<double> best{};
    vector<int> result{};
    int index = 0;

    if (intervals_copy[0][0] > target.first)
	return {};

    do
    {
	for (unsigned int i = index;
	     i < intervals_copy.size() && intervals_copy[i][0] <= position;
	     i++)
	{
	    if (best.size() == 0 || (intervals_copy[i][1] > position &&
	       (intervals_copy[i][1] - position) > (best[1] - position)))
	    {
		best = intervals_copy[i];
		index = i;

		if (best[1] >= target.second)
		{
		    result.push_back(best[2]);
		    return result;
		}		    
	    }
	}

	if (result.size() == 0 || (result.size() != 0 && best[2] != result[result.size() - 1]))
	{
	    result.push_back(best[2]);
	    position = best[1];
	}
	else
	    return {};
	
    } while (position < target.second);

    if (best[1] < target.second ||
    	(result.size() > 0 &&intervals[result[0]].first > target.first))
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
		cout << i << " ";
	    }
	    cout << res[res.size() - 1] << endl;
	}
    }
}

