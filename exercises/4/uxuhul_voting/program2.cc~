#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Priest
{
    vector<int> preference;
    map<int, int> memory;
};

vector<Priest> get_data()
{
    int priest_count;
    cin >> priest_count;

    vector<Priest> priests;
    for (int i{0}; i < priest_count; i++)
    {
	Priest p;
	vector<pair<int,int>> input;
	for (int j{0}; j < 8; j++)
	{
	    int data;
	    cin >> data;
	    input.push_back({j, data});
	}

	sort(input.begin(), input.end(), [] (pair<int,int> p1, pair<int,int> p2) { return p1.second < p2.second; });

	p.preference.resize(input.size());
	transform(input.begin(), input.end(), p.preference.begin(), [] (pair<int,int> p) { return p.first; });
	
	priests.push_back(p);
    }
    return priests;
}

int get_vote(map<int, vector<int>> const& neighbours, vector<Priest>& priests, int priest_index, int state)
{
    if (priest_index == priests.size())
	return state;

    Priest& pr = priests.at(priest_index);
    vector<int> reachable = neighbours.at(state);

    vector<int> result(3);

    for (int i{0}; i < 3; i++)
    {
	// auto it = pr.memory.find(reachable[i]);
	// if (it != pr.memory.end())
	// {
	//     result.at(i) = it->second;
	// }
	// else
	// {
	    result.at(i) = get_vote(neighbours, priests, priest_index + 1, reachable[i]);
	//     pr.memory[reachable[i]] = result.at(i);
	// }
    }
    
    for (int pref : pr.preference)
    {
	for (int res{0}; res < 3; res++)
	    if (result.at(res) == pref)
		return reachable.at(res);
    }
}

int main()
{
    const map<int, vector<int>> neighbours{
	{0, {1,2,4}},
	{1, {0,3,5}},
	{2, {0,3,6}},
	{3, {1,2,7}},
	{4, {0,5,6}},
	{5, {1,4,7}},
	{6, {2,4,7}},
	{7, {3,5,6}}
    };

    const map<int, string> data_map{
    	{1, "NNN"},
    	{2, "NNY"},
    	{3, "NYN"},
    	{4, "NYY"},
    	{5, "YNN"},
    	{6, "YNY"},
    	{7, "YYN"},
    	{8, "YYY"}	
    };
    
    int tests;
    cin >> tests;   

    for (int t{0}; t < tests; t++)
    {
	vector<Priest> priests = get_data();
	cout << data_map.at(get_vote(neighbours, priests, 0, 0) + 1) << endl;
    }
    
}
