#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

vector<int> cover(pair<float, float>& target, vector<pair<float, float>>& intervals)
{

    if (intervals.size() == 0)
	return {};
    
    vector<vector<float>> intervals_copy;
    for (int i = 0; i < (int) intervals.size(); i++)
    {
	intervals_copy.push_back(vector<float>{intervals[i].first, intervals[i].second, (float) i});
    }

    sort(intervals_copy.begin(), intervals_copy.end(), [] (vector<float>& vec1, vector<float>& vec2)
	 {
	     if (vec1[0] == vec2[0])
		 return vec1[1] > vec2[1];
	     return vec1[0] < vec2[0];
	 });

    float position{intervals_copy[0][1]};
    vector<int> result{(int) intervals_copy[0][2]};

    // for (auto elem: intervals_copy)
    // 	cout << "{" << elem[0] << ", " << elem[1] << "}, ";

    int index = 1;
    while (intervals_copy[result[result.size() - 1]][2] < target.second)
    {
	vector<float> best{intervals_copy[index]};
	for (auto it = intervals_copy.begin(); it != intervals_copy.end(); it++)
	{
	    if (it->at(0) > intervals_copy[result[result.size() - 1]][0])
	    {
		result.push_back(best[2]);
		index = best[2];
		break;
	    }
	    
	    if (it->at(0) <= intervals_copy[result[result.size() - 1]][0] && it->at(1) > best[1])
	    {
		best = *it;
	    }
	}
    }
    
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
