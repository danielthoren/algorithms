#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include <sstream>

#include "stringlib.h"

using namespace std;

void trim_string(string& str)
{
    //Remove leading blank spaces
    size_t start = str.find_first_not_of(' ');
    
    if (start != string::npos)
    	str = str.substr(start);

    size_t end = str.find_last_not_of(' ');

    //Remove trailing blank spaces
    if (end != string::npos)
    	str = str.substr(0, end+1);

    //Remove double blank spaces
    std::size_t doubleSpace = str.find("  ");
    while (doubleSpace != std::string::npos)
    {
	str.erase(doubleSpace, 1);
	doubleSpace = str.find("  ");
    }

    std::size_t tab = str.find('\t');
    while (tab != std::string::npos)
    {
	str.erase(tab, 1);
	tab = str.find('\t');
    }    
}

string read_block()
{
    string res{};
    while (true)
    {
	string line{};
	getline(cin, line);

	if (line == "***END***")
	    break;

	trim_string(line);
	
	if (line != "" && line != " ")
	{	
	    res += line;
	}
    }
    return res;
}

vector<string> read_orig()
{
    vector<string> res{};
    while (true)
    {
	string line{};
	getline(cin, line);

	if (line == "***END***")
	    break;

	trim_string(line);

	if (line != "" && line != " ")
	{	
	    res.push_back(line);
	}
    }
    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int cases;
    while (cin >> cases)
    {

	vector<pair<string, string>> blocks{};

	for (int c{0}; c < cases; c++)
	{
	    string name;
	    cin >> name;
	    string text{ read_block() };

	    blocks.push_back( {name, text} );
	}

	vector<string> patterns{ read_orig() };
    
	vector<string> longest_matches{};
	int max_count{0};

	for (auto block : blocks)
	{

	    vector<pair<int, int>> matches =
		string_multi_matching<string, insert_pair>(patterns, block.second);

	    sort(matches.begin(), matches.end(), [] (pair<int,int> const& p1, pair<int,int> const& p2)
	    					     {
	    						 return p1.first < p2.first;
	    					     });
	
	    int local_max_count{0};	
	    int count{1};
	    for (int i{1}; i < matches.size(); i++)
	    {		
		int position{ matches[i-1].second };
		int next_pos{ patterns[ matches[i-1].first ].size() + position};
	    
		//New match is at the line below the last one in the input block and
		//New match is at the line below on the input
		if (matches[i].second == next_pos &&
		    matches[i].first == matches[i-1].first + 1)
		{
		    //Matches position follow on each other
		    count++;

		    //if bigger value than before, save the new value
		    if (count >= local_max_count)
		    {
			local_max_count = count;
		    }
		}
		//reset counter
		else if (matches[i].second != matches[i-1].second)
		{
		    //if bigger value than before, save the new value
		    if (count >= local_max_count)
		    {
			local_max_count = count;
		    }
		
		    count = 1;
		}
	    }

	    if (max_count <= local_max_count && local_max_count != 0)
	    {
		//Reset list if not equal
		if (max_count < local_max_count)
		{
		    longest_matches.clear();
		}
	    
		max_count = local_max_count;	    
		longest_matches.push_back(block.first);
	    }
	}
    
	cout << max_count;

	for (string match : longest_matches)
	{
	    cout << " " << match;
	}
	cout << endl;
    }
}
