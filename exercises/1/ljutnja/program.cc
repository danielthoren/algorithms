#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

int demand(pair<int, int> &child)
{
    return child.first - child.second;
}

void print_list(vector<pair<int, int>>& list)
{
    cout << "Children: " << endl;
    for (auto child : list)
	cout << "{" << child.first << ", " << child.second << "}" << endl;
    cout << endl;
}

int main()
{
    int children;
    int candies;

    cin >> candies >> children;

    // cout << "Candies: " << candies << endl;

    vector<int> indata;
    for (int i = 0; i < children; i++)
    {
	int demand;
	cin >> demand;
	indata.push_back(demand);
    }
    
    sort(indata.begin(), indata.end());

    vector<pair<int, int>> demand;
    int count = 1;    
    for (int i = 1; i < children; i++)
    {
	if (indata[i-1] != indata[i])
	{
	    demand.push_back({indata[i-1], count});
	    count = 1;
	}
	else
	    count++;
    }
    demand.push_back({indata[indata.size() - 1], count});
    
    int last_index = demand.size() - 1;
    while (candies > 0)
    {
	// cout << "remaining candy: " << candies << endl;
	// print_list(demand);	

	int demand_diff = demand[last_index].first - demand[last_index - 1].first;
	// cout << "demand_diff: " << demand_diff << endl;
	int candy = clamp(demand[last_index].second * demand_diff, 0, candies);

	candies -= candy;
	if ((candy == 0 && candies / demand[last_index].second > 0) || demand.size() == 0)
	{
	    demand[last_index].first--;
	    candies -= demand[last_index].second;
	}
	else if (candy == 0)
	{
	    demand.push_back({demand[last_index].first - 1, candy});
	    demand[last_index].second -= candy;
	    candies -= candy;
	}
	else
	{
	    demand[last_index - 1].second += demand[last_index].second;
	    demand.pop_back();
	    last_index--;
	}	
    }
    
    int anger = 0;
    for (auto child : demand)
	anger += (pow(child.first, 2) * child.second);

    cout << anger;
}
