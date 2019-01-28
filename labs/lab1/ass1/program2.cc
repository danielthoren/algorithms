#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

vector<int> help_cover(pair<float, float>& target, vector<vector<float>> intervals)
{
    if (target.second >= intervals[0][0])
	return {target[2]};
    else if (intervals.size() != 0)
	
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

	    for (unsigned int i{0}; i < (res.size()- 1); i++)
	    {
		cout << i << " ";
	    }
	    cout << res[res.size() - 1];
	}
    }
}
