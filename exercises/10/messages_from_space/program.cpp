#include<vector>
#include<string>
#include<iostream>
#include<algorithm>

#include "stringlib.h"

using namespace std;

void parse_msg(string msg, vector<string> dict)
{
    std::vector<pair<int,int>> matches =
	string_multi_matching<string, insert_pair>(dict, msg);

    
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    vector<string> dict{};

    while (true)
    {
	string word{};
	cin >> word;
	if (word != "#")
	    break;
	
	dict.push_back(word);
    }

    sort(dict.begin(), dict.end(), [] (string s1, string s2)
				       {
					   return s1.size() < s2.size();
				       });    

    string text{};
    while(true)
    {
	string line{};
	getline(cin, line);

	if (line == "#")
	    break;

	text = text + line;

	if (line[line.size() - 1] == '|')
	{
	    text.erase(text.size() - 1);
	    parse_msg(text, dict);

	    text.clear();
	}
    }   
    return 0;
}
 
