#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

void print_list(vector<pair<unsigned long, unsigned long>>& list)
{
    cout << "Children: " << endl;
    for (auto child : list)
	cout << "{" << child.first << ", " << child.second << "}" << endl;
    cout << endl;
}

int main()
{
    long long children;
    long long candies;

    cin >> candies >> children;

    // cout << "Candies: " << candies << endl;

    vector<pair<unsigned long, unsigned long>> indata;
    long long total_demand = 0;
    for (unsigned int i = 0; i < children; i++)
    {
	unsigned long demand;
	cin >> demand;
	total_demand += demand;
	indata.push_back({demand, 0});
    }
    long long unsatisfied_demand = total_demand - candies;
    // cout << "unsatidfied_demand: " << unsatisfied_demand << endl;
    
    sort(indata.begin(), indata.end(), [] (pair<unsigned long, unsigned long> p1, pair<unsigned long, unsigned long> p2)
	 {
	     return p1.first < p2.first;
	 });

    for (unsigned int i = 0; i < indata.size(); i++)
    {
	unsigned long dist = unsatisfied_demand / (indata.size() - i);
	unsigned long anger = clamp<unsigned long>(dist, 0, indata[i].first);
	unsatisfied_demand -= anger;
	indata[i].second = anger;
	// cout << "Remaining demand: " << unsatisfied_demand << endl;
	// print_list(indata);
    }

    // print_list(indata);

    unsigned long long anger = 0;
    for (pair<unsigned long, unsigned long> p : indata)
	anger += p.second * p.second;

    cout << anger;
    
}
