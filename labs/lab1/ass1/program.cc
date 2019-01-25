#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> cover(pair<float, float>& target, vector<pair<float, float>>& intervals)
{
    sort(intervals.begin(), intervals.end(), [] (pair<float, float>& p1, pair<float, float>& p2)
	 {
	     if (p1.first == p2.first)
		 return p1.second > p2.second;
	     return p1.first < p2.first;
	 });

    if (intervals.size() == 0 || intervals[0].first > target.first)
	return vector<int>{};

    vector<int> result;
    int optimal{-1};
    float pos = target.first;
    for (int i = 0; i < intervals.size(); i++)
    {	
	if (optimal == -1 || (intervals[i].first <= pos &&
			      (intervals[i].second - pos) > (intervals[optimal].second - pos)))
	{
	    optimal = i;
	    pos = intervals[optimal].second;
	}
	if (i != optimal && intervals[i].first >= intervals[optimal].first)
	{
	    result.push_back(optimal);
	}
    }
    result.push_back(optimal);

    if (intervals[optimal].second < target.second)
	return vector<int>{};
    return result;
}

int main()
{
    pair<float, float> target_interval;
    cin >> target_interval.first >> target_interval.second;

    int count;
    cin >> count;

    vector<pair<float, float>> intervals;
    for (int i = 0; i < count; i++)
    {
	pair<float, float> interval;
	cin >> interval.first >> interval.second;
	intervals.push_back(interval);	
    }

    vector<int> res = cover(target_interval, intervals);
    
    if (res.size() == 0)
    {
	cout << "impossible" << endl;
    }
    else{
	cout << res.size() << endl;

	for (int i : res)
	    cout << i << " ";
	cout << endl;
    }
}
