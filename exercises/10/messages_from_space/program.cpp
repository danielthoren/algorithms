#include<vector>
#include<string>
#include<iostream>
#include<algorithm>

#include "stringlib.h"

using namespace std;

template<typename T>
void parse_msg(string& msg, vector<string>& dict)
{
    std::vector<pair<T,T>> matches_bad =
	string_multi_matching<string, insert_pair<T>>(dict, msg);

    if (matches_bad.size() == 0)
    {
	cout << 0 << endl;
	return;
    }

    std::vector<pair<T,T>> matches{};

    transform(matches_bad.begin(), matches_bad.end(), back_inserter(matches),
	      [&dict] (pair<T,T>& p)
		  {
		      pair<T,T> np{p.second, p.second + dict[p.first].size()};
		      return np;
	      });

    sort(matches.begin(), matches.end(), [] (pair<T, T> const& m1, pair<T, T> const& m2)
					     {
						 return m1.second > m2.second;
					     });

    vector<pair<T, T>> stripped_matches{};
    stripped_matches.push_back(matches.back());
    pair<T, T> prev = stripped_matches[0];
    matches.pop_back();

    while(matches.size() != 0)
    {
	pair<T, T> next{ matches.back() };
	matches.pop_back();

	if (next.first >= prev.second)
	{
	    stripped_matches.push_back(next);
	    prev = next;
	}
    }

    cout << stripped_matches.size() << endl;
    
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    vector<string> dict{};

    while (true)
    {
	string word{};
	cin >> word;
	if (word == "#")
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
	    if (text.size() > 0)
		parse_msg<long long>(text, dict);

	    text.clear();
	}	
    }   
    return 0;
}
 
