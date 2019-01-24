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

    vector<pair<int, int>> child_demand;
    for (int i = 0; i < children; i++)
    {
	pair<int, int> demand;
	cin >> demand.first;
	demand.second = 0;
	child_demand.push_back(demand);
    }

    sort(child_demand.begin(), child_demand.end(),
	 [] (pair<int, int> p1, pair<int, int> p2)
	 {
	     return p1.first < p2.first;
	 });

    int last_index = child_demand.size() - 1;
    while (candies > 0)
    {
	// cout << "remaining candy: " << candies << endl;
	// print_list(child_demand);	

	int candy = clamp(demand(child_demand[last_index]) - demand(child_demand[last_index - 1]) + 1, 0, candies);
	
	child_demand[last_index].second += candy;
	candies -= candy;

	sort(child_demand.begin(), child_demand.end(),
	     [] (pair<int, int> p1, pair<int, int> p2)
	     {
		 return demand(p1) < demand(p2);
	     });
    }
    // print_list(child_demand);	
    // cout << "final candies: " << candies << endl;
    
    int anger = 0;
    for (auto child : child_demand)
	anger += pow(demand(child), 2);

    cout << anger;
}
