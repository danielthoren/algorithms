#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

inline bool check_insert(vector<float> best, float position,
			 vector<int> result, vector<float> elem)
{
    if (best[0] <= position && best[1] >= position && elem.at(0) > position)
	return (!(result.size() > 0 && result[result.size() - 1] == best[2]));
    return false;
}

vector<int> cover(pair<float, float>& target,
		  vector<pair<float, float>>& intervals)
{

    if (intervals.size() == 0)
	return {};
    
    vector<vector<float>> intervals_copy;
    for (int i = 0; i < (int) intervals.size(); i++)
    {
	intervals_copy.push_back(
	    vector<float>{intervals[i].first, intervals[i].second, (float) i});
    }

    sort(intervals_copy.begin(), intervals_copy.end(),
	 [] (vector<float>& vec1, vector<float>& vec2)
	 {
	     if (vec1[0] == vec2[0])
		 return vec1[1] > vec2[1];
	     return vec1[0] < vec2[0];
	 });

    float position{target.first};
    vector<float> best{intervals_copy[0]};
    vector<int> result{};

    for (auto it = intervals_copy.begin();
	 it != intervals_copy.end(); it++)
    {
	if(check_insert(best, position, result, *it))
	{
	    result.push_back((int) best[2]);
	    position = best[1];
	}
	
	if ((it->at(0) <= position && it->at(1) >= position &&
	     (it->at(1) - position) > (best[1] - position)) ||
	    best[1] < position)
	{
	    best = *it;
	}
    }

    if (check_insert(best, position, result,
		     intervals_copy[intervals_copy.size() - 1]) ||
	target.first == target.second)
    {
	if (!(result.size() > 0 && result[result.size() - 1] == best[2]))
	{
	    result.push_back((int) best[2]);
	}
    }

    if (best[1] < target.second ||
	(result.size() > 0 &&intervals[result[0]].first > target.first))
	return {};

    return result;
}

int main()
{
    pair<float, float> target_interval;


    while (cin >> target_interval.first >> target_interval.second)
    {

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
	else
	{
	    cout << res.size() << endl;

	    for (int i : res)
		cout << i << " ";
	    cout << endl;
	}
    }
}
