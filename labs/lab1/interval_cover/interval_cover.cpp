#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

#include "interval_cover.h"

int main()
{
    pair<double, double> target_interval;
    
    while (cin >> target_interval.first >> target_interval.second)
    {
	int count;
	cin >> count;

	map<pair<double, double>, int> interval_map;
	vector<pair<double, double>> intervals;
	for (int i = 0; i < count; i++)
	{
	    pair<double, double> interval;
	    cin >> interval.first >> interval.second;
	    interval_map[interval] = i;
	    intervals.push_back(interval);
	}

	Interval_cover<double> cover(intervals);

	vector<pair<double,double>> res = cover.cover_interval(target_interval);
    
	if (res.size() == 0)
	{
	    cout << "impossible" << endl;
	}
	else
	{
	    cout << res.size() << endl;

	    for (unsigned int i{0}; i < (res.size()- 1); i++)
	    {
		cout << interval_map[res[i]] << " ";
	    }
	    cout << interval_map[res[res.size() - 1]] << endl;
	}
    }
}

