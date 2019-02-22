#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

struct preference
{
    int pref;
    int val;
};

vector<vector<preference>> get_data()
{
    int priests;
    cin >> priests;

    vector<vector<preference>> data;
    for (int i{0}; i < priests; i++)
    {
	data.push_back({});
	for (int j{0}; j < 8; j++)
	{
	    preference pref_data;
	    cin >> pref_data.pref;
	    pref_data.val = j;
	    data.at(i).push_back(pref_data);
	}
	sort(data[i].begin(), data[i].end(), [] (preference p1, preference p2)
	     {
		 return p1.pref < p2.pref;
	     });	
    }
    return data;
}

vector<int> get_vote(vector<preference>& priest_preference, map<int, int>& final_outcome,  map<int, vector<int>> const& neighbours)
{
    vector<int> outcome{};
    for (int data_in{0}; data_in < 8; data_in++)
    {
	for (struct preference p : priest_preference)
	{
	    auto it = find(neighbours.at(data_in).begin(), neighbours.at(data_in).end(), final_outcome.at(p.val));
	    if (it != neighbours.at(data_in).end())
	    {
		outcome.push_back(final_outcome.at(p.val));
		break;
	    }
	}
	if (outcome.size() - 1 != data_in)
	{
	    outcome.push_back(data_in);
	}
    }
    return outcome;
}

void calc_final_outcome(vector<int>& priest_voting, map<int, int>& final_outcome)
{
    for (int i{0}; i < 8; i++)
    {
	//Find index at which element i lies
	int index{-1};
	for (int j{0}; j < 8; j++)
	{
	    if (priest_voting.at(j) == i)
	    {
		index = j;
		break;
	    }
	}

	final_outcome.at(i) = index;
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
    
    int rounds_count;
    cin >> rounds_count;

    for (int round{0}; round < rounds_count; round++)
    {
    	vector<vector<preference>> priest_preference = get_data();
    	vector<vector<int>> priest_voting{};
	map <int, int> final_outcome{ {0,0},{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7} }; // {wanted outcome, needed vote}
	
    	for (int priest{priest_preference.size() - 1}; priest >= 0; priest--)
    	{
    	    priest_voting.push_back(get_vote(priest_preference[priest], final_outcome, neighbours));

	    if (priest > 0)
		calc_final_outcome(priest_voting.at(priest_voting.size() - 1), final_outcome);
    	}

	//reverse(priest_voting.begin(), priest_voting.end());
    	int state{0};
    	for (vector<int> priest : priest_voting)
    	{
    	    state = priest.at(state); 
    	}
    	cout << data_map.at(state + 1) << endl;
    }


    return 0;
}
